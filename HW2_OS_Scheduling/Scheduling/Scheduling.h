#pragma once
#include "PCB.h"
#include<list>
#include<algorithm>
/*
*	�����ٸ� Ŭ���� : �ش� Ŭ������ FCFS / SJF / RR�� �����ȴ�
*	�����ٸ� Ŭ������ ������ �۵��ϴ� ���� �ƴ� �߻����� Ŭ�����̱� ������ � �Լ��� ������ �� ����, �ڽ� Ŭ������ ���� �Լ��� �޶�����.
*	�ش� Ŭ������ ��� �Լ��� virltual �Լ��� �����ȴ�.
*/
class Scheduling
{
protected : 
	//PCB ����� �����ϴ� ����Ʈ
	list<PCB> pcbList;
	//PCBList�� �������� schedule�� ������ �����ϴ� ����Ʈ
	list<PCB> scheduling_List;
	//Schedule List�� ������ �����ϴ� ����Ʈ
	list<float> burstTimeSection;
	//��� averageWaitTime ���� �����Ѵ�.
	float averageWaitTime;
	//BurstTime�� ���� ����
	float totalTime;
	//pcb�� �� ����
	int size;
public :
	Scheduling();

	//Scheduling�� �����Ѵ�.
	virtual void Schedule() = 0;

	//Scheduling�� ������ ����, Queue�� ����Ѵ�.
	virtual void printQueue() = 0;

	//PCB�� pcb ����Ʈ�� �߰��Ѵ�.
	virtual void add(PCB pcb) = 0;

	//i��° �ε����� PCB�� �����Ѵ�.
	virtual PCB& at(int i) = 0;
};

