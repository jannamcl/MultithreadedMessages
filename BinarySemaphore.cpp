#include "BinarySemaphore.h"

/**
	Create a new BinarySemaphore.
*/
BinarySemaphore::BinarySemaphore() {
	this->sem = new CountingSemaphore(1);
}

/**
	Delete this BinarySemaphore.
*/
BinarySemaphore::~BinarySemaphore() {
	delete this->sem;
}

/**
	Wait on this semaphore. Block if needed.
*/
void BinarySemaphore::P() {
	this->sem->P();
}

/**
	Signal this semaphore.
*/
void BinarySemaphore::V() {
	this->sem->V();
}