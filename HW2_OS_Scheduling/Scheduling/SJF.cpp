#include "SJF.h"

SJF::SJF()
{
	this->averageWaitTime = 0;
	this->totalTime = 0;
	this->size = 0;
}

void SJF::Schedule()
{
	//���� ������ ����Ʈ �ʱ�ȭ
	this->scheduling_List.clear();
	this->burstTimeSection.clear();
	this->burstTimeSection.push_back(0);

	list<PCB>::iterator iter;
	iter = this->pcbList.begin();

	//section�� arrival Ÿ���� �Ҵ�
	for (int i = 0; i < this->size; i++) {
		this->section.push_back(iter->getArrivalTime());
		iter++;
	}

	bool isMix = false;	//section ������ �ƴ� ���ο� section�� �߰��ϸ� true
	int ogSize = this->size; 
	iter = this->pcbList.begin();
	float BurstTime = 0;
	int nowPoint = 0;	//nowPoint : 0 ~ 5
	//process�� ��� ���� ������ �����Ѵ�.
	while (!this->pcbList.empty()) {
		//���� ���μ����� ���� ������ ���̶�� ���� ���μ����� scheduling�� �Ѵ�.
		if (this->totalTime <= this->sectionAt(nowPoint) && nowPoint < ogSize - 1) {
			//tempList�� nowPoint ���̿� �ִ� PCB�� �ְ� �����ٸ��� �����Ѵ�.
			list<PCB> tempList;
			int point = nowPoint;
			if (ogSize != this->size)
				point -= ogSize - this->size;
			if (isMix) {
				point--;
				isMix = false;
			}
			
			for (int i = 0; i <= point; i++)
				tempList.push_back(this->at(i));

			PCB shortest = this->getShortestJob(tempList);
			list<PCB>::iterator tempIter = this->pcbList.begin();	//���� shortest�� Iterator�� burstTime�� ���ҽ�Ű�� ���� iterator
			for (int i = 0; i < nowPoint; i++) {
				if (this->at(i).getName() == shortest.getName())
					break;
				tempIter++;
			}	//iterator = ���� �ð��� �۵��� �� �ִ� PCB �� ���� ª�� shortest BurstTime�� ���� PCB
			
			if (tempIter->getArrivalTime() < this->totalTime)
				if (tempIter->getFinishTime() < this->totalTime)
					tempIter->increaseWaitTime(this->totalTime - tempIter->getFinishTime());
						
			//iterator�� ���� BurstTime�� �������� BurstTime���� ũ�ٸ�, �ش� BurstTime�� �״�� ����
			if (tempIter->getBurstTime() > this->sectionAt(nowPoint + 1) - this->sectionAt(nowPoint)) {
				BurstTime = this->sectionAt(nowPoint + 1) - this->sectionAt(nowPoint);
				tempIter->reduceBurstTime(BurstTime);
				this->scheduling_List.push_back(*tempIter);
				this->totalTime += BurstTime;
				tempIter->setFinishTime(this->totalTime);
			}
			else if (tempIter->getBurstTime() == this->sectionAt(nowPoint + 1) - this->sectionAt(nowPoint)) {
				BurstTime = tempIter->getBurstTime();
				this->totalTime += BurstTime;
				tempIter->setFinishTime(this->totalTime);
				this->scheduling_List.push_back(*tempIter);
				this->averageWaitTime += tempIter->getWaitTime();
				this->pcbList.erase(tempIter);
				this->size--;
			}
			else {
				BurstTime = this->sectionAt(nowPoint + 1) - this->sectionAt(nowPoint);
				this->totalTime += tempIter->getBurstTime();
				tempIter->setFinishTime(this->totalTime);
				BurstTime -= tempIter->getBurstTime();
				this->scheduling_List.push_back(*tempIter);
				this->averageWaitTime += tempIter->getWaitTime();
				this->pcbList.erase(tempIter);
				this->size--;

				list<float>::iterator insertIter = this->section.begin();
				for (int i = 0; i <= nowPoint; i++)
					insertIter++;

				this->section.insert(insertIter, this->totalTime);
				isMix = true;
			}
			nowPoint++;
		}
		else {
			list<PCB>::iterator tempIter = this->pcbList.begin();
			PCB shortest = this->getShortestJob(this->pcbList);
			
			for (int i = 0; i < this->size; i++) {
				if (shortest.getName() == tempIter->getName())
					break;
				tempIter++;
			}

			if(tempIter->getArrivalTime() < this->totalTime)
				if (tempIter->getFinishTime() < this->totalTime)
					tempIter->increaseWaitTime(this->totalTime - tempIter->getFinishTime());


			this->scheduling_List.push_back(*tempIter);
			this->totalTime += tempIter->getBurstTime();
			this->averageWaitTime += tempIter->getWaitTime();
			this->pcbList.erase(tempIter);
			this->size--;
		}

		this->burstTimeSection.push_back(this->totalTime);
	}

	this->averageWaitTime /= ogSize;

}

void SJF::printQueue()
{
	list<PCB>::iterator temp;
	list<float>::iterator timeIter = this->burstTimeSection.begin();
	cout << endl << "SJF Schedule List :" << endl;
	while (!this->scheduling_List.empty()) {
		temp = this->scheduling_List.begin();
		cout << *timeIter << " ~ ";
		timeIter++;
		cout << *timeIter << " : " << temp->getName() << endl;
		this->scheduling_List.pop_front();
	}
	cout << endl << "SJF Average Waiting Time : " << this->averageWaitTime << endl << endl;
}

void SJF::add(PCB pcb)
{
	this->pcbList.push_back(pcb);
	this->size++;
}

PCB& SJF::at(int i)
{
	list<PCB>::iterator iter;
	iter = this->pcbList.begin();
	for (int index = 0; index < i; index++)
		iter++;

	return *iter;
}

PCB SJF::getShortestJob(list<PCB> pcbList)
{
	list<PCB>::iterator iter;
	PCB temp = *pcbList.begin();
	while (!pcbList.empty()) {
		iter = pcbList.begin();
		if (iter->getBurstTime() < temp.getBurstTime())
			temp = *iter;

		pcbList.pop_front();
	}

	return temp;
}