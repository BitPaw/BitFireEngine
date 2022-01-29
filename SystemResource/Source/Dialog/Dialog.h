#pragma once

#include "../Resource.h"
#include "../File/FileActionResult.hpp"

namespace BF
{
	class Dialog : public Resource
	{
		public:
		char Message[300];		

		FileActionResult Load()
		{
			return FileActionResult::Successful;
		};
	};
}