#include "SimHeader.h"


int main() {

	Queue eventQueue;
	Queue lowQueue;
	Queue hiQueue;
	Queue doneQueue;
	int cpuCount;
	int countIndex;
	int totalRunTime = 0;
	int totalIdleTime = 0;
	int lowQueueSizeCount = 0;
	int hiQueueSizeCount = 0;
	int totalWaitTime = 0;
	int waitAverageTotal = 0;
	int aArrived = 0;
	int bArrived = 0;
	int cArrived = 0;
	int dArrived = 0;
	initializeJobs(eventQueue);

	cout << "Enter the number of CPU's to use: ";
	cin >> cpuCount;
	vector<CPU> cpus(cpuCount);

	
	int currentTime = 0;
	const int endTime = 100;
	while (currentTime < endTime) {

		//cout << "Current time: " << currentTime << '\n';
		handleMove(currentTime, lowQueue, hiQueue, eventQueue);
		//cout << "lowQueue:\n";
		//lowQueue.printAll();
		//cout << "hiQueue:\n";
		//hiQueue.printAll();
		if (lowQueue.getHead()) {
			switch (lowQueue.getLast()->job.type) {
			case 'A': {
				aArrived = lowQueue.getLast()->job.jobTypeNum;
				break;
			}
			case 'B': {
				bArrived = lowQueue.getLast()->job.jobTypeNum;
				break;
			}
			case 'C': {
				cArrived = lowQueue.getLast()->job.jobTypeNum;
				break;
			}
			default: {
				break;
			}
			}
		}
		if (hiQueue.getHead()) {
			if (hiQueue.getLast()->job.type == 'D') {
				dArrived = hiQueue.getLast()->job.jobTypeNum;
			}
		}



		countIndex = 1;
		for (auto& i : cpus) {
			i.jobProcess(lowQueue, hiQueue, doneQueue);
			//cout << "CPU " << countIndex << ": Job Type: " << i.currentJob.type << ". Remaining Time: " << i.currentJob.remainingTime << '\n';
			countIndex++;
		}

		
		
		if (lowQueue.getHead()) {
			lowQueue.addWaitTime();
			totalWaitTime += lowQueue.tallyWaitTime();
			waitAverageTotal += lowQueue.tallyWaitTime() / lowQueue.getSize();
			lowQueueSizeCount += lowQueue.getSize();
		}
		if (hiQueue.getHead()) {
			hiQueue.addWaitTime();
			totalWaitTime += hiQueue.tallyWaitTime();
			waitAverageTotal += hiQueue.tallyWaitTime() / hiQueue.getSize();
			hiQueueSizeCount += hiQueue.getSize();
		}

		
	

		currentTime++;
	}

	cout << "\n//Metrics://\n\n";
	cout << "Number of processors used: " << cpuCount << '\n';
	cout << "Current low-priority queue size: " << lowQueue.getSize() << '\n';
	cout << "Average low-priority queue size: " << (lowQueueSizeCount / endTime) << '\n';
	cout << "Current high-priority queue size: " << hiQueue.getSize() << '\n';
	cout << "Average high-priority queue size: " << (hiQueueSizeCount / endTime) << '\n';
	cout << "Total job time spent in queues: " << totalWaitTime << '\n';
	cout << "Average job time spent in queues: " << (waitAverageTotal / endTime) << '\n';
	cout << "Total type A jobs arrived: " << aArrived << '\n';
	cout << "Total type A jobs completed: " << doneQueue.getJobCount('A') << '\n';
	cout << "Total type B jobs arrived: " << bArrived << '\n';
	cout << "Total type B jobs completed: " << doneQueue.getJobCount('B') << '\n';
	cout << "Total type C jobs arrived: " << cArrived << '\n';
	cout << "Total type C jobs completed: " << doneQueue.getJobCount('C') << '\n';
	cout << "Total type D jobs arrived: " << dArrived << '\n';
	cout << "Total type D jobs completed: " << doneQueue.getJobCount('D') << '\n';
	cout << "Total jobs completed: " << doneQueue.getLast()->job.totalJobNum << '\n';

	
	/*
	countIndex = 1;
	for (const auto& i : cpus) {
		cout << "CPU " << countIndex << " Run Time: " << i.runTime << ", Idle Time: " << i.idleTime << '\n';
		countIndex++;
	}
	*/
	countIndex = 1;
	for (const auto& i : cpus) {
		totalRunTime += i.runTime;
		totalIdleTime += i.idleTime;
	}
	cout << "Total Run Time: " << totalRunTime << '\n';
	cout << "Total Idle Time: " << totalIdleTime << '\n';

	

	return 0;
}