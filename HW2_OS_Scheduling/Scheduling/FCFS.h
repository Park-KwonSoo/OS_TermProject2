#pragma once
#include "Scheduling.h"

/*
*	FCFS = First come, first serverd = FIFO = FIrst In First Out = 선입 선출
*	Burst Time에 관계 없이 Process가 실행됨
*	Scheduling을 상속
*/

class FCFS : public Scheduling
{
public :
	//기본 생성자
	FCFS();

	//Scheduling을 진행한다.
	void Schedule();

	//Scheduling을 진행한 이후, Queue를 출력한다.
	void printQueue();

	//PCB를 pcb 리스트에 추가한다.
	void add(PCB pcb);

	//i번째 인덱스의 PCB를 리턴한다.
	PCB& at(int i);
};

