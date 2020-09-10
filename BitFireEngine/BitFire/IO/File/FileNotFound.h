#pragma once

#include <string>
#include <exception>

class FileNotFound : public std::exception
{
public:
	char* ErrorMessage;
	std::string FilePath;

	FileNotFound(std::string filePath);

	~FileNotFound();

	const char* what() const noexcept
	{
		return ErrorMessage;
	}
};