// include your own comments

#include <string>
#include "Person.h"

using namespace std;

Person::Person(const string& name, const int& regNo)
{
	this->name = name;
	this->regNo = regNo;
}

string Person::getName() const
{   return name;
}

/*
I'm certain there's no way to handle all the edge cases, if you change your name mid program, what about all the previous tweets you have made?
It becomes difficult to keep track of all the different tweet
*/
void Person::changeName(const string &newName)
{   name = newName;
}
