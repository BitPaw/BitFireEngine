#pragma once

#include "../OSDefine.h"

#if defined(OSUnix)
#elif defined(OSWindows)
#include <Windows.h>
#include <sqlext.h>  
#include <sqltypes.h>
#endif

namespace BF
{
	class DataBase
	{
		private:		
#if defined(OSUnix)
#elif defined(OSWindows)
		SQLHENV _handleEnvironment;
		SQLHDBC _handleConnection;
#endif	

		public:
		DataBase();
		~DataBase();

		void Connect
		(
			const wchar_t* source,
			const wchar_t* database,
			const wchar_t* user,
			const wchar_t* password
		);

		void Disconnect();
		void Cleanup();

		void Execute(const wchar_t* sqlStatement);
	};
}