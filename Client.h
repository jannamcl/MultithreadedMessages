#ifndef CLIENT_H
#define CLIENT_H
#define TEST 1

#include "Thread.h"
#include "AsyncMailbox.h"
#include "ChatMessage.h"
#include <string>
#include <iostream>

class Client {
private:
	// Pointer to the server's mailbox.
	AsyncMailbox* serverMailbox;
	void HandleMessage(struct ChatMessage* msg);
	char* GenRandom(const int len);
	void TestSend();
public:
	// This client's mailbox.
	AsyncMailbox* myMailbox;
	// This client's username.
	std::string username;
	Client(AsyncMailbox* serverMailbox, std::string username);
	~Client();
	void Run();
	void SendMessage(struct ChatMessage* msg);
	struct ChatMessage* ReceiveMessage(); //receiver blocks until message available
	void PrintMessage();
};

#endif