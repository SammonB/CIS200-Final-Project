#include "SimHeader.h"

void CPU::jobProcess(const int& curTime, const int& countIndex, Queue& low, Queue& high, Queue& done) {

	if (!isBusy) {
		if (high.getHead()) {
			currentJob = high.getHead()->job;
			high.popJob();
			writeToLog("Time " + to_string(curTime) + ": Begin Processing Job: " + to_string(currentJob.totalJobNum) + ", Type " + currentJob.type + " in CPU " + to_string(countIndex) + '\n');
			runTime++;
			totalRunTime++;
			idleTime = 0;
			isBusy = true;
		}
		else if (low.getHead()) {
			currentJob = low.getHead()->job;
			low.popJob();
			writeToLog("Time " + to_string(curTime) + ": Begin Processing Job: " + to_string(currentJob.totalJobNum) + ", Type " + currentJob.type + " in CPU " + to_string(countIndex) + '\n');
			runTime++;
			totalRunTime++;
			idleTime = 0;
			isBusy = true;
		}
		else {
			idleTime++;
			totalIdleTime++;
		}
		
	}
	else {
		if (high.getHead() && currentJob.type != 'D') {
			writeToLog("Time " + to_string(curTime) + ": Job Ejected: Job: " + to_string(currentJob.totalJobNum) + ", Type " + currentJob.type + ", Remaining Time: " + to_string(currentJob.remainingTime) + ", in CPU " + to_string(countIndex) + '\n');
			Job j = { currentJob.type, currentJob.arriveTime, currentJob.processTime, currentJob.remainingTime , currentJob.totalJobNum, currentJob.jobTypeNum};
			currentJob = high.getHead()->job;
			high.popJob();
			high.addToFront(new Node(j));
			runTime++;
			totalRunTime++;
		}
		else if(currentJob.remainingTime > 1){
			currentJob.remainingTime--;
			runTime++;
			totalRunTime++;
		}
		else {
			Job j = { currentJob.type, currentJob.arriveTime, currentJob.processTime, currentJob.remainingTime , currentJob.totalJobNum, currentJob.jobTypeNum };
			done.addJob(new Node(j));
			writeToLog("Time " + to_string(curTime) + ": Completed processing job: " + to_string(currentJob.totalJobNum) + ", Type " + currentJob.type + ", in CPU " + to_string(countIndex) + '\n');
			currentJob = Job();
			runTime = 0;
			totalRunTime++;
			isBusy = false;
		}
	}
}