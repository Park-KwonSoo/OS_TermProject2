#include "FCFS.h"
#include "SJF.h"
#include "RR.h"

//scheduler에 process를 넣는다.
void add_function(Scheduling* S, PCB P[], int n);

int main()
{
	int timeQuantum = 3;	//RR에 사용할 Time Quantum

	Scheduling* fcfs = new FCFS;
	Scheduling* sjf = new SJF;
	Scheduling* rr = new RR(timeQuantum);	

	PCB P1("P1", 0, 10), P2("P2", 3, 12), P3("P3", 7, 4), P4("P4", 10, 6), P5("P5", 14, 8), P6("P6", 15, 7);
	PCB P[] = { P1, P2, P3, P4 ,P5, P6 };

	add_function(fcfs, P, 6);
	add_function(sjf, P, 6);
	add_function(rr, P, 6);
	
	fcfs->Schedule();
	fcfs->printQueue();

	sjf->Schedule();
	sjf->printQueue();

	rr->Schedule();
	rr->printQueue();
}

void add_function(Scheduling* S, PCB P[], int n) {
	for (int i = 0; i < n; i++)
		S->add(P[i]);
}