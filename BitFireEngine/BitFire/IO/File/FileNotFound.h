#pragma once

#include <exception>

#include "../../Utility/ASCIIString.h"

namespace BF
{
	class FileNotFound : public std::exception
	{
		public:
		ASCIIString ErrorMessage;
		ASCIIString FilePath;

		FileNotFound(ASCIIString& filePath);

		const char* what() const noexcept
		{
			return 0;
		}
	};
}