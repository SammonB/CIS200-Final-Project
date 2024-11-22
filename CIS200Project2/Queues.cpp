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

/*
void Queue::moveJob(Queue& q) {
	if (!head) {
		head = q.head;
		q.head = q.head->next;
		head->next = nullptr;
	}
	else {
		Node* tempPtr = head;
		while (tempPtr->next) {
			tempPtr = tempPtr->next;
		}
		tempPtr->next = q.head;
		q.head = q.head->next;
		tempPtr->next = nullptr;
	}
}
*/
