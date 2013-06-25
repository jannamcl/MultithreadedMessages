#ifndef CHATMESSAGE_H
#define CHATMESSAGE_H

#include <string>

struct ChatMessage {
	std::string origin; // " Username " from where message originated
	std::string destination; // " Username " to send to
	int timestamp; // For ordering messages on receiving client's end
	std::string message; 
};

#endif