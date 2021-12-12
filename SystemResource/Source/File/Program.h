#pragma once

#include "FileActionResult.hpp"
#include "ProgramExecuteResultListener.hpp"

#include "../Async/Thread.h"

namespace BF
{
	class Program
	{
		public:
		static ThreadFunctionReturnType ExecuteThreadFunction(void* data);

		static FileActionResult Execute(const char* programPath, const char* parameterList, ProgramExecuteResultListener* callback);
		static FileActionResult Execute(const wchar_t* programPath, const wchar_t* parameterList, ProgramExecuteResultListener* callback);


		void* CurrentProcess();
		size_t CurrentProcessID();

		void Attach();
		void Detach();
		void ReadMemory();
	};
}