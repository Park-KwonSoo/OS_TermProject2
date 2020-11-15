#include "PCB.h"

PCB::PCB()
{
	this->name = "";
	this->BurstTime = 0;
	this->ArrivalTime = 0;
	this->waitTime = 0;
	this->finishTime = 0;
}

PCB::PCB(string name, float ArrivalTime, float BurstTime)
{
	this->name = name;
	this->ArrivalTime = ArrivalTime; 
	this->BurstTime = BurstTime;
	this->waitTime = 0;
	this->finishTime = this->ArrivalTime;
}

void PCB::reduceBurstTime(float reduce)
{
	this->BurstTime -= reduce;
}

void PCB::increaseWaitTime(float increase)
{
	this->waitTime += increase;
}

void PCB::printPCB()
{
	cout << "PCB : " << this->name << endl
		<< "BurstTime : " << this->BurstTime << endl
		<< "Arrival Time : " << this->ArrivalTime << endl;
}

void PCB::setFinishTime(float finishTime)
{
	this->finishTime = finishTime;
}

string PCB::getName()
{
	return this->name;
}

float PCB::getBurstTime()
{
	return this->BurstTime;
}

float PCB::getArrivalTime()
{
	return this->ArrivalTime;
}

float PCB::getWaitTime()
{
	return this->waitTime;
}

float PCB::getFinishTime()
{
	return this->finishTime;
}

bool PCB::isBurst()
{
	return this->BurstTime;
}

