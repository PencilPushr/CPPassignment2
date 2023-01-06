// include your own comments

#ifndef _PERSON_H_
#define _PERSON_H_

#include <string>

using std::string;

class Person
{   
public:
	//default con
	Person();
	//constructor
	Person(const string& name);
	//copy constructor
	Person(Person& otherPerson);
	//destructor not needed as we are only using heap memory
	//~Person();
	string getName() const;
	void changeName(const string &newName);
protected:
	string name;
};

#endif
