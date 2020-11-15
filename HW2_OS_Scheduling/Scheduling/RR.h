#pragma once
#include "Scheduling.h"

/*
*	Time Quantum  ����ؼ� Scheduling ����
*	Time Quantum  = 3
*	Scheduling�� ���
*/
class RR : public Scheduling
{
private :
	//time quantum
	float timeQuantum;
	
	//���������� pcb�� �����ϴ� �ð�
	float lastArriveTime;
	
	//���� pcbList���� ���� finishŸ���� ª�� pcbList�� ����
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
			//Iterator�� ���� burstTIme�� time Qunatum��ŭ ����
			iter->reduceBurstTime(this->timeQuantum);

			//���� Iterator�� wait�� �Ѵٸ�(=�������� �ð��� arrival time���� �� �ڿ� ���� ���)
			//wait�� �ð���ŭ �����ش�
			if (this->totalTime - this->timeQuantum > iter->getArrivalTime())
				this->averageWaitTime += this->totalTime - iter->getFinishTime();
			
			//�������� �ð��� Time Quantum��ŭ ������Ų��.
			this->totalTime += this->timeQuantum;

			//Iterator�� ���μ����� ��� �������� �������� �����Ѵ�.
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
	//�⺻ ������
	RR();
	
	//Time Quantum ������
	RR(float TQ);

	//Scheduling�� �����Ѵ�.
	void Schedule();

	//Scheduling�� ������ ����, Queue�� ����Ѵ�.
	void printQueue();

	//PCB�� pcb ����Ʈ�� �߰��Ѵ�.
	void add(PCB pcb);

	//i��° �ε����� PCB�� �����Ѵ�.
	PCB& at(int i);
};

