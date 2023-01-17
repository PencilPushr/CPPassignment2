// include your own comments

#ifndef _PERSON_H_
#define _PERSON_H_

#include <string>

using namespace std;

class Person
{   public:
        Person(const string &name, const int& regNo);
		//default constructor
		//Person();
	   string getName() const;
	   //don't use this, it fucks up the program
	   void changeName(const string &newName);
    protected:
	   string name;
	   int regNo;
};

#endif
