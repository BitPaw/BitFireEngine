#pragma once

#include <iostream>

#include "Message.h"

class MessagerSystem
{
public:
	static void PushMessage(Message message);
	static void PushMessage(MessagePriorityType Priority, std::string Content);
};