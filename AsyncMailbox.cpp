#include "AsyncMailbox.h"

/**
	Creates a new AsyncMailbox.
*/
AsyncMailbox::AsyncMailbox() {
	this->messageAvailable = new CountingSemaphore(0);
	this->slotAvailable = new CountingSemaphore(CAPACITY);
	this->senderMutex = new Mutex();
	this->receiverMutex = new Mutex();
	this->in = 0;
	this->out = 0;
}

/**
	Destroys this AsyncMailbox.
*/
AsyncMailbox::~AsyncMailbox() {
	delete this->messageAvailable;
	delete this->slotAvailable;
	delete this->senderMutex;
	delete this->receiverMutex;
}

/**
	Sends a message to this mailbox.
	@param message Pointer to the message object to be sent.
*/
void AsyncMailbox::send(void* message) {
	if (message == NULL) {
		throw new std::exception("asyncMailbox::send(message): message == NULL");
	}
	slotAvailable->P();
	senderMutex->lock();
	messages[in] = message; 
	in = (in + 1) % CAPACITY;
	senderMutex->unlock();
	messageAvailable->V();
}

/**
	Sends the previous message to the mailbox again.
*/
void AsyncMailbox::resend() {
	slotAvailable->P();
	senderMutex->lock();
	// Wrap around if needed to grab the previous message
	messages[in] = messages[(in + (CAPACITY - 1)) % CAPACITY];
	in = (in + 1) % CAPACITY;
	senderMutex->unlock();
	messageAvailable->V();
}

/**
	Receive a message from the mailbox.
	@return A pointer to the message object that was sent.
*/
void* AsyncMailbox::receive() {
	void* receivedMessage;
	messageAvailable->P();
	receiverMutex->lock();
	receivedMessage = messages[out];
	out = (out + 1) % CAPACITY;
	receiverMutex->unlock();
	slotAvailable->V();
	return receivedMessage;
}