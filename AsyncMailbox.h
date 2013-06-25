#ifndef ASYNCMAILBOX_H
#define ASYNCMAILBOX_H

#define CAPACITY 100

#include <exception>
#include "Mutex.h"

class AsyncMailbox {
private:
	// Message buffer
	void* messages[CAPACITY];
	// Is a message available?
	CountingSemaphore* messageAvailable;
	// Is a slot available?
	CountingSemaphore* slotAvailable;
	// Control access to send() and receive().
	Mutex* senderMutex;
	Mutex* receiverMutex;
	int in; 
	int out;

public:
	AsyncMailbox();
	~AsyncMailbox();
	void send(void* msg);
	void resend();
	void* receive();
};

#endif