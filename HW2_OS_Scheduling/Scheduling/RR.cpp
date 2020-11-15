#include "RR.h"

RR::RR()
{
	this->averageWaitTime = 0;
	this->totalTime = 0;
	this->size = 0;
	this->timeQuantum = 1;
}

RR::RR(float TQ)
{
	this->averageWaitTime = 0;
	this->totalTime = 0;
	this->size = 0;
	this->timeQuantum = TQ;
}

void RR::Schedule()
{
	//초기화
	this->scheduling_List.clear();
	this->burstTimeSection.clear();
	this->burstTimeSection.push_back(0);
	this->lastArriveTime = this->pcbList.back().getArrivalTime();

	//ogSize를 설정한다.
	int ogSize = this->pcbList.size();

	//Iterator : this->pcbList
	list<PCB>::iterator iter = this->pcbList.begin();
	//iterBeforeAll, temp, tempIter, get = 아직 모든 프로세스가 들어오기 전의 pcbList Iterator
	list<PCB> temp;
	list<PCB>::iterator  tempIter, get, iterBeforeAll = this->pcbList.begin();
	while (!this->pcbList.empty()) {
		//total Time < arrival Time 전까지는 해당 시간 내에 도착한 PCB들만 Schedule을 진행한다.
		if (this->totalTime < this->lastArriveTime) {
			iterBeforeAll = this->pcbList.begin();
			
			while (iterBeforeAll->getArrivalTime() <= this->totalTime) {
				temp.push_back(*iterBeforeAll);
				iterBeforeAll++;
			}
			
			int tempSize = 0, searchSize = temp.size();
			//get : temp List에서 가장 작은 finish Time을 가진 Iterator
			while (!temp.empty()) {
				tempIter = temp.begin();
				get = temp.begin();
				tempSize = temp.size();

				for (int i = 0; i < tempSize; i++) {
					if (tempIter->getFinishTime() <= get->getFinishTime())
						get = tempIter;
					tempIter++;
				}

				//get과 같은 PCB를 this->pcbList에서 찾아서 iterBeforeAll에 대입
				iterBeforeAll = this->pcbList.begin();
				for (int i = 0; i < searchSize; i++) {
					if (iterBeforeAll->getName() == get->getName())
						break;
					iterBeforeAll++;
				}
				
				this->ScheduleRR(iterBeforeAll);
		
				temp.erase(get);
			}

		}
		else {
			//iterator는 finish time이 가장 짧은, 즉 readyQueue의 제일 앞의 원소로 설정한다.
			iter = this->findSmallFinish();
			this->ScheduleRR(iter);
		}
	}

	this->averageWaitTime /= ogSize;
}

void RR::printQueue()
{
	list<float>::iterator timeIter = this->burstTimeSection.begin();
	cout << endl << "RR Schedule List : " << endl;
	//schedule list와 average wait time을 출력한다.
	while (!this->scheduling_List.empty()) {
		PCB Temp = *this->scheduling_List.begin();
		cout << *timeIter << " ~ ";
		timeIter++;
		cout << *timeIter << " : " << Temp.getName() << endl;
		this->scheduling_List.pop_front();
	}
	cout << endl << "RR Average Waiting Time :" << this->averageWaitTime << endl << endl;
}

void RR::add(PCB pcb)
{
	this->pcbList.push_back(pcb);
	this->size++;
}

PCB& RR::at(int i)
{
	list<PCB>::iterator iter;
	iter = this->pcbList.begin();
	for (int index = 0; index < i; index++)
		iter++;

	return *iter;
}