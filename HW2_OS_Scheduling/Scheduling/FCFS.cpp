#include "FCFS.h"

FCFS::FCFS()
{
	this->averageWaitTime = 0;
	this->totalTime = 0;
	this->size = 0;
}

void FCFS::Schedule()
{
	//shceduling_List 초기화
	this->scheduling_List.clear();
	this->burstTimeSection.clear();
	this->burstTimeSection.push_back(0);

	int ogSize = this->size;
	while (!this->pcbList.empty()) {
		//pcbList의 제일 앞에 있는 PCB를 schedule list에 삽입
		PCB Temp = *this->pcbList.begin();
		this->scheduling_List.push_back(Temp);

		//만약 arrival time이 지났는데도 작업이 진행하고 있다면 waitingtime을 추가
		if (Temp.getArrivalTime() < this->totalTime)
			Temp.increaseWaitTime(this->totalTime - Temp.getArrivalTime());
		this->totalTime += Temp.getBurstTime();
		this->burstTimeSection.push_back(this->totalTime);

		//작업 끝난 PCB는 pcbList에서 제거, 제거 전 averageTime에 해당 값 입력
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
	//schedule list와 average wait time을 출력한다.
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
