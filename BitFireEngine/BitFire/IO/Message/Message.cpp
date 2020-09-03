#include "Message.h"

Message::Message(MessagePriorityType priority, std::string content)
{
	Priority = priority;
	Content = content;
}