#include "CompareEvent.h"

bool CompareEvent::operator()(Event j1, Event j2)
{
	return j1.getTime() > j2.getTime();
}
