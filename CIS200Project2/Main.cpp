#include "SimHeader.h"


int main() {

	fstream logFile("Log.txt");

	Queue eventQueue;
	Queue lowQueue;
	Queue hiQueue;
	Queue doneQueue;

	int currentTime = 0;
	const int initialTime = 500;
	const int endTime = 10000;
	int cpuCount;
	int countIndex;
	int totalRunTime = 0;
	int totalIdleTime = 0;
	int lowQueueSizeCount = 0;
	int hiQueueSizeCount = 0;
	long totalWaitTime = 0;
	int waitAverageTotal = 0;
	int aArrived = 0;
	int bArrived = 0;
	int cArrived = 0;
	int dArrived = 0;
	initializeJobs(eventQueue);

	cout << "Enter the number of CPU's to use: ";
	cin >> cpuCount;
	vector<CPU> cpus(cpuCount);

	
	while (currentTime < initialTime) {

		handleMove(currentTime, lowQueue, hiQueue, eventQueue);

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
			i.jobProcess(currentTime, countIndex, lowQueue, hiQueue, doneQueue);
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

		writeToLog("Time " + to_string(currentTime) + ": Low Priority Queue Size: " + to_string(lowQueue.getSize()) + ", ");
		writeToLog("High Priority Queue Size: " + to_string(hiQueue.getSize()) + "; ");
		countIndex = 1;
		for (auto& i : cpus) {
			if (i.isBusy) {
				writeToLog("CPU " + to_string(countIndex) + " run time: " + to_string(i.runTime) + "; ");
			}
			else {
				writeToLog("CPU " + to_string(countIndex) + " idle time: " + to_string(i.idleTime) + "; ");
			}
			countIndex++;
		}
		writeToLog("\n");

		currentTime++;
	}

	cout << "\n//Metrics://\n\n";
	cout << "Number of processors used: " << cpuCount << '\n';
	cout << "Current low-priority queue size: " << lowQueue.getSize() << '\n';
	cout << "Average low-priority queue size: " << (lowQueueSizeCount / initialTime) << '\n';
	cout << "Current high-priority queue size: " << hiQueue.getSize() << '\n';
	cout << "Average high-priority queue size: " << (hiQueueSizeCount / initialTime) << '\n';
	cout << "Total job time spent in queues: " << totalWaitTime << '\n';
	cout << "Average job time spent in queues: " << (waitAverageTotal / initialTime) << '\n';
	cout << "Total type A jobs arrived: " << aArrived << '\n';
	cout << "Total type A jobs completed: " << doneQueue.getJobCount('A') << '\n';
	cout << "Total type B jobs arrived: " << bArrived + 1 << '\n';
	cout << "Total type B jobs completed: " << doneQueue.getJobCount('B') << '\n';
	cout << "Total type C jobs arrived: " << cArrived << '\n';
	cout << "Total type C jobs completed: " << doneQueue.getJobCount('C') << '\n';
	cout << "Total type D jobs arrived: " << dArrived << '\n';
	cout << "Total type D jobs completed: " << doneQueue.getJobCount('D') << '\n';
	cout << "Total jobs completed: " << doneQueue.getLast()->job.totalJobNum << '\n';

	

	countIndex = 1;
	for (const auto& i : cpus) {
		totalRunTime += i.runTime;
		totalIdleTime += i.idleTime;
	}
	cout << "Total Run Time: " << totalRunTime << '\n';
	cout << "Total Idle Time: " << totalIdleTime << '\n';
	countIndex = 1;
	totalRunTime = 0;
	totalIdleTime = 0;

	while (currentTime < endTime) {

		handleMove(currentTime, lowQueue, hiQueue, eventQueue);

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
			i.jobProcess(currentTime, countIndex, lowQueue, hiQueue, doneQueue);
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

		writeToLog("Time " + to_string(currentTime) + ": Low Priority Queue Size: " + to_string(lowQueue.getSize()) + ", ");
		writeToLog("High Priority Queue Size: " + to_string(hiQueue.getSize()) + "; ");
		countIndex = 1;
		for (auto& i : cpus) {
			if (i.isBusy) {
				writeToLog("CPU " + to_string(countIndex) + " run time: " + to_string(i.runTime) + "; ");
			}
			else {
				writeToLog("CPU " + to_string(countIndex) + " idle time: " + to_string(i.idleTime) + "; ");
			}
			countIndex++;
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
	cout << "Total type B jobs arrived: " << bArrived + 1 << '\n';
	cout << "Total type B jobs completed: " << doneQueue.getJobCount('B') << '\n';
	cout << "Total type C jobs arrived: " << cArrived << '\n';
	cout << "Total type C jobs completed: " << doneQueue.getJobCount('C') << '\n';
	cout << "Total type D jobs arrived: " << dArrived << '\n';
	cout << "Total type D jobs completed: " << doneQueue.getJobCount('D') << '\n';
	cout << "Total jobs completed: " << doneQueue.getLast()->job.totalJobNum << '\n';



	countIndex = 1;
	for (const auto& i : cpus) {
		totalRunTime += i.totalRunTime;
		totalIdleTime += i.totalIdleTime;
	}
	cout << "Total Run Time: " << totalRunTime << '\n';
	cout << "Total Idle Time: " << totalIdleTime << '\n';


	logFile.close();
	return 0;
}