
#ifndef ITERATOR_FOR_TWEETS_H
#define ITERATOR_FOR_TWEETS_H

namespace itr{

    class iterator
    {
    public:
        // constructor and other necessary 
        // ...
        // overload the * operator to return the current element
        string operator*() const { return *it; }
        // overload the ++ operator to move to the next element
        iterator& operator++() { ++it; return *this; }
        // overload the == operator to compare two iterators
        bool operator==(const iterator& other) const { return it == other.it; }
        // overload the != operator to compare two iterators
        bool operator!=(const iterator& other) const { return it != other.it; }

    private:
        // iterator needs access to the tweets set to iterate through it
        friend class ReadTweets;
        // store an iterator for the tweets set
        set<string>::iterator it;
        //store an iterator for the multimap tweets (Will be used to iterator either over the whole map or per user)
        multimap<User, string>::iterator mm_it;
        // constructor
        iterator(set<string>::iterator it) : it(it) {}
        iterator(multimap<User, string>::iterator it) : mm_it(it) {}
    };

    //read-only version of iterator
    class const_iterator
    {
    public:
        // constructor and other necessary functions
        // ...
        // overload the * operator to return the current element
        const string operator*() const { return *it; }
        // overload the ++ operator to move to the next element
        const_iterator& operator++() { ++it; return *this; }
        // overload the == operator to compare two iterators
        bool operator==(const const_iterator& other) const { return it == other.it; }
        // overload the != operator to compare two iterators
        bool operator!=(const const_iterator& other) const { return it != other.it; }

    private:
        // const_iterator needs access to the tweets set to iterate through it
        friend class ReadTweets;
        // store a const_iterator for the tweets set
        set<string>::const_iterator it;
        //store a const_terator for the multimap tweets (Will be used to iterator either over the whole map or per user)
        multimap<User, string>::iterator mm_it;
        // constructor
        const_iterator(set<string>::const_iterator it) : it(it) {}
        const_iterator(multimap<User, string>::iterator it) : mm_it(it) {}
    };

    // define the begin and end functions to return the iterators
    iterator begin() { return iterator(all_tweets.begin()); }
    iterator end() { return iterator(all_tweets.end()); }
    const_iterator begin() const { return const_iterator(all_tweets.begin()); }
    const_iterator end() const { return const_iterator(all_tweets.end()); }

    //multimap iterators, is based on user, and will attempt to find the the first user it comes across to iterate through it.
    iterator mm_begin() { return iterator(tweets.begin()); }
    iterator mm_end() { return iterator(tweets.end()); }

    //Link: https://thispointer.com/multimap-example-and-tutorial-in-c/
    //Link: https://www.google.com/search?q=multimap+how+to+get+all+values+assigned+to+a+key&oq=multimap+how+to+get+all+values+assigned+to+a+key&aqs=chrome..69i57j33i160l2j33i22i29i30.13423j0j7&sourceid=chrome&ie=UTF-8
    iterator mm_User_begin(User) { return iterator(tweets.find(User) }
    iterator mm_User_end() { return iterator(all_tweets.end()); }
    const_iterator begin() const { return const_iterator(all_tweets.begin()); }
    const_iterator end() const { return const_iterator(all_tweets.end()); }
    };
}

#endif