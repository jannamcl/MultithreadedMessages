#ifndef COUNTINGSEMAPHORE_H
#define COUNTINGSEMAPHORE_H

#define WIN32_MEAN_AND_LEAN

#include <windows.h>
#include <queue>
#include <exception>
#include <stdio.h>

#include "Thread.h"

class CountingSemaphore {
public:
	CountingSemaphore(signed int start);
	~CountingSemaphore();
	void P();
	void V();

private:
	// Current count on this semaphore.
	volatile signed int count;
	// Queue of blocked threads
	std::queue<HANDLE>* threadQueue;
};

#endif