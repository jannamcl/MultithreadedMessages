#include "Client.h"
#include <time.h>
#define TEST 1  // Whether or not the clients should automatically send random garbage
#define REQUESTED_CLIENTS 50

/**
Create a new Client object.
@param server A pointer to the server object.
@param username This client's username.
*/
Client::Client(AsyncMailbox* server, std::string username) {
	this->serverMailbox = server;
	this->myMailbox = new AsyncMailbox();
	this->username = username;
}

/**
Destroys this Client object.
*/
Client::~Client() {
}

/**
Sends a message to the server.
@param msg Pointer to the ChatMessage to be sent.
*/
void Client::SendMessage(struct ChatMessage* msg) {
	this->serverMailbox->send(msg);
	std::cout << "--- Outgoing Message (" << this->username << ") ---" << std::endl 
		<< "Passed a message to " << msg->destination << " to the server." << std::endl 
		<< "Body: " << msg->message << std::endl << "--- End of Message ---" 
		<< std::endl <<std::endl;
}

/**
Receives a message from the server.
@return Returns a pointer to the ChatMessage being received.
*/
struct ChatMessage* Client::ReceiveMessage() {
	struct ChatMessage* message = (struct ChatMessage*) this->myMailbox->receive();
	return message;
}

/**
Starts this client's main loop. The client must register with the server 
via Server::ConnectToServer() before calling this method.
*/
void Client::Run() {

	srand(time(NULL));

	while(true) {
		//std::cout << "This thread is running! I am " << this->username << "." 
		//<< std::endl;
#ifdef TEST
		// Send some random message to another client at random

		Sleep((rand()%(750-250))+250);

		char* out = this->GenRandom(16);
		if (out == NULL) {
			continue;
		}
		std::string names[] = {"Billy", "Bob", "Joe", "Frank", "Rupert", "Timothy", 
			"Trevor", "Martin", "Mary Sue", "Ricardo", "Juan", "Heinrich"};

		struct ChatMessage testmsg;
		testmsg.origin = this->username;
		char temp3[5];
		testmsg.destination = names[rand() % 12] + itoa(rand() % 4, temp3, 10);
		testmsg.timestamp = (int) time(NULL);
		testmsg.message = out;
		struct ChatMessage* temp = &testmsg;
		this->SendMessage(temp);	
#endif

		struct ChatMessage* msg = this->ReceiveMessage();
		if (msg == NULL) {
			continue;
		}
		this->HandleMessage(msg);


	}
}

/**
Handles the received message.
@param msg Pointer to the message that was received.
*/
void Client::HandleMessage(struct ChatMessage* msg) {
	// Implement some client functionality if desired.
	// We're just printing to stdout for ease of programming.
	std::cout << "--- Incoming Message (" << this->username << ") ---" << std::endl 
		<< "From: " << msg->origin 
		<< ", To: " << msg->destination << std::endl 
		<< "Body: " << msg->message << std::endl 
		<< "Sent: " << msg->timestamp << std::endl 
		<< "--- End of Message ---" << std::endl << std::endl;
	Sleep(10000); // Just so messages are legible.
}

/**
Generates a null-terminated random string of characters.
@param len Length of the string to be generated.
@return A pointer to the string, or NULL if out of memory.
*/
char* Client::GenRandom(const int len) {
	char* s = (char*) malloc(len + 1);
	if (s == NULL) {
		return NULL;
	}
	for (int i = 0; i < len; ++i) {
		int randomChar = rand()%(26+26+10);
		if (randomChar < 26) {
			s[i] = 'a' + randomChar;
		}
		else if (randomChar < 26+26) {
			s[i] = 'A' + randomChar - 26;
		}
		else {
			s[i] = '0' + randomChar - 26 - 26;
		}
	}
	s[len] = 0;
	return s;
}