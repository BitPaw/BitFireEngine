#include "Message.h"

BF::Message::Message(MessageType priority, std::string content)
{
	Priority = priority;
	Content = content;
}