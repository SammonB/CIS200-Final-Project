#include "SimHeader.h"

/*
every time instance:
	readjob searches for jobs arriving at that time and loads them into the queue




*/



int main() {

	Queue eventQueue;
	Queue lowQueue;
	Queue hiQueue;
	initializeJobs(eventQueue);
	

	//this_thread::sleep_for(chrono::seconds(1));

	
	int currentTime = 0;
	const int endTime = 100;
	while (currentTime <= endTime) {

		cout << "Current time: " << currentTime << '\n';
		handleMove(currentTime, lowQueue, hiQueue, eventQueue);
		cout << "lowQueue:\n";
		lowQueue.printAll();
		cout << "hiQueue:\n";
		hiQueue.printAll();

		//this_thread::sleep_for(chrono::seconds(1));
		currentTime++;
	}
	
	

	return 0;
}