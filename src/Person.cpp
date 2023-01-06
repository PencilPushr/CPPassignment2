#include "Person.h"
#include "Person.h"
// include your own comments

#include <string>
#include "Person.h"

using std::string;

Person::Person()
{
	this->name = nullptr;
}


Person::Person(const string &name)
{   this->name = name;
}

/*
Person::~Person()
{
}
*/

Person::Person(Person& otherPerson)
{
	this->name = otherPerson.name;
}

string Person::getName() const
{   return this->name;
}

void Person::changeName(const string &newName)
{   this->name = newName;
}
