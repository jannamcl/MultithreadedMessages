#include "SyncMailbox.h"

SyncMailbox::SyncMailbox() {
	//initialization
	this->sent = new CountingSemaphore(0); //nothing has been sent yet; 0 "permits"
	this->received = new CountingSemaphore(0); //nothing has been received yet; 0 "permits"
	this->mutex_receiving = new Mutex(); //setup a mutex to control when messages are received
	this->mutex_sending = new Mutex(); //setup a mutex to control when messages are sent
	this->msg = NULL; //no message yet
}

SyncMailbox::~SyncMailbox() {
	//Standard Destructor
	delete this->sent;
	delete this->received;
	delete this->mutex_receiving;
	delete this->mutex_sending;
}

void SyncMailbox::send(void* out) {
	if (out == NULL) { //if there is no message to be sent
		throw new std::exception("syncMailbox::send(out): out == NULL"); //inform mailbox user
	}
	this->mutex_sending->lock(); //only one thread at a time may send a message from this mailbox
	this->msg = out; //set the message to the message being sent
	this->sent->V(); //mailbox can now receive message
	this->received->P(); //block until the message has been received so no threads may send until the receive
	this->mutex_sending->unlock(); //threads may now send new messages
}

void* SyncMailbox::receive() {
	void* receivedMessage;
	this->mutex_receiving->lock(); //only one thread at a time may receive a message from this mailbox
	this->sent->P(); //block until a message has been sent so no other threads may receive until the send
	receivedMessage = this->msg; //the message
	this->received->V(); //mailbox can now send message
	this->mutex_receiving->unlock(); //threads may now receive new messages
	return receivedMessage;
}

void SyncMailbox::resend() { //resend last message
	this->mutex_sending->lock();
	this->sent->V();
	this->received->P();
	this->mutex_sending->unlock();
}