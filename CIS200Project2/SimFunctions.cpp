#include "SimHeader.h"

void initializeJobs(Queue& q) {
	fstream file("jobs.txt");
	file.ignore(1000, '\n');
	char a;
	int b, c, totalCount = 0, aCount = 0, bCount = 0, cCount = 0, dCount = 0;
	while (file >> a >> b >> c) {
		totalCount++;
		Job j = { a, b, c, c , totalCount};
		switch (a) {
		case 'A':{
			aCount++;
			j.jobTypeNum = aCount;
			break;
		}
		case 'B': {
			bCount++;
			j.jobTypeNum = bCount;
			break;
		}
		case 'C': {
			cCount++;
			j.jobTypeNum = cCount;
			break;
		}
		case 'D': {
			dCount++;
			j.jobTypeNum = dCount;
			break;
		}
		}
		
		q.addJob(new Node(j));
	}
	file.close();
}

void moveJob(Queue& to, Queue& from) {
	Node* movingJob = from.getHead();
	from.setHead(from.getHead()->next);
	movingJob->next = nullptr;

	if (!to.getHead()) {
		to.setHead(movingJob);
	}
	else {
		Node* tempPtr = to.getHead();
		while (tempPtr->next) {
			tempPtr = tempPtr->next;
		}
		tempPtr->next = movingJob;
	}
}

void handleMove(const int& curTime, Queue& low, Queue& high, Queue& event) {
	while (event.getHead() && event.getHead()->job.arriveTime == curTime) {
		writeToLog("Time " + to_string(curTime) + ": Arrival: Overall Jobs: " + to_string(event.getHead()->job.totalJobNum) + ", Type " + event.getHead()->job.type + " jobs: " + to_string(event.getHead()->job.jobTypeNum) + ", Process time: " + to_string(event.getHead()->job.processTime) + '\n');
		if (event.getHead()->job.type == 'D') {
			moveJob(high, event);
		}
		else {
			moveJob(low, event);
		}
	}
}

void writeToLog(const string str) {
	fstream file("Log.txt", ios::app | ios::binary);

	file << str;
}

