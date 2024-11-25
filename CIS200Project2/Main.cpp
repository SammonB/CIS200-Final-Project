#include "SimHeader.h"


int main() {

	Queue eventQueue;
	Queue lowQueue;
	Queue hiQueue;
	int cpuCount;
	int countIndex;
	int totalRunTime = 0;
	int totalIdleTime = 0;
	initializeJobs(eventQueue);

	cout << "Enter the number of CPU's to use: ";
	cin >> cpuCount;
	vector<CPU> cpus(cpuCount);

	
	int currentTime = 0;
	const int endTime = 160;
	while (currentTime < endTime) {

		
		cout << "Current time: " << currentTime << '\n';
		handleMove(currentTime, lowQueue, hiQueue, eventQueue);
		cout << "lowQueue:\n";
		lowQueue.printAll();
		cout << "hiQueue:\n";
		hiQueue.printAll();

		countIndex = 1;
		for (auto& i : cpus) {
			i.jobProcess(lowQueue, hiQueue);
			cout << "CPU " << countIndex << ": Job Type: " << i.currentJob.type << ". Remaining Time: " << i.currentJob.remainingTime << '\n';
			countIndex++;
		}

		currentTime++;
	}

	cout << "\n//Statistics//\n\n";
	countIndex = 1;
	for (const auto& i : cpus) {
		cout << "CPU " << countIndex << " Run Time: " << i.runTime << ", Idle Time: " << i.idleTime << '\n';
		countIndex++;
	}
	countIndex = 1;
	for (const auto& i : cpus) {
		totalRunTime += i.runTime;
		totalIdleTime += i.idleTime;
	}

	cout << "\nTotal Run Time: " << totalRunTime << '\n';
	cout << "Total Idle Time: " << totalIdleTime;

	

	return 0;
}