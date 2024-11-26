#include "SimHeader.h"

Queue::Queue() {
	head = nullptr;
}

Queue::~Queue() {
	Node* tempPtr = head;
	while (tempPtr) {
		Node* nextPtr = tempPtr->next;
		delete tempPtr;
		tempPtr = nextPtr;
	}
	head = nullptr;
}

void Queue::addJob(Node* newNode) {
	if (!head) {
		head = newNode;
		newNode->next = nullptr;
	}
	else {
		Node* tempPtr = head;
		while (tempPtr->next) {
			tempPtr = tempPtr->next;
		}
		tempPtr->next = newNode;
		newNode->next = nullptr;
	}
}

void Queue::addToFront(Node* newNode) {
	if (!head) {
		head = newNode;
		newNode->next = nullptr;
	}
	else {
		newNode->next = head;
		head = newNode;
	}
}

void Queue::popJob() {
	Node* tempPtr = head;
	head = head->next;
	delete tempPtr;
}

void Queue::printAll() {
	Node* tempPtr = head;

	while (tempPtr) {
		cout << "Type: " << tempPtr->job.type << ", ArriveTime: " << tempPtr->job.arriveTime << ", Process Time: " << tempPtr->job.processTime << '\n';
		tempPtr = tempPtr->next;
	}
}

int Queue::getSize() {
	Node* tempPtr = head;
	int count = 0;
	while (tempPtr) {
		tempPtr = tempPtr->next;
		count++;
	}
	return count;
}

void Queue::addWaitTime() {
	Node* tempPtr = head;
	while (tempPtr) {
		tempPtr->job.waitTime++;
		tempPtr = tempPtr->next;
	}
}

int Queue::tallyWaitTime() {
	Node* tempPtr = head;
	int count = 0;
	while (tempPtr) {
		count += tempPtr->job.waitTime;
		tempPtr = tempPtr->next;
	}
	return count;
}

int Queue::getJobCount(const char c) {
	Node* tempPtr = head;
	int count = 0;
	while (tempPtr) {
		if (tempPtr->job.type == c) {
			count = tempPtr->job.jobTypeNum;
		}
		tempPtr = tempPtr->next;
	}
	return count;
}

Node* Queue::getLast() {
	Node* tempPtr = head;
	if (head) {
		while (tempPtr->next) {
			tempPtr = tempPtr->next;
		}
	}
	return tempPtr;
}