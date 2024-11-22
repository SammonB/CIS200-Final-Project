#include "SimHeader.h"

void initializeJobs(Queue& q) {
	fstream file("jobs.txt");
	file.ignore(1000, '\n');
	char a;
	int b, c;
	while (file >> a >> b >> c) {
		Job j = { a, b, c };
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

void handleMove(int curTime, Queue& low, Queue& high, Queue& event) {
	while (event.getHead()->job.arriveTime == curTime) {
		if (event.getHead()->job.type == 'D') {
			moveJob(high, event);
		}
		else {
			moveJob(low, event);
		}
	}
}
