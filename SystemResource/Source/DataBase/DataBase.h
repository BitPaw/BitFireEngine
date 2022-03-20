#pragma once

#include "../OSDefine.h"

#include "SQLType.h"
#include "SQLResult.h"

#include <cstddef>

#if defined(OSUnix)
#elif defined(OSWindows)
#include <Windows.h>
#include <sqlext.h>  
#include <sqltypes.h>
#endif

namespace BF
{
	typedef void (*ConnectedEvent)
		(
			const wchar_t* driver,
			const wchar_t* source,
			const wchar_t* database,
			const wchar_t* user
		);

	typedef void (*DriverDetectedEvent)(const wchar_t* driverName, const wchar_t* driverAttribte);
	typedef void (*ResultEvent)(const size_t columSize, const size_t rowSize);
	typedef void (*ColumInfoEvent)
		(
			const size_t columIndex, 
			const SQLType type, 
			const bool canBeNull,
			const wchar_t* name,
			const size_t nameLength
		);
	typedef void (*RowDataEvent)
		(
			const size_t rowIndex, 
			const size_t columIndex,
			const wchar_t* fieldString
		);

	class DataBase
	{
		private:		
#if defined(OSUnix)
#elif defined(OSWindows)
		SQLHENV _handleEnvironment;
		SQLHDBC _handleConnection;
#endif	

		ConnectedEvent OnConnectedEvent;
		DriverDetectedEvent OnDriverDetectedEvent;
		ResultEvent OnResultEvent;
		ColumInfoEvent OnColumInfoEvent;
		RowDataEvent OnRowDataEvent;

		public:
		DataBase();
		~DataBase();

		SQLResult Connect
		(
			const wchar_t* source,
			const wchar_t* database,
			const wchar_t* user,
			const wchar_t* password
		);

		void ScanForDrivers();

		void Disconnect();
		void Cleanup();

		SQLResult Execute(const wchar_t* sqlStatement);
	};
}