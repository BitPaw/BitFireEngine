#pragma once

namespace BF
{
	struct ISocketListener
	{
		public:				
		virtual void OnConnectionLinked(int socketID) = 0;
		virtual void OnConnectionListening(int socketID) = 0;
		virtual void OnConnectionEstablished(int socketID) = 0;
		virtual void OnConnectionTerminated(int socketID) = 0;

		virtual void OnMessageSend(int socketID, const char* message, size_t messageSize) = 0;
		virtual void OnMessageReceive(int socketID, const char* message, size_t messageSize) = 0;
	};
}