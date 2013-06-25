#ifndef BINARYSEMAPHORE_H
#define BINARYSEMAPHORE_H

#include "CountingSemaphore.h"

class BinarySemaphore {
public:
	BinarySemaphore();
	~BinarySemaphore();
	void P();
	void V();

private:
	CountingSemaphore* sem;
};

#endif