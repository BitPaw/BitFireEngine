#pragma once

#include "../ErrorCode.h"

#include <stdlib.h>

namespace BF
{
	class ProgramExecuteResultListener
	{
		public:
		virtual void OnProgramExecuted(bool succesful, intptr_t returnResult, ErrorCode errorCode) = 0;
	};
}