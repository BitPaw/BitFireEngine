#pragma once

#include <cstddef>
#include "ProgramExecuteResultListener.hpp"

namespace BF
{
	struct ProgramExecuteInfo
	{
		public:
		char FilePath[260];

		char** ParameterList;
		size_t ParameterListSize;

		ProgramExecuteResultListener* CallBack;

		ProgramExecuteInfo();
	};
}