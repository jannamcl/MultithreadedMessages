#include "CountingSemaphore.h"

/**
	Creates a new CountingSemaphore.
	@param start The starting value of this semaphore.
*/
CountingSemaphore::CountingSemaphore(signed int start) {
	if (start < 0) {
		throw new std::invalid_argument("start must be greater than or equal to 0");
	}
	this->count = start;
	this->threadQueue = new std::queue<HANDLE>();
}

/**
	Destroys this CountingSemaphore object.
*/
CountingSemaphore::~CountingSemaphore() {
	delete this->threadQueue;
}

/**
	Wait on this CountingSemaphore. Blocks if needed.
*/
void CountingSemaphore::P() {
	this->count--;
	if (this->count < 0) {
		HANDLE h; 
		DuplicateHandle(GetCurrentProcess(), GetCurrentThread(), GetCurrentProcess(),
			&h, 0, FALSE, DUPLICATE_SAME_ACCESS);
		this->threadQueue->push(h);
		SuspendThread(GetCurrentThread());
	}
}

/**
	Signals this CountingSemaphore.
*/
void CountingSemaphore::V() {
	this->count++;
	if (!(this->threadQueue->empty())) {
		HANDLE h = this->threadQueue->front();
		ResumeThread(h);
		this->threadQueue->pop();
	}
}
