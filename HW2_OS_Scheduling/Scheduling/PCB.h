#pragma once
#include <iostream>
#include <string>
using namespace std;

/*
*	PCB를 구현하기 위한 자료구조이다
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

	//PCB의 BurstTime을 parameter만큼 감소
	void reduceBurstTime(float reduce);

	//PCB의 BurstTime을 parameter만큼 증가
	void increaseWaitTime(float increase);

	//PCB의 정보를 출력하는 함수
	void printPCB();

	//PCB의 Finished Time을 세팅하는 함수
	void setFinishTime(float finishTime);

	//PCB의 이름을 리턴하는 함수
	string getName();

	//PCB의 BurstTime을 리턴하는 함수
	float getBurstTime();

	//PCB의 ArrivalTime을 리턴하는 함수
	float getArrivalTime();

	//PCB의 waitTime을 리턴하는 함수
	float getWaitTime();

	//PCB의 finishTime을 리턴하는 함수
	float getFinishTime();

	//PCB가 전부 실행되었으면 false 리턴, 아직 작업이 남아있다면 true 리턴
	bool isBurst();
};

