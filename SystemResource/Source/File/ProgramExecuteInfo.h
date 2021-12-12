#pragma once

#include "ProgramExecuteResultListener.hpp"

namespace BF
{
	struct ProgramExecuteInfo
	{
		public:
		char FilePath[260];
		char ParameterList[1024];

		ProgramExecuteResultListener* CallBack;

		ProgramExecuteInfo();
	};
}