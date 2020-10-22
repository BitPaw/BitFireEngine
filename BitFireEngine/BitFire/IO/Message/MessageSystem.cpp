#include "MessageSystem.h"

void BF::MessageSystem::PushMessage(Message message)
{
	std::string priorityTag;

	switch (message.Priority)
	{
	case MessageType::Info:
		priorityTag = "[i] ";
		break;

	case MessageType::Notfication:
		priorityTag = "[#] ";
		break;
	
	case MessageType::Warning:
		priorityTag = "[!] ";
		break;

	case MessageType::Error:
		priorityTag = "[X] ";
		break;

	case MessageType::Failure:
		priorityTag = "[F] ";
		break;
	}

	std::cout << priorityTag << message.Content << std::endl;
}

void BF::MessageSystem::PushMessage(MessageType Priority, std::string Content)
{
	PushMessage(Message(Priority, Content));
}
