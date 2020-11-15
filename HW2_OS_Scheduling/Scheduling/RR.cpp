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
	//�ʱ�ȭ
	this->scheduling_List.clear();
	this->burstTimeSection.clear();
	this->burstTimeSection.push_back(0);
	this->lastArriveTime = this->pcbList.back().getArrivalTime();

	//ogSize�� �����Ѵ�.
	int ogSize = this->pcbList.size();

	//Iterator : this->pcbList
	list<PCB>::iterator iter = this->pcbList.begin();
	//iterBeforeAll, temp, tempIter, get = ���� ��� ���μ����� ������ ���� pcbList Iterator
	list<PCB> temp;
	list<PCB>::iterator  tempIter, get, iterBeforeAll = this->pcbList.begin();
	while (!this->pcbList.empty()) {
		//total Time < arrival Time �������� �ش� �ð� ���� ������ PCB�鸸 Schedule�� �����Ѵ�.
		if (this->totalTime < this->lastArriveTime) {
			iterBeforeAll = this->pcbList.begin();
			
			while (iterBeforeAll->getArrivalTime() <= this->totalTime) {
				temp.push_back(*iterBeforeAll);
				iterBeforeAll++;
			}
			
			int tempSize = 0, searchSize = temp.size();
			//get : temp List���� ���� ���� finish Time�� ���� Iterator
			while (!temp.empty()) {
				tempIter = temp.begin();
				get = temp.begin();
				tempSize = temp.size();

				for (int i = 0; i < tempSize; i++) {
					if (tempIter->getFinishTime() <= get->getFinishTime())
						get = tempIter;
					tempIter++;
				}

				//get�� ���� PCB�� this->pcbList���� ã�Ƽ� iterBeforeAll�� ����
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
			//iterator�� finish time�� ���� ª��, �� readyQueue�� ���� ���� ���ҷ� �����Ѵ�.
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
	//schedule list�� average wait time�� ����Ѵ�.
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