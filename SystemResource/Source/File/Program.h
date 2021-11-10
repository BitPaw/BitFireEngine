#pragma once

#include "FileActionResult.hpp"
#include "ProgramExecuteResultListener.hpp"

namespace BF
{
	class Program
	{
		public:
		static FileActionResult Execute(const char* programPath, const char* parameterList, ProgramExecuteResultListener* callback);
		static FileActionResult Execute(const wchar_t* programPath, const char* parameterList, ProgramExecuteResultListener* callback);


		void* CurrentProcess();
		size_t CurrentProcessID();

		void Attach();
		void Detach();
		void ReadMemory();
	};
}