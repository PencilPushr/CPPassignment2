#include "User.h"

User::User(const string& name, int regNo)
{
	this->name = name;
	this->regNo = regNo;
}

int User::getRegNo() const
{
	return this->regNo;
}

void User::addScore(float score, string twit)
{
	this->accumulative_reputation_score += score;
}

bool User::updateAccumulativeScore(float score)
{
	return this->accumulative_reputation_score += score;
}

//the template means we can use a float or an int for our division
template <size_t N>
bool User::updateFASTRunningAverage(float avg, float score)
{
	this->average_reputation_score; -= this->average_reputation_score; / N;
	this->average_reputation_score; += input / N;
	return this->average_reputation_score;
}

bool User::updateCircularRunningAverage(float score)
{

}

ostream& operator<<(ostream& str, const User& s)
{
	str = "Users regNo: " + std::to_string(s.regNo) + "\n"
			+ "Users name: " + s.name + "\n"
			+ "User accumlative rep: " + std::to_string(s.accumulative_reputation_score) + "\n"
			+ "Users average rep " + std::to_string(s.average_reputation_score) + "\n"
		//I assume we will need to iterate through the map (of the highest and lowest tweets so I'm leaving this overloaded operator incomplete
		// + "Users highest rated tweet: " std::multimap::iterator collect the pair with the highest number and print out the associated key (std::string)

	// TODO: insert return statement here
	return str;
}
