/**
 * ReadTweets Interface for CE221 assignment 2
 */

#ifndef READTWEETS_H
#define READTWEETS_H
/**
 * ReadTweets class. Provides mechanisms to read a text file, and return
 * lower-case versions of words from that file.
 */

#include <string>
#include <fstream>
#include <set>
#include <map>
#include "User.h"

using std::string;
using std::set;
using std::multimap;

 class ReadTweets
 {
 private:

     //file we are reading from
     std::ifstream wordfile;
     //the next word
     string nextword;
     //end of file bit: true or false
     bool eoffound;
     //PROVIDED BY LECTURER. Not sure what this is for, I guess the tweets we have to show
     set<string> tweets2show;
     multimap<User, string> tweets; //the tweets can also be another user

     //needed for the iterator class
     //set<string> all_tweets;

  public:

    /**
     * Constructor. Opens the file with the given filename and associates in
     * with the wordfile stream.
     * Initailises the other members.
     * Prints an error message then terminates the program if thr file cannot be opened.
     * Must not perform any other processing
     * @param filename - a C string naming the file to read.
     */
     ReadTweets(const char *filename);

    /**
     * Closes the file.
     */
     void close();

    /**
     * Returns a string, being the next word in the file. 
     * All letters should be converted to lower case
     * Leading and trailing punctuation symbols should not be included in the word
     * but punctuation elsewhere should not be removed
     * Returns an empty string if next word contains no letters
     * @return - string - next word.
     */
     string getNextWord();

    /**
     * Returns true if there is a further word in the file, false if we have reached the
     * end of file.
     * @return - bool - !eof
     */
     bool isNextWord();

     /**
      * This method should get all tweets based on a user registration number
      * the return type is bool so that true means the function was succesfully executed
      * and false otherwise. Tweets should be stored in the Tweets set.
      **/

     bool getTweets();

     /**
      * The method getTweetsToShow should select randomly five tweets from the file and store them in the set 
      * private member array tweets2show. The return type is bool so that true means the function was succesfully 
      * executed and false otherwise
      * */
     bool getTweetsToShow();

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
         // store an iterator for the tweets2show set
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
         // store a const_iterator for the tweets2show set
         set<string>::const_iterator it;
         //store a const_terator for the multimap tweets (Will be used to iterator either over the whole map or per user)
         multimap<User, string>::iterator mm_it;
         // constructor
         const_iterator(set<string>::const_iterator it) : it(it) {}
         const_iterator(multimap<User, string>::iterator it) : mm_it(it) {}
     };

     // define the begin and end functions to return the iterators
     iterator begin() { return iterator(tweets.begin()); }
     iterator end() { return iterator(tweets.end()); }
     const_iterator begin() const { return const_iterator(tweets.cbegin()); }
     const_iterator end() const { return const_iterator(tweets.end()); }

     //multimap iterators, is based on user, and will attempt to find the the first user it comes across to iterate through it.

     //Link: https://thispointer.com/multimap-example-and-tutorial-in-c/
     //Link: https://www.google.com/search?q=multimap+how+to+get+all+values+assigned+to+a+key&oq=multimap+how+to+get+all+values+assigned+to+a+key&aqs=chrome..69i57j33i160l2j33i22i29i30.13423j0j7&sourceid=chrome&ie=UTF-8
     iterator mm_User_range_begin(User user)
     {
         // get the range of values for a specific key in the multimap
         auto range = tweets.equal_range(user);
         // return the iterator pointing to the first element in the range
         return std::begin(tweets.equal_range(user).);
     }
     iterator mm_User_range_end() { return iterator(all_tweets.end()); }
     const_iterator begin() const { return const_iterator(all_tweets.begin()); }
     const_iterator end() const { return const_iterator(all_tweets.end()); }

 };

 #endif
