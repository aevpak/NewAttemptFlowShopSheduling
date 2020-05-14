#pragma once
#include "Event.h"
class CompareEvent
{
public:
	bool operator() (Event j1, Event j2);
};

