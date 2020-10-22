#pragma once

#include <iostream>

#include "Message.h"
#include "MessageType.h"

namespace BF
{
	class MessageSystem
	{
	public:
		static void PushMessage(Message message);
		static void PushMessage(MessageType Priority, std::string Content);
	};
}