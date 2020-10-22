#pragma once

#include <string>
#include <exception>

namespace BF
{
	class EmptyFileName : public std::exception
	{
		public:
		char* ErrorMessage;

		EmptyFileName();

		~EmptyFileName();

		const char* what() const noexcept
		{
			return ErrorMessage;
		}
	};
}