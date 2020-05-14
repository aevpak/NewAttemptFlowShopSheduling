#include "FlowShop.h"
#include <iostream>

typedef struct buferElem {
	int name, time, ind;
} buferElem;

class CompareBufer {
public:
	bool operator()(buferElem j1, buferElem j2)
	{
		return j1.time > j2.time;
	}
};

FlowShop::FlowShop()
{
	picking = std::vector<int>(pickingSize, -1);
	packing = std::vector<int>(packingSize, -1);
	bufer = std::vector<int>(buferSize, -1);
	for (int i = 0; i < buferSize; i++)
		indexesBuferEmpty.push(i);
	for (int i = 0; i < packingSize; i++)
		indexesPackingEmpty.push(i);
}

void FlowShop::toString()
{
	std::cout << "Input: " << std::endl;
	if (!input.empty()) {
		std::queue<int> copy = input;
		while (!copy.empty()) {
			std::cout << copy.front() << " ";
			copy.pop();
		}
		std::cout << std::endl;
	}
	std::cout << "Picking: " << std::endl;
	if (!picking.empty()) {
		for (auto it = picking.begin(); it != picking.end(); ++it)
			std::cout << *it << " ";
		std::cout << std::endl;
	}
	std::cout << "Bufer: " << std::endl;
	if (!bufer.empty()) {
		for (auto it = bufer.begin(); it != bufer.end(); ++it)
			std::cout << *it << " ";
		std::cout << std::endl;
	}
	std::cout << "Packing: " << std::endl;
	if (!packing.empty()) {
		for (auto it = packing.begin(); it != packing.end(); ++it)
			std::cout << *it << " ";
		std::cout << std::endl;
	}
	std::cout << "Output: " << std::endl;
	if (!output.empty()) {
		std::queue<int> copy = output;
		while (!copy.empty()) {
			std::cout << copy.front() << " ";
			copy.pop();
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void FlowShop::pushInput(int j)
{
	input.push(j);
}

void FlowShop::setCount(int cou)
{
	this->count = cou;
}

void FlowShop::setTime(int t)
{
	this->time = t;
}

int FlowShop::getTime()
{
	return this->time;
}

void FlowShop::pushEventList(int name1, int type1, int time1)
{
	Event e(name1, type1, time1);
	eventList.push(e);
}

void FlowShop::pushEventList(Event e)
{
	eventList.push(e);
}

void FlowShop::popEventList()
{
	eventList.pop();
}

Event FlowShop::getTopEvent()
{
	Event e = eventList.top();
	return e;
}

void FlowShop::run()
{
	for (int i = 0; i < pickingSize; i++) {
		int j = input.front();
		input.pop();
		picking[i] = j;
		data[j].setIndPickingMachine(i);
		data[j].setTimeComeToPick(0);
		eventList.push(Event(j, data[j].getTimeForPick(), 1));
	}
	while (!eventList.empty()) {
		Event topEvent = getTopEvent();
		popEventList();
		int currentTime = topEvent.getTime();
		setTime(currentTime);
		//std::cout << "\n" << "EVENT!!! " << topEvent.getName() << "\n";
		if (topEvent.getType() == 1) {
			//picking
			//int bufInd = FAM(bufer);
			if (!indexesBuferEmpty.empty()) {
				//в буфере есть место
				int bufInd = indexesBuferEmpty.front();
				indexesBuferEmpty.pop();
				int eventName = topEvent.getName();
				bufer[bufInd] = eventName;
				data[eventName].setTimeComeFromPick(currentTime);
				data[eventName].setTimeComeToBuf(currentTime);
				data[eventName].setIndBuferMachine(bufInd);
				indexesPickingEmpty.push(data[eventName].getIndPickingMachine());
				//picking[data[eventName].getIndPickingMachine()] = -1;
				std::priority_queue<buferElem, std::vector<buferElem>, CompareBufer> candidatsBufer;
				for (auto it = bufer.begin(); it != bufer.end(); ++it) {
					if(*it != -1){
						buferElem e;
						e.name = *it;
						e.time = data[*it].getTimeForPack();
						e.ind = int(std::distance(bufer.begin(), it));
						candidatsBufer.push(e);
					}					
				}
				while (!indexesPackingEmpty.empty() && !candidatsBufer.empty()) {
					int indPacking = indexesPackingEmpty.front();
					indexesPackingEmpty.pop();
					int indBufer = candidatsBufer.top().name;
					indexesBuferEmpty.push(candidatsBufer.top().ind);
					bufer[candidatsBufer.top().ind] = -1;
					candidatsBufer.pop();
					packing[indPacking] = indBufer;
					data[indBufer].setTimeComeFromBuf(currentTime);
					data[indBufer].setTimeComeToPack(currentTime);
					data[indBufer].setIndPackingMachine(indPacking);
					Event e(indBufer, currentTime + data[indBufer].getTimeForPack(), 2);
					eventList.push(e);
				}
				std::priority_queue<buferElem, std::vector<buferElem>, CompareBufer> candidatsPicking;
				for (auto it = picking.begin(); it != picking.end(); ++it) {
					if (data[*it].getBlocked() && data[*it].getIndBuferMachine() == -1) {
						buferElem e;
						e.name = *it;
						e.time = data[*it].getTimeForPack();
						e.ind = int(std::distance(picking.begin(), it));
						candidatsPicking.push(e);
					}
				}
				while (!indexesBuferEmpty.empty() && !candidatsPicking.empty()) {
					int indBufer = indexesBuferEmpty.front();
					indexesBuferEmpty.pop();
					int indPicking = candidatsPicking.top().name;
					indexesPickingEmpty.push(candidatsPicking.top().ind);
					candidatsPicking.pop();
					bufer[indBufer] = indPicking;
					data[indPicking].setTimeComeFromPick(currentTime);
					data[indPicking].setTimeComeToBuf(currentTime);
					data[indPicking].setIndBuferMachine(indBufer);
				}
				while (!indexesPickingEmpty.empty() && !input.empty()) {
					int indPicking = indexesPickingEmpty.front();
					indexesPickingEmpty.pop();
					int j = input.front();
					input.pop();
					picking[indPicking] = j;
					data[j].setIndPickingMachine(indPicking);
					data[j].setTimeComeToPick(currentTime);
					eventList.push(Event(j, currentTime + data[j].getTimeForPick(), 1));
				}
			}
			else {
				//в буфере нет места
				data[topEvent.getName()].setBlocked(true);
			}
		}
		if (topEvent.getType() == 2) {
			//packing
			output.push(topEvent.getName());
			indexesPackingEmpty.push(data[topEvent.getName()].getIndPackingMachine());
			data[topEvent.getName()].setTimeComeFromPack(currentTime);
			std::priority_queue<buferElem, std::vector<buferElem>, CompareBufer> candidatsBufer;
			for (auto it = bufer.begin(); it != bufer.end(); ++it) {
				if (*it != -1) {
					buferElem e;
					e.name = *it;
					e.time = data[*it].getTimeForPack();
					e.ind = int(std::distance(bufer.begin(), it));
					candidatsBufer.push(e);
				}
				
			}
			while (!indexesPackingEmpty.empty() && !candidatsBufer.empty()) {
				int indPacking = indexesPackingEmpty.front();
				indexesPackingEmpty.pop();
				int indBufer = candidatsBufer.top().name;
				indexesBuferEmpty.push(candidatsBufer.top().ind);
				//std::cout << "\nTEEEST111111! " << candidatsBufer.top().ind << " " << bufer[candidatsBufer.top().ind] << "\n";
				bufer[candidatsBufer.top().ind] = -1;
				//std::cout << "\nTEEEST22222!! " << candidatsBufer.top().ind << " " << bufer[candidatsBufer.top().ind] << "\n";
				//toString();
				candidatsBufer.pop();
				packing[indPacking] = indBufer;
				data[indBufer].setTimeComeFromBuf(currentTime);
				data[indBufer].setTimeComeToPack(currentTime);
				data[indBufer].setIndPackingMachine(indPacking);
				Event e(indBufer, currentTime + data[indBufer].getTimeForPack(), 2);
				eventList.push(e);
			}
			std::priority_queue<buferElem, std::vector<buferElem>, CompareBufer> candidatsPicking;
			for (auto it = picking.begin(); it != picking.end(); ++it) {
				if (data[*it].getBlocked() && data[*it].getIndBuferMachine() == -1) {
					buferElem e;
					e.name = *it;
					e.time = data[*it].getTimeForPack();
					e.ind = int(std::distance(picking.begin(), it));
					candidatsPicking.push(e);
				}
			}
			while (!indexesBuferEmpty.empty() && !candidatsPicking.empty()) {
				int indBufer = indexesBuferEmpty.front();
				indexesBuferEmpty.pop();
				int indPicking = candidatsPicking.top().name;
				indexesPickingEmpty.push(candidatsPicking.top().ind);
				candidatsPicking.pop();
				bufer[indBufer] = indPicking;
				data[indPicking].setTimeComeFromPick(currentTime);
				data[indPicking].setTimeComeToBuf(currentTime);
				data[indPicking].setIndBuferMachine(indBufer);
			}
			while (!indexesPickingEmpty.empty() && !input.empty()) {
				int indPicking = indexesPickingEmpty.front();
				indexesPickingEmpty.pop();
				int j = input.front();
				input.pop();
				picking[indPicking] = j;
				data[j].setIndPickingMachine(indPicking);
				data[j].setTimeComeToPick(currentTime);
				eventList.push(Event(j, currentTime + data[j].getTimeForPick(), 1));
			}
		}
		if (topEvent.getType() == 0) {
			//ERROR!!
			std::cout << "ERROR!";
			break;
		}
		//toString();
	}
}

void FlowShop::setData(std::vector<Job> vec)
{
	this->data = vec;
}

int FlowShop::FAM(std::vector<int> vec)
{
	int ind = -1;
	for (auto it = vec.begin(); it != vec.end(); ++it)
		if (*it == -1) {
			ind = int(std::distance(vec.begin(), it));
			break;
		} 
	return ind;
}

void FlowShop::eventListToString()
{
	std::priority_queue<Event, std::vector<Event>, CompareEvent> copy = eventList;
	while (!copy.empty()) {
		Event e = copy.top();
		std::cout << e.getName() << " ";
		copy.pop();
	}
	std::cout << std::endl;
}

void FlowShop::printProcess(bool firstly, std::string dir)
{
	std::ofstream fout;
	if (firstly) {
		fout.open(dir + " before.csv");
	}
	else {
		fout.open(dir + " after.csv");
	}
	fout << "work_id start_pick finish_pick start_buff finish_buff start_pack finish_pack pick_id buff_id pack_id real_time\n";
	for (auto it = data.begin(); it != data.end(); ++it) {
		Job j = *it;
		fout << j.getName()
			<< " " << j.getTimeComeToPick()
			<< " " << j.getTimeComeFromPick()
			<< " " << j.getTimeComeToBuf()
			<< " " << j.getTimeComeFromBuf()
			<< " " << j.getTimeComeToPack()
			<< " " << j.getTimeComeFromPack()
			<< " " << j.getIndPickingMachine()
			<< " " << j.getIndBuferMachine()
			<< " " << j.getIndPackingMachine()
			<< " " << j.getTimeForPick() << std::endl;
	}
	fout.close();
}

FlowShop::~FlowShop()
{
}
