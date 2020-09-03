#include "MessagerSystem.h"

void MessagerSystem::PushMessage(Message message)
{
	std::string priorityTag;

	switch (message.Priority)
	{
	case MessagePriorityType::Info:
		priorityTag = "[°] ";
		break;

	case MessagePriorityType::Notfication:
		priorityTag = "[i] ";
		break;
	
	case MessagePriorityType::Warning:
		priorityTag = "[!] ";
		break;

	case MessagePriorityType::Error:	
		priorityTag = "[X] ";
		break;

	case MessagePriorityType::Failure:
		priorityTag = "[F] ";
		break;
	}

	std::cout << priorityTag << message.Content << std::endl;
}

void MessagerSystem::PushMessage(MessagePriorityType Priority, std::string Content)
{
	PushMessage(Message(Priority, Content));
}
