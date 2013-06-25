#include "Mutex.h"

/**
	Creates a new Mutex.
*/
Mutex::Mutex() {
	this->sem = new BinarySemaphore();
}

/**
	Destroys this Mutex object.
*/
Mutex::~Mutex() {
	delete this->sem;
}

/**
	Requests a lock on this mutex. Blocks until it can be acquired.
*/
void Mutex::lock() {
	this->sem->P();
}

/**
	Releases the lock on this mutex.
*/
void Mutex::unlock() {
	this->sem->V();
}