#include "FileNotFound.h"

BF::FileNotFound::FileNotFound(AsciiString& filePath)
{
	AsciiString fileMissing("File is missing at path <");
	AsciiString messagePre = fileMissing + filePath + ">.";
	ErrorMessage = messagePre;

	FilePath = filePath;
}