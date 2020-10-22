#include "FileNotFound.h"

BF::FileNotFound::FileNotFound(std::string filePath)
{
	std::string messagePre = "File is missing at path <" + filePath + ">.";
	ErrorMessage = new char[messagePre.size() + 1]{'\x00'};

	for (size_t i = 0; i < messagePre.size(); i++)
	{
		ErrorMessage[i] = messagePre[i];
	}

	FilePath = filePath;
}

BF::FileNotFound::~FileNotFound()
{
	if (ErrorMessage != nullptr)
	{
		delete[] ErrorMessage;
	}
}