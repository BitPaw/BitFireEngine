#pragma once

#include <string>

#include "MessagePriorityType.h"

class Message
{
public:
	MessagePriorityType Priority;
	std::string Content;

	Message(MessagePriorityType Priority, std::string Content);
};