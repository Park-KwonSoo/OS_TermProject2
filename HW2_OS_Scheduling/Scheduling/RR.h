#pragma once
#include "Scheduling.h"

/*
*	Time Quantum  사용해서 Scheduling 구현
*	Time Quantum  = 3
*	Scheduling을 상속
*/
class RR : public Scheduling
{
private :
	//time quantum
	float timeQuantum;
	
	//마지막으로 pcb가 도착하는 시간
	float lastArriveTime;
	
	//현재 pcbList에서 가장 finish타임이 짧은 pcbList를 리턴
	list<PCB>::iterator findSmallFinish() {
		list<PCB>::iterator get, iter;
		get = this->pcbList.begin();
		iter = this->pcbList.begin();

		for (int i = 0; i < this->size; i++) {
			if (iter->getFinishTime() < get->getFinishTime())
				get = iter;
			iter++;
		}

		return get;
	};

	void ScheduleRR(list<PCB>::iterator iter) {
		if (iter->getBurstTime() >= this->timeQuantum) {
			//Iterator의 남은 burstTIme을 time Qunatum만큼 감소
			iter->reduceBurstTime(this->timeQuantum);

			//만약 Iterator가 wait를 한다면(=진행중인 시간이 arrival time보다 더 뒤에 있을 경우)
			//wait한 시간만큼 더해준다
			if (this->totalTime - this->timeQuantum > iter->getArrivalTime())
				this->averageWaitTime += this->totalTime - iter->getFinishTime();
			
			//진행중인 시간을 Time Quantum만큼 증가시킨다.
			this->totalTime += this->timeQuantum;

			//Iterator의 프로세스가 어느 지점에서 끝났는지 설정한다.
			iter->setFinishTime(this->totalTime);

			this->scheduling_List.push_back(*iter);
			this->burstTimeSection.push_back(this->totalTime);
		}
		else if (iter->getBurstTime()) {
			float temp = iter->getBurstTime();
			iter->reduceBurstTime(temp);

			if (this->totalTime - this->timeQuantum > iter->getArrivalTime())
				this->averageWaitTime += this->totalTime - iter->getFinishTime();

			this->totalTime += temp;

			iter->setFinishTime(this->totalTime);
			this->scheduling_List.push_back(*iter);
			this->burstTimeSection.push_back(this->totalTime);
		}
		else {
			this->pcbList.erase(iter);
			this->size--;
		}
	};

public :
	//기본 생성자
	RR();
	
	//Time Quantum 생성자
	RR(float TQ);

	//Scheduling을 진행한다.
	void Schedule();

	//Scheduling을 진행한 이후, Queue를 출력한다.
	void printQueue();

	//PCB를 pcb 리스트에 추가한다.
	void add(PCB pcb);

	//i번째 인덱스의 PCB를 리턴한다.
	PCB& at(int i);
};

