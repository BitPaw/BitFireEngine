#include "IOSocketMessage.h"

BF::IOSocketMessage::IOSocketMessage() : IOSocketMessage(0, nullptr, 0)
{

}

BF::IOSocketMessage::IOSocketMessage(int socketID, char* message, size_t messageSize)
{
	SocketID = socketID;
	Message = message;
	MessageSize = messageSize;
}