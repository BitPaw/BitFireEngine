#pragma once

#include <exception>

#include "../../Utility/AsciiString.h"

namespace BF
{
	class FileNotFound : public std::exception
	{
		public:
		AsciiString ErrorMessage;
		AsciiString FilePath;

		FileNotFound(AsciiString& filePath);

		const char* what() const noexcept
		{
			return 0;
		}
	};
}