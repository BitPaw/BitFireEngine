#pragma once

#include <cstddef>

namespace BF
{
	struct IOSocketMessage
	{
		public:
		int SocketID;
		const unsigned char* Message;
		size_t MessageSize;

		IOSocketMessage();
		IOSocketMessage(int socketID, const unsigned char* message, size_t messageSize);
	};
}