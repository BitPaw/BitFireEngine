#ifndef DataBaseINLCUDE
#define DataBaseINLCUDE

#include <OS/System/OSVersion.h>

#if OSUnix
#elif OSWindows
#include <Windows.h>
#include <sqlext.h>  
#include <sqltypes.h>
#endif

#include <Format/Type.h>

#ifdef __cplusplus
extern "C"
{
#endif

	typedef enum SQLType_
	{
		SQLTypeInvalid,
		SQLTypeUnkown,

		// C Types
		SQLTypeCharacter, // tinyint
		SQLTypeInteger,
		SQLTypeLongLong, // bigint
		SQLTypeFloat,
		SQLTypeDouble,
		SQLTypeShort, // smallint

		SQLTypeStringANSI, // char Array
		SQLTypeStringUNICODE, // wchar_t Array


		// SQL - Variable Types
		SQLTypeNumeric,
		SQLTypeDecimal,
		SQLTypeReal, // like float

		SQLTypeDATETIME,

		SQLTypeTYPE_DATE,
		SQLTypeTYPE_TIME,
		SQLTypeTYPE_TIMESTAMP
	}
	SQLType;

	const SQLType SQLTypeFromID(const unsigned int sqlType);


	typedef enum SQLResult_
	{
		SQLResultInvalid,
		SQLResultSuccessful,
		SQLResultConnectionFailed,
		SQLResultDatabaseNotConnected, // Trying to use a command that requires an already established connection.
		SQLResultMemoryAllocFailed,
		SQLResultMemoryFreeFailed,
		SQLResultSettingEnvironmentAttributeFailed,
		SQLResultExecuteFailed
	}
	SQLResult;

	typedef void (*ConnectedEvent)
		(
			const wchar_t* driver,
			const wchar_t* source,
			const wchar_t* database,
			const wchar_t* user
			);

	typedef void (*DriverDetectedEvent)(const wchar_t* driverName, const wchar_t* driverAttribte);
	typedef void (*ResultEvent)(const PXSize columSize, const PXSize rowSize);
	typedef void (*ColumInfoEvent)
		(
			const PXSize columIndex,
			const SQLType type,
			const unsigned char canBeNull,
			const wchar_t* name,
			const PXSize nameLength
			);
	typedef void (*RowDataEvent)
		(
			const PXSize rowIndex,
			const PXSize columIndex,
			const wchar_t* fieldString
			);


	typedef struct DataBaseConnection_
	{
#if OSUnix
#elif OSWindows
		SQLHENV _handleEnvironment;
		SQLHDBC _handleConnection;
#endif	

		ConnectedEvent OnConnectedEvent;
		DriverDetectedEvent OnDriverDetectedEvent;
		ResultEvent OnResultEvent;
		ColumInfoEvent OnColumInfoEvent;
		RowDataEvent OnRowDataEvent;
	}
	DataBaseConnection;


	PXPublic void DataBaseConnectionConstruct(DataBaseConnection* const dataBaseConnection);
	PXPublic void DataBaseConnectionDestruct(DataBaseConnection* const dataBaseConnection);

	PXPublic void DataBaseConnectionConnect
	(
		DataBaseConnection* const dataBaseConnection,
		const wchar_t* source,
		const wchar_t* database,
		const wchar_t* user,
		const wchar_t* password
	);
	PXPublic void DataBaseConnectionDisconnect(DataBaseConnection* const dataBaseConnection);
	PXPublic void DataBaseConnectionCleanup(DataBaseConnection* const dataBaseConnection);

	PXPublic void DataBaseConnectionScanForDrivers(DataBaseConnection* const dataBaseConnection);

	PXPublic void DataBaseConnectionExecute(DataBaseConnection* const dataBaseConnection, const wchar_t* sqlStatement);

#ifdef __cplusplus
}
#endif

#endif