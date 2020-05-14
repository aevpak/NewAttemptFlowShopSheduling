#include "Event.h"

Event::Event()
{
	name = 0;
	time = 0;
	type = 0;
}

Event::Event(int name1, int time1, int type1)
{
	name = name1;
	time = time1;
	type = type1;
}

Event::Event(const Event& orig)
{
	name = orig.name;
	time = orig.time;
	type = orig.type;
}

Event& Event::operator=(Event& orig)
{
	if (this == &orig) {
		return *this;
	}
	name = orig.name;
	time = orig.time;
	type = orig.type;
	return *this;
}
Event& Event::operator=(Event orig)
{
	if (this == &orig) {
		return *this;
	}
	name = orig.name;
	time = orig.time;
	type = orig.type;
	return *this;
}

int Event::getName()
{
	return this->name;
}

int Event::getType()
{
	return this->type;
}

int Event::getTime()
{
	return this->time;
}

void Event::setName(int name1)
{
	this->name = name1;
}

void Event::setType(int type1)
{
	this->type = type1;
}

void Event::setTime(int time1)
{
	this->time = time1;
}

Event::~Event()
{
}
