#include "Manager.h"

Manager::Manager(const string& name, int regNo)
{
	this->name = name;
	this->regNo = regNo;
}

Manager::Manager(Manager &otherManager)
{
	this->regNo = otherManager.regNo;
	this->name = otherManager.name;
}

/*
Manager::~Manager()
{
}
*/

int Manager::getRegNo() const
{
	return this->regNo;
}
