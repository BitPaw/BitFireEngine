#pragma once

#include <string>

#include "MessageType.h"

namespace BF
{
	class Message
	{
	public:
		MessageType Priority;
		std::string Content;

		Message(MessageType Priority, std::string Content);
	};
}