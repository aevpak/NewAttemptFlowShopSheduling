#pragma once
class Event
{
private:
	int name;
	int time;
	int type;//0 - crash, 1 - picking, 2 - packing
public:
	Event();
	Event(int name1, int time1, int type1);
	Event(const Event& orig);
	Event& operator=(Event& orig);
	Event& operator=(Event orig);
	int getName();
	int getType();
	int getTime();
	void setName(int name1);
	void setType(int type1);
	void setTime(int time1);
	~Event();
};

