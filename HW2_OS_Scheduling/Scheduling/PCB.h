#pragma once
#include <iostream>
#include <string>
using namespace std;

/*
*	PCB�� �����ϱ� ���� �ڷᱸ���̴�
*	Private : String PCB Name, int BoudTime, int ArrivalTime, int waitTime
*/
class PCB
{
private :
	string name;
	float BurstTime;
	float ArrivalTime;
	float waitTime;
	float finishTime;
public : 
	PCB();
	PCB(string name, float ArrivalTime, float BurstTime);

	//PCB�� BurstTime�� parameter��ŭ ����
	void reduceBurstTime(float reduce);

	//PCB�� BurstTime�� parameter��ŭ ����
	void increaseWaitTime(float increase);

	//PCB�� ������ ����ϴ� �Լ�
	void printPCB();

	//PCB�� Finished Time�� �����ϴ� �Լ�
	void setFinishTime(float finishTime);

	//PCB�� �̸��� �����ϴ� �Լ�
	string getName();

	//PCB�� BurstTime�� �����ϴ� �Լ�
	float getBurstTime();

	//PCB�� ArrivalTime�� �����ϴ� �Լ�
	float getArrivalTime();

	//PCB�� waitTime�� �����ϴ� �Լ�
	float getWaitTime();

	//PCB�� finishTime�� �����ϴ� �Լ�
	float getFinishTime();

	//PCB�� ���� ����Ǿ����� false ����, ���� �۾��� �����ִٸ� true ����
	bool isBurst();
};

