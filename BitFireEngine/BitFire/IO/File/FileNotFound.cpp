#include "FileNotFound.h"

BF::FileNotFound::FileNotFound(ASCIIString& filePath)
{
	ASCIIString fileMissing("File is missing at path <");
	ASCIIString messagePre = fileMissing + filePath + ">.";
	ErrorMessage = messagePre;

	FilePath = filePath;
}