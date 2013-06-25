#include "AsyncMailbox.h"
#include "Thread.h"
#include "Server.h"
#include "Client.h"
#include <stdio.h>
#include <time.h>
#include <string>
#define REQUESTED_CLIENTS 50
#define MAX_CLIENTS 100

using namespace std;

// Client threads
Thread* clients[MAX_CLIENTS];
// The server's mailbox
AsyncMailbox* serverMailbox;
// The server object
Server* s;

// False if the server's been initialized, true if it has.
int serverReady = 0;

// Server thread starting point
void ServerThread(void*);
// Client thread starting point
void ClientThread(void*);
// Returns a name for a client.
string nameClient();
// Available name prefixes for clients.
string names[] = {"Billy", "Bob", "Joe", "Frank", "Rupert", "Timothy", "Trevor", 
	"Martin", "Mary Sue", "Ricardo", "Juan", "Heinrich"};

// Used in name assignments to rotate around the names
int temp = 0;
// Suffix for the client name
int temp2 = 0;

int main() {

	srand(time(NULL));

	serverMailbox = new AsyncMailbox();

	// Create a server thread and get it running
	Thread* server = new Thread();
	server->function = ServerThread;
	server->params = NULL;
	server->Run();

	// Create REQUESTED_CLIENTS client threads and run them.
	for(int i = 0; i < REQUESTED_CLIENTS; i++) {
		clients[i] = new Thread();
		clients[i]->function = ClientThread;
		clients[i]->params = NULL;
		clients[i]->Run();
		Sleep(1100);
	}

	while (true) {
		; // Prevent main thread from exiting
	}

	return 0;
}

// Create the server object and initialize it.
void ServerThread(void* params) {
	s = new Server(serverMailbox, &serverReady);
	s->Run();
}

// Returns a name for the client
string nameClient() {
	string clientName = names[temp % 12];
	temp++;
	if (temp > (sizeof(names) / sizeof(string))) {
		temp = 0;
		temp2++;
	}
	char temp3[5];
	clientName += itoa(temp2, temp3, 10);
	return clientName;
}

// Initialize a client and get it in its main loop
void ClientThread(void* params) {
	string clientName = nameClient();
	Client* c = new Client(serverMailbox, clientName);
	while (!serverReady) {
		; // Loop until server's ready
	}
	while (!(s->ConnectToServer(c->username, c->myMailbox))) {
		; // Loop until we connect to the server
	}
	c->Run();
}