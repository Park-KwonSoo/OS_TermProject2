#pragma once
#include "Scheduling.h"

/*
*	preemptive : Burst Time�� �� ���� ���μ����� ���� �����
*	�ش� ���� ����ؼ� PCB ����� ��
*	Scheduling�� ���
*/
class SJF : public Scheduling
{
private :
	//PCBList�� Arrival Time�� �����Ͽ� ������ ������ ����Ʈ
	list<float> section;
	//PCB�� BurstTime�� ���� sort�Ϸ��� �Լ�
	bool BurstSort(PCB P1, PCB P2) {
		return P1.getBurstTime() < P2.getBurstTime();
	};

	PCB findByName(string name) {
		int i = this->pcbList.size();
		for (int j = 0; j < i; j++)
			if (this->at(j).getName() == name)
				return this->at(i);
	};

	//i���� index�� section���� ����
	float sectionAt(int i) {
		list<float>::iterator iter;
		iter = this->section.begin();
		for (int index = 0; index < i; index++)
			iter++;
		return *iter;
	}

	//pcbList�� parameter�� �޾Ƽ� �ش� List ������ BurstTime�� ���� ���� PCB�� ����
	PCB getShortestJob(list<PCB> pcbList);

public : 
	//�⺻ ������
	SJF();

	//Scheduling�� �����Ѵ�.
	void Schedule();

	//Scheduling�� ������ ����, Queue�� ����Ѵ�.
	void printQueue();

	//PCB�� pcb ����Ʈ�� �߰��Ѵ�.
	void add(PCB pcb);

	//i��° �ε����� PCB�� �����Ѵ�.
	PCB& at(int i);

};

