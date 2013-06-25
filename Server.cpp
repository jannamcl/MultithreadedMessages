#include "Server.h"

/**
	Creates a new Server object.
	@param inbox Pointer to the server's mailbox.
	@param ready Pointer to the serverReady variable in SampleProgram.
*/
Server::Server(AsyncMailbox* inbox, int* ready) {
	this->currentClients = 0;
	this->inbox = inbox;
	*ready = 1;
}

/**
	Registers this client with the server if space is available.
	@param username The client's username.
	@param clientmailbox Pointer to the client's mailbox.
	@return True if connected, false if no space available.
*/
bool Server::ConnectToServer(std::string username, AsyncMailbox* clientmailbox) {
	if (this->currentClients >= MAX_CLIENTS) {
		return false;
	}
	this->connectedClients[this->currentClients] = username;
	this->outboxes[this->currentClients] = clientmailbox;
	++(this->currentClients);
	return true;
}

/**
	Destroys this Server object.
*/
Server::~Server() {
}

/**
	Look up a client's index based on their username.
	@param username The client's username.
	@return The client's index.
*/
int Server::ResolveUsername(std::string username) {
	for(int i = 0; i < this->currentClients; i++) {
		if(this->connectedClients[i] == username) {
			return i;
		}
	}
	return -1;
}

/**
	Server main loop. Dispatches messages as they come in.
*/
void Server::Run() {
	while (true) {
		//std::cout << "This thread is running! I am the server." << std::endl;
		/*while (this->state == 0) {
			; // Wait until flagged to run again
		}*/
		struct ChatMessage* msg;
		while (msg = (struct ChatMessage*) this->inbox->receive()) {
			int dest = this->ResolveUsername(msg->destination);
			if((dest > -1) && (dest < MAX_CLIENTS)) {
				this->outboxes[dest]->send(msg);
			}
		}
	}
}