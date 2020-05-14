#pragma once
#include <queue>
#include "Job.h"
#include <iostream>
#include "Event.h"
#include "CompareEvent.h"
#include <fstream>
class FlowShop
{
private: 
	int pickingSize = 3;
	int buferSize = 3;
	int time = 0;
	int packingSize = 3;
	int count = 200;
	std::vector<Job> data;
	std::queue<int> input;
	std::vector<int> picking;
	std::vector<int> bufer;
	std::vector<int> packing;
	std::queue<int> output;
	std::priority_queue<Event, std::vector<Event>, CompareEvent> eventList;
	std::queue<int> indexesPickingEmpty;
	std::queue<int> indexesBuferEmpty;
	std::queue<int> indexesPackingEmpty;
	std::vector<int> indexesBuferUsing;
public:
	FlowShop();
	void toString();
	void pushInput(int j);
	void setCount(int cou);
	void setTime(int t);
	int getTime();
	void pushEventList(int name1, int type1, int time1);
	void pushEventList(Event e);
	void popEventList();
	Event getTopEvent();
	void run();
	void setData(std::vector<Job> vec);
	int FAM(std::vector<int> vec);
	void eventListToString();
	void printProcess(bool firstly, std::string dir);
	~FlowShop();
};

