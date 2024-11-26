#include "SimHeader.h"

void CPU::jobProcess(Queue& low, Queue& high, Queue& done) {

	if (!isBusy) {
		if (high.getHead()) {
			currentJob = high.getHead()->job;
			high.popJob();
			runTime++;
			isBusy = true;
		}
		else if (low.getHead()) {
			currentJob = low.getHead()->job;
			low.popJob();
			runTime++;
			isBusy = true;
		}
		else {
			idleTime++;
		}
		
	}
	else {
		if (high.getHead() && currentJob.type != 'D') {
			Job j = { currentJob.type, currentJob.arriveTime, currentJob.processTime, currentJob.remainingTime , currentJob.totalJobNum, currentJob.jobTypeNum};
			currentJob = high.getHead()->job;
			high.popJob();
			high.addToFront(new Node(j));
			runTime++;
		}
		else if(currentJob.remainingTime > 1){
			currentJob.remainingTime--;
			runTime++;
		}
		else {
			Job j = { currentJob.type, currentJob.arriveTime, currentJob.processTime, currentJob.remainingTime , currentJob.totalJobNum, currentJob.jobTypeNum };
			done.addJob(new Node(j));
			currentJob = Job();
			runTime++;
			isBusy = false;
		}
	}
}