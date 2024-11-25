#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

struct Job {
	char type;
	int arriveTime;
	int processTime;
	int remainingTime;
	int totalJobNum;
	int jobTypeNum;
	int priority;
	int startTime;
	int enterTime;
	int leaveTime;
	bool interrupted;

	Job(char typ = ' ', int arvT = 0, int prcT = 0, int rmnT = 0, int tJobNum = 0, int jTyNum = 0, int prio = 0, int stT = 0, int enT = 0, int lvT = 0, bool interr = false) {
		type = typ;
		arriveTime = arvT;
		processTime = prcT;
		remainingTime = rmnT;
		totalJobNum = tJobNum;
		jobTypeNum = jTyNum;
		priority = prio;
		startTime = stT;
		enterTime = enT;
		leaveTime = lvT;
		interrupted = interr;
	}
};

struct Node {
	Node* next;
	Job job;
	Node(Job j) { job = j; next = nullptr; }
};

class Queue {
	Node* head;
public:
	Queue();
	~Queue();
	Node* getHead() const { return head; }
	void setHead(Node* newHead) { head = newHead; }
	void addJob(Node* newNode);
	void addToFront(Node* newNode);
	void popJob();
	void printAll();
};

struct CPU {
	bool isBusy = false;
	Job currentJob;
	int runTime = 0;
	int idleTime = 0;
	void jobProcess(Queue& low, Queue& high);
};

void initializeJobs(Queue& q);
void moveJob(Queue& to, Queue& from);
void handleMove(const int& curTime, Queue& low, Queue& high, Queue& event);
//void assignJob(const int& curTime, Queue& low, Queue& high, CPU& cpu);