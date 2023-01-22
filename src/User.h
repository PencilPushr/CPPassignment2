// include your own comments

#ifndef _USER_H_
#define _USER_H_

#include <string>
#include <map>
#include <stdexcept>
#include "Person.h"

using namespace std;

class NoScoreException: public exception
{
public:
	NoScoreException() = default;
	NoScoreException(const char* message);
	~NoScoreException();
	char const* what() const noexcept;
};

class User: public Person
{   public:
        // constructor should initialise name and registration number using arguments
        // and initialise score map to be empty
        User(const string &name, int regNo);

	   // method to return registration number
	   int getRegNo() const;

	   float calculateAverageScore(float accumulated_score, int no_of_tweets);

	   // method to update the accumulative score map
	   // should throw NoScoreException if user has no tweet yet
	   bool updateAccumulativeScore(float score);

    private:
		//don't need this anymore cuz I edited Person.h
		int regNo{};
		float accumulative_reputation_score{};
		float average_reputation_score{};
		size_t m_noTweets{};

    // friend function to output details of user to stream
    // output to be defined and formated by you
    // if the user has no scores "has no scores" should be output instead of the scores
    friend ostream& operator<<(ostream &str, const User &s);
};

#endif
