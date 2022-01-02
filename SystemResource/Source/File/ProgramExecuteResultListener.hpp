#pragma once

#include "../ErrorCode.h"

#include <cstdlib>
#include <cstdint>

namespace BF
{
	class ProgramExecuteResultListener
	{
		public:
		virtual void OnProgramExecuted(bool succesful, intptr_t returnResult, ErrorCode errorCode) = 0;
	};
}