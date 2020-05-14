#pragma once
class Job
{
private:
	int name;
	int timeForPick;
	int timeForPack;
	bool blocked;
	int timeComeToPick;
	int timeComeToPack;
	int timeComeToBuf;
	int timeComeFromPick;
	int timeComeFromPack;
	int timeComeFromBuf;
	bool pickingCompleted;
	bool packingCompleted;
	int indPickingMachine = -1;
	int indPackingMachine = -1;
	int indBuferMachine = -1;
public:
	Job();
	Job(int name1, int timeForPick1, int timeForPack1);
	int getTimeForPick();
	int getTimeForPack();
	int getName();
	bool getBlocked();
	int getTimeComeToPick();
	int getTimeComeToPack();
	int getTimeComeToBuf();
	int getTimeComeFromPick();
	int getTimeComeFromPack();
	int getTimeComeFromBuf();
	void setName(int name1);
	void setTimeForPick(int time);
	void setTimeForPack(int time);
	void setBlocked(bool isBlocked);
	void setTimeComeToPick(int time);
	void setTimeComeToPack(int time);
	void setTimeComeToBuf(int time);
	void setTimeComeFromPick(int time);
	void setTimeComeFromPack(int time);
	void setTimeComeFromBuf(int time);
	void setPickingCompleted(bool isCompleted);
	bool getPickingCompleted() const;
	void setPackingCompleted(bool isCompleted);
	bool getPackingCompleted() const;
	void setIndPickingMachine(int ind);
	void setIndPackingMachine(int ind);
	void setIndBuferMachine(int ind);
	int getIndPickingMachine();
	int getIndPackingMachine();
	int getIndBuferMachine();
	Job(const Job& orig);
	/*Job& operator=(Job& orig);*/
	Job& operator=(Job orig);
	void toString() const;
	~Job();

};


