#pragma once
#include "PCB.h"
#include<list>
#include<algorithm>
/*
*	스케줄링 클래스 : 해당 클래스는 FCFS / SJF / RR로 구성된다
*	스케줄링 클래스는 실제로 작동하는 것이 아닌 추상적인 클래스이기 때문에 어떤 함수를 구현할 수 없고, 자식 클래스에 따라서 함수가 달라진다.
*	해당 클래스의 모든 함수는 virltual 함수로 구현된다.
*/
class Scheduling
{
protected : 
	//PCB 목록을 저장하는 리스트
	list<PCB> pcbList;
	//PCBList를 바탕으로 schedule된 내용을 저장하는 리스트
	list<PCB> scheduling_List;
	//Schedule List의 구간을 저장하는 리스트
	list<float> burstTimeSection;
	//평균 averageWaitTime 값을 저장한다.
	float averageWaitTime;
	//BurstTime의 합을 저장
	float totalTime;
	//pcb의 총 개수
	int size;
public :
	Scheduling();

	//Scheduling을 진행한다.
	virtual void Schedule() = 0;

	//Scheduling을 진행한 이후, Queue를 출력한다.
	virtual void printQueue() = 0;

	//PCB를 pcb 리스트에 추가한다.
	virtual void add(PCB pcb) = 0;

	//i번째 인덱스의 PCB를 리턴한다.
	virtual PCB& at(int i) = 0;
};

