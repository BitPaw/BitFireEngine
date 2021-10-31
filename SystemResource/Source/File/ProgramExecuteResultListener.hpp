#pragma once

#include "../ErrorCode.h"

namespace BF
{
	class ProgramExecuteResultListener
	{
		public:
		virtual void OnProgramExecuted(bool succesful, size_t returnResult, ErrorCode errorCode) = 0;
	};
}