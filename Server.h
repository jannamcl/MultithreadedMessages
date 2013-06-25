#define MAX_CLIENTS 100

#include "Thread.h"
#include "AsyncMailbox.h"
#include "ChatMessage.h"
#include <string>
#include <iostream>

class Server {
	private:
		// The server's mailbox.
		AsyncMailbox* inbox;
		// The client mailboxes.
		AsyncMailbox* outboxes[MAX_CLIENTS];
		// Client usernames
		std::string connectedClients[MAX_CLIENTS];
		// Current number of connected clients
		int currentClients;
		int ResolveUsername(std::string username);
	public:
		Server(AsyncMailbox* inbox, int*);
		~Server();
		void Run();
		bool ConnectToServer(std::string username, AsyncMailbox* clientmailbox); 
};