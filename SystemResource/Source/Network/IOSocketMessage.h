#pragma once

namespace BF
{
	struct IOSocketMessage
	{
		public:
		int SocketID;
		char* Message;
		size_t MessageSize;

		IOSocketMessage();
		IOSocketMessage(int socketID, char* message, size_t messageSize);		
	};
}