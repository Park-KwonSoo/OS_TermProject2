#include "FCFS.h"

FCFS::FCFS()
{
	this->averageWaitTime = 0;
	this->totalTime = 0;
	this->size = 0;
}

void FCFS::Schedule()
{
	//shceduling_List �ʱ�ȭ
	this->scheduling_List.clear();
	this->burstTimeSection.clear();
	this->burstTimeSection.push_back(0);

	int ogSize = this->size;
	while (!this->pcbList.empty()) {
		//pcbList�� ���� �տ� �ִ� PCB�� schedule list�� ����
		PCB Temp = *this->pcbList.begin();
		this->scheduling_List.push_back(Temp);

		//���� arrival time�� �����µ��� �۾��� �����ϰ� �ִٸ� waitingtime�� �߰�
		if (Temp.getArrivalTime() < this->totalTime)
			Temp.increaseWaitTime(this->totalTime - Temp.getArrivalTime());
		this->totalTime += Temp.getBurstTime();
		this->burstTimeSection.push_back(this->totalTime);

		//�۾� ���� PCB�� pcbList���� ����, ���� �� averageTime�� �ش� �� �Է�
		this->averageWaitTime += Temp.getWaitTime();
		this->pcbList.pop_front();
		this->size--;
	}
	this->averageWaitTime /= ogSize;
}

void FCFS::printQueue()
{
	list<float>::iterator timeIter = this->burstTimeSection.begin();
	cout << endl << "FCFS Schedule List : " << endl;
	//schedule list�� average wait time�� ����Ѵ�.
	while (!this->scheduling_List.empty()) {
		PCB Temp = *this->scheduling_List.begin();
		cout << *timeIter << " ~ ";
		timeIter++;
		cout << *timeIter << " : " << Temp.getName() << endl;
		this->scheduling_List.pop_front();
	}
	cout << endl << "FCFS Average Waiting Time :" << this->averageWaitTime << endl << endl;
}

void FCFS::add(PCB pcb)
{
	this->pcbList.push_back(pcb);
	this->size++;
}

PCB& FCFS::at(int i)
{
	list<PCB>::iterator iter;
	iter = this->pcbList.begin();
	for (int index = 0; index < i; index++)
		iter++;

	return *iter;
}
