#include "User.h"
#include <iostream>


NoScoreException::NoScoreException(const char* message) : std::exception(message)
{
	//C-style string exception
}


NoScoreException::~NoScoreException() 
{
	//this is incase, you wish to add a private variable such as std::string _message in the class, otherwise this just acts as a placeholder destructor
}

char const* NoScoreException::what() const noexcept
{
	return "You attempted to call/update a User score when they have none.";
}

User::User(const string& name, int regNo) : Person(name, regNo)
{
}

/*
 * ------------------------------------------------------- USER MEMBER FUNCTIONS -----------------------------------------------------------------------
 */

int User::getRegNo() const
{
	return this->regNo;
}

float User::calculateAverageScore(float accumulated_score, int no_of_tweets)
{
	return (accumulated_score / no_of_tweets);
}

bool User::updateAccumulativeScore(float score)
{
	try
	{
		if (this->m_noTweets == 0) throw (NoScoreException());
		this->accumulative_reputation_score += score;
	}
	catch (NoScoreException nse)
	{
		std::cout << nse.what();
	}
}

ostream& operator<<(ostream& str, const User& s)
{
	return str;
}
