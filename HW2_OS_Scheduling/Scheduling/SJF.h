#pragma once
#include "Scheduling.h"

/*
*	preemptive : Burst Time이 더 적은 프로세스가 먼저 수행됨
*	해당 내용 고려해서 PCB 사용할 것
*	Scheduling을 상속
*/
class SJF : public Scheduling
{
private :
	//PCBList의 Arrival Time을 저장하여 구간을 나누는 리스트
	list<float> section;
	//PCB의 BurstTime에 의해 sort하려는 함수
	bool BurstSort(PCB P1, PCB P2) {
		return P1.getBurstTime() < P2.getBurstTime();
	};

	PCB findByName(string name) {
		int i = this->pcbList.size();
		for (int j = 0; j < i; j++)
			if (this->at(j).getName() == name)
				return this->at(i);
	};

	//i번쨰 index의 section값을 리턴
	float sectionAt(int i) {
		list<float>::iterator iter;
		iter = this->section.begin();
		for (int index = 0; index < i; index++)
			iter++;
		return *iter;
	}

	//pcbList를 parameter로 받아서 해당 List 내에서 BurstTime이 가장 작은 PCB를 리턴
	PCB getShortestJob(list<PCB> pcbList);

public : 
	//기본 생성자
	SJF();

	//Scheduling을 진행한다.
	void Schedule();

	//Scheduling을 진행한 이후, Queue를 출력한다.
	void printQueue();

	//PCB를 pcb 리스트에 추가한다.
	void add(PCB pcb);

	//i번째 인덱스의 PCB를 리턴한다.
	PCB& at(int i);

};

