// include your own comments

#ifndef _USER_H_
#define _USER_H_

#include <string>
#include <map>
#include <stdexcept>
#include "Person.h"

using std::string;
using std::multimap;
using std::ostream;


class NoScoreException: public std::exception
{
	
public:
	NoScoreException();


};

enum class ERR_CODE
{
	ERR_SUCCESS,
	ERR_FAIL,
	ERR_BAD_PARAM,
	ERR_FAILED_CHECK,
	ERR_UNKNOWN //generic failure
};

class User: public Person
{   public:
        // constructor should initialise name and registration number using arguments
        // and initialise score map to be empty
        User(const string &name, int regNo);

	   // method to return registration number
	   int getRegNo() const;

	   // method to add the score to the map
	   void addScore(float score,string twit);

	   // method to update the accumulative score map
	   // should throw NoScoreException if user has no tweet yet
	   bool updateAccumulativeScore(float score);

	   //expo moving average: https://en.wikipedia.org/wiki/Moving_average#Exponential_moving_average
	   template<size_t N>
	   bool updateFASTRunningAverage(float avg, float score);

	   //Link: https://stackoverflow.com/questions/10990618/calculate-rolling-moving-average-in-c
	   //Use the MovingAverage.h
	   bool updateCircularRunningAverage(float score);

    private:
	   int regNo;
	   //this is a copy from user
	   //string name;
	   multimap<string,float> reputation_scores;  // scores map, with each in range 0.0 to 100.0, and a tweet
	   float accumulative_reputation_score; 
	   float average_reputation_score; 

    // friend function to output details of user to stream
    // output to be defined and formated by you
    // if the user has no scores "has no scores" should be output instead of the scores
    friend ostream& operator<<(ostream &str, const User &s)
};

#endif
