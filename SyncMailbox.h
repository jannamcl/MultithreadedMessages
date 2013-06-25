#ifndef SYNCMAILBOX_H
#define SYNCMAILBOX_H

#include "Mutex.h"

class SyncMailbox { //passes messages

private:
	CountingSemaphore* sent; //semaphore for controlling the sending of messages
	CountingSemaphore* received; //semaphore for controlling the receiving of messages
	Mutex* mutex_receiving; //locks the receive() function
	Mutex* mutex_sending; //locks the send() function
	void* msg; //message being passed

public:
	SyncMailbox();
	~SyncMailbox();
	void send(void* out);
	void resend();
	void* receive();

};

#endif