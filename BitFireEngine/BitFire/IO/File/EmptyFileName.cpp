#include "EmptyFileName.h"

BF::EmptyFileName::EmptyFileName()
{
	std::string messagePre = "Filepath is empty.";
	ErrorMessage = new char[messagePre.size() + 1]{ '\x00' };

	for (size_t i = 0; i < messagePre.size(); i++)
	{
		ErrorMessage[i] = messagePre[i];
	}
}

BF::EmptyFileName::~EmptyFileName()
{
	if (ErrorMessage != nullptr)
	{
		delete[] ErrorMessage;
	}
}