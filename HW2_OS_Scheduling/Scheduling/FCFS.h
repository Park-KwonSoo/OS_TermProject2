#pragma once
#include "Scheduling.h"

/*
*	FCFS = First come, first serverd = FIFO = FIrst In First Out = ���� ����
*	Burst Time�� ���� ���� Process�� �����
*	Scheduling�� ���
*/

class FCFS : public Scheduling
{
public :
	//�⺻ ������
	FCFS();

	//Scheduling�� �����Ѵ�.
	void Schedule();

	//Scheduling�� ������ ����, Queue�� ����Ѵ�.
	void printQueue();

	//PCB�� pcb ����Ʈ�� �߰��Ѵ�.
	void add(PCB pcb);

	//i��° �ε����� PCB�� �����Ѵ�.
	PCB& at(int i);
};

