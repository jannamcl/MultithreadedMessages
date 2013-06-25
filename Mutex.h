#ifndef MUTEX_H
#define MUTEX_H

#include "BinarySemaphore.h"

class Mutex : BinarySemaphore {

public:
	Mutex();
	~Mutex();
	void lock();
	void unlock();

private:
	BinarySemaphore* sem;
};

#endif