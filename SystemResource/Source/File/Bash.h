#pragma once

#include "FileActionResult.hpp"

namespace BF
{
	class Bash
	{
		public:
		static FileActionResult Execute(const char* programPath, bool syncronous = true);
		static FileActionResult Execute(const wchar_t* programPath, bool syncronous = true);
	};
}