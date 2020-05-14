#include "Job.h"
#include <iostream>

Job::Job() {
	name = -1;
	timeForPick = 0;
	timeForPack = 0;
	blocked = false;
	timeComeToPick = 0;
	timeComeToPack = 0;
	timeComeToBuf = 0;
	timeComeFromPick = 0;
	timeComeFromPack = 0;
	timeComeFromBuf = 0;
	pickingCompleted = false;
	packingCompleted = false;
	indPickingMachine = -1;
	indPackingMachine = -1;
	indBuferMachine = -1;
}
Job::Job(int name1, int timeForPick1, int timeForPack1) {
	name = name1;
	timeForPick = timeForPick1;
	timeForPack = timeForPack1;
	blocked = false;
	timeComeToPick = 0;
	timeComeToPack = 0;
	timeComeToBuf = 0;
	timeComeFromPick = 0;
	timeComeFromPack = 0;
	timeComeFromBuf = 0;
	pickingCompleted = false;
	packingCompleted = false;
	indPickingMachine = -1;
	indPackingMachine = -1;
	indBuferMachine = -1;
}
int Job::getTimeForPick() {
	return this->timeForPick;
}
int Job::getTimeForPack() {
	return this->timeForPack;
}
int Job::getName() {
	return this->name;
}
void Job::setTimeForPick(int time) {
	this->timeForPick = time;
}
bool Job::getBlocked() {
	return this->blocked;
}
int Job::getTimeComeToPick() {
	return this->timeComeToPick;
}
int Job::getTimeComeToPack() {
	return this->timeComeToPack;
}
int Job::getTimeComeToBuf() {
	return this->timeComeToBuf;
}
int Job::getTimeComeFromPick() {
	return this->timeComeFromPick;
}
int Job::getTimeComeFromPack() {
	return this->timeComeFromPack;
}
int Job::getTimeComeFromBuf() {
	return this->timeComeFromBuf;
}
void Job::setName(int name1) {
	this->name = name1;
}
void Job::setTimeForPack(int time) {
	this->timeForPack = time;
}
void Job::setBlocked(bool isBlocked) {
	this->blocked = isBlocked;
}
void Job::setTimeComeToPick(int time) {
	this->timeComeToPick = time;
}
void Job::setTimeComeToPack(int time) {
	this->timeComeToPack = time;
}
void Job::setTimeComeToBuf(int time) {
	this->timeComeToBuf = time;
}
void Job::setTimeComeFromPick(int time) {
	this->timeComeFromPick = time;
}
void Job::setTimeComeFromPack(int time) {
	this->timeComeFromPack = time;
}
void Job::setTimeComeFromBuf(int time) {
	this->timeComeFromBuf = time;
}
void Job::setIndPickingMachine(int ind)
{
	this->indPickingMachine = ind;
}
void Job::setIndPackingMachine(int ind)
{
	this->indPackingMachine = ind;
}
void Job::setIndBuferMachine(int ind)
{
	this->indBuferMachine = ind;
}
int Job::getIndPickingMachine()
{
	return this->indPickingMachine;
}
int Job::getIndPackingMachine()
{
	return this->indPackingMachine;
}
int Job::getIndBuferMachine()
{
	return this->indBuferMachine;
}
Job::Job(const Job& orig) {
	name = orig.name;
	timeForPick = orig.timeForPick;
	timeForPack = orig.timeForPack;
	blocked = orig.blocked;
	timeComeToPick = orig.timeComeToPick;
	timeComeToPack = orig.timeComeToPack;
	timeComeToBuf = orig.timeComeToBuf;
	timeComeFromPick = orig.timeComeFromPick;
	timeComeFromPack = orig.timeComeFromPack;
	timeComeFromBuf = orig.timeComeFromBuf;
	pickingCompleted = orig.pickingCompleted;
	packingCompleted = orig.packingCompleted;
	indPickingMachine = orig.indPickingMachine;
	indPackingMachine = orig.indPackingMachine;
	indBuferMachine = orig.indBuferMachine;
}
//Job& Job::operator=(Job& orig) {
//	if (this == &orig) {
//		return *this;
//	}
//	name = orig.name;
//	timeForPick = orig.timeForPick;
//	timeForPack = orig.timeForPack;
//	blocked = orig.blocked;
//	timeComeToPick = orig.timeComeToPick;
//	timeComeToPack = orig.timeComeToPack;
//	timeComeToBuf = orig.timeComeToBuf;
//	timeComeFromPick = orig.timeComeFromPick;
//	timeComeFromPack = orig.timeComeFromPack;
//	timeComeFromBuf = orig.timeComeFromBuf;
//	pickingCompleted = orig.pickingCompleted;
//	packingCompleted = orig.packingCompleted;
//	indPickingMachine = orig.indPickingMachine;
//	indPackingMachine = orig.indPackingMachine;
//	indBuferMachine = orig.indBuferMachine;
//	return *this;
//}
Job& Job::operator=(Job orig)
{
	if (this == &orig) {
		return *this;
	}
	name = orig.name;
	timeForPick = orig.timeForPick;
	timeForPack = orig.timeForPack;
	blocked = orig.blocked;
	timeComeToPick = orig.timeComeToPick;
	timeComeToPack = orig.timeComeToPack;
	timeComeToBuf = orig.timeComeToBuf;
	timeComeFromPick = orig.timeComeFromPick;
	timeComeFromPack = orig.timeComeFromPack;
	timeComeFromBuf = orig.timeComeFromBuf;
	pickingCompleted = orig.pickingCompleted;
	packingCompleted = orig.packingCompleted;
	indPickingMachine = orig.indPickingMachine;
	indPackingMachine = orig.indPackingMachine;
	indBuferMachine = orig.indBuferMachine;
	return *this;
}
void Job::toString() const {
	std::cout
		<< "name " << name << std::endl
		<< "timeForPick " << timeForPick << std::endl
		<< "timeForPack " << timeForPack << std::endl
		<< "blocked " << blocked << std::endl
		<< "timeComeToPick " << timeComeToPick << std::endl
		<< "timeComeToPack " << timeComeToPack << std::endl
		<< "timeComeToBuf " << timeComeToBuf << std::endl
		<< "timeComeFromPick " << timeComeFromPick << std::endl
		<< "timeComeFromPack " << timeComeFromPack << std::endl
		<< "timeComeFromBuf " << timeComeFromBuf << std::endl
		<< "pickingCompleted " << pickingCompleted << std::endl
		<< "packingCompleted " << packingCompleted << std::endl << std::endl;
}
void Job::setPickingCompleted(bool isCompleted) {
	this->pickingCompleted = isCompleted;
}
bool Job::getPickingCompleted() const {
	return pickingCompleted;
}
void Job::setPackingCompleted(bool isCompleted) {
	this->packingCompleted = isCompleted;
}
bool Job::getPackingCompleted() const {
	return packingCompleted;
}
Job::~Job() {
}