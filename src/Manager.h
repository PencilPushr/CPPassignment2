// include your own comments

#ifndef _MANAGER_H_
#define _MANAGER_H_

#include <string>
#include <vector>
#include <stdexcept>
#include "Person.h"

using std::string;

class Manager: public Person
{   public:
        // constructor should initialise name and registration number using arguments
        Manager(const string &name, int regNo);
		Manager(Manager &otherManager);

		//destructor
		//~Manager();

	   // method to return registration number
	   int getRegNo() const;

    private:
	   int regNo;
	   string name;
};

#endif
