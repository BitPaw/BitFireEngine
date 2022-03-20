#include "DataBase.h"

#include <stdio.h>

BF::DataBase::DataBase()
{
    OnConnectedEvent = 0;
    OnDriverDetectedEvent = 0;
    OnResultEvent = 0;
    OnColumInfoEvent = 0;
    OnRowDataEvent = 0;

#if defined(OSUnix)
#elif defined(OSWindows)
    _handleEnvironment = 0;
    _handleConnection = 0;
#endif	
}

BF::DataBase::~DataBase()
{
    Disconnect();

    Cleanup();
}

BF::SQLResult BF::DataBase::Connect
(
    const wchar_t* source,
    const wchar_t* database,
    const wchar_t* user,
    const wchar_t* password
)
{
    // Allocate environment handle  
    {
        const SQLRETURN result = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &_handleEnvironment);
        const bool successful = result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO;

        if (!successful)
        {
            return SQLResult::MemoryAllocFailed;
        }
    }

    // Set the ODBC version environment attribute  
    {
        const SQLRETURN result = SQLSetEnvAttr(_handleEnvironment, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0);
        const bool successful = result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO;

        if (!successful)
        {
            return SQLResult::SettingEnvironmentAttributeFailed;
        }
    }

    // Allocate connection handle  
    {
        const SQLRETURN result = SQLAllocHandle(SQL_HANDLE_DBC, _handleEnvironment, &_handleConnection);
        const bool successful = result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO;

        if (!successful)
        {
            return SQLResult::MemoryAllocFailed;
        }
    }
           
    // Set login timeout to 5 seconds  
    {
        const SQLRETURN resultConnect = SQLSetConnectAttrW(_handleConnection, SQL_LOGIN_TIMEOUT, (SQLPOINTER)5, 0);
        const bool successful = resultConnect == SQL_SUCCESS || resultConnect == SQL_SUCCESS_WITH_INFO;

        if (!successful)
        {
            return SQLResult::Invalid;
        }
    }   
                                                                      
    printf("+---[ODBC Drivers]-------------------------------------------+--------------+\n");

    ScanForDrivers();

    printf("+------------------------------------------------------------+--------------+\n");

    const wchar_t* driver = L"MySQL ODBC 8.0 Unicode Driver";

    // Connect
    {
        SQLWCHAR connectionString[2048]{ 0 };
        SQLWCHAR connectionStringResult[2048]{ 0 };
        const SQLSMALLINT connectionStringResultSize = sizeof(connectionStringResult) / sizeof(SQLWCHAR);
        SQLSMALLINT connectionStringResultWrittenSize = 0;
        const size_t connectionStringSize = wsprintf
        (
            connectionString,
            L"Driver={%ls};Server=%ls;Database=%ls;UID=%ls;PWD=%ls;",
            driver,
            source,
            database,
            user,
            password
        );

        const SQLRETURN resultDriverConnect = SQLDriverConnectW
        (
            _handleConnection,
            NULL,
            connectionString,
            connectionStringSize,
            connectionStringResult,
            connectionStringResultSize,
            &connectionStringResultWrittenSize,
            SQL_DRIVER_NOPROMPT
        );

        const bool successfulConnected = resultDriverConnect == SQL_SUCCESS || resultDriverConnect == SQL_SUCCESS_WITH_INFO;

        if (!successfulConnected)
        {
            return SQLResult::ConnectionFailed;
        }
    }

    if (OnConnectedEvent)
    {
        OnConnectedEvent(driver, source, database, user);
    }

    return SQLResult::Successful;

    /*
    SQLWCHAR* serverNameS = (wchar_t*)serverName;
    const SQLSMALLINT serverNameLength = SQL_NTSL;
    SQLWCHAR* userName = NULL;
    const SQLSMALLINT userNameLength = 0;
    SQLWCHAR* password = NULL;
    const SQLSMALLINT passwordLength = 0;

    retcode = SQLConnectW
    (
        connectionHandle,
        serverNameS,
        serverNameLength,
        userName,
        userNameLength,
        password,
        passwordLength
    );* /

    if (successfulConnected)
    {       
        SQLUSMALLINT infoType = SQL_PROCEDURES;
        wchar_t bufferLength[1024];
        SQLSMALLINT   cbInfoValueMax = sizeof(bufferLength);
        SQLSMALLINT pcbInfoValue = 0;

        SQLRETURN infoResult = SQLGetInfoW
        (
            _handleConnection,
            infoType,
            bufferLength,
            cbInfoValueMax,
            &pcbInfoValue
        );       
    }*/
}

void BF::DataBase::ScanForDrivers()
{
    SQLUSMALLINT direction = SQL_FETCH_FIRST;
    bool finished = false;

    while(!finished)
    {
        wchar_t driverDescription[1024]{ 0 };
        const SQLSMALLINT driverDescriptionSize = sizeof(driverDescription) / sizeof(wchar_t);
        SQLSMALLINT driverDescriptionSizeWritten = 0;

        wchar_t driverAttributes[1024]{ 0 };
        const SQLSMALLINT driverAttributesSize = sizeof(driverAttributes) / sizeof(wchar_t);
        SQLSMALLINT driverAttributesSizeWritten = 0;

        const SQLRETURN resultDriver = SQLDriversW
        (
            _handleEnvironment,
            direction,
            driverDescription,
            driverDescriptionSize,
            &driverDescriptionSizeWritten,
            driverAttributes,
            driverAttributesSize,
            &driverAttributesSizeWritten
        );

        switch (resultDriver)
        {
            case SQL_SUCCESS_WITH_INFO:
            case SQL_SUCCESS: // Do nothing and go next   
                direction = SQL_FETCH_NEXT; // [!] Important [!] - Mark to go next. 

                if (OnDriverDetectedEvent)
                {
                    OnDriverDetectedEvent(driverDescription, driverAttributes);
                }

                printf("| %-57ls | %-13ls |\n", driverDescription, driverAttributes);
                break;

            default:
            case SQL_ERROR: // Unkown error
            case SQL_INVALID_HANDLE: // Environment handle was invalid
            case SQL_NO_DATA: // read error : No entry
                finished = true;
                break;
        }
    }
}

void BF::DataBase::Disconnect()
{
    if (_handleConnection != 0)
    {
        const SQLRETURN resultDisconnect = SQLDisconnect(_handleConnection);
        const SQLRETURN resultFree = SQLFreeHandle(SQL_HANDLE_DBC, _handleConnection);

        _handleConnection = 0;
    }
}

void BF::DataBase::Cleanup()
{
    Disconnect();

    if (_handleEnvironment != 0)
    {
        const SQLRETURN result = SQLFreeHandle(SQL_HANDLE_ENV, _handleEnvironment);
    }   
}

BF::SQLResult BF::DataBase::Execute(const wchar_t* sqlStatement)
{
    SQLHSTMT handleStatement = 0;    
    size_t colums = 0;
    size_t rows = 0;
     
    // Check connection
    {
        const bool connected = _handleConnection != 0;

        if (!connected)
        {
            return SQLResult::DatabaseNotConnected;
        }
    }   

    // Alloc statement
    {
        const SQLRETURN retcode = SQLAllocHandle(SQL_HANDLE_STMT, _handleConnection, &handleStatement);
        const bool sucessfulAlloc = retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO;

        if (!sucessfulAlloc)
        {
            return SQLResult::MemoryAllocFailed;
        }
    }
       
    // Execute command
    {
        const SQLRETURN resultExecute = SQLExecDirectW(handleStatement, (SQLWCHAR*)sqlStatement, SQL_NTSL);
        const bool successful = resultExecute == SQL_SUCCESS || resultExecute == SQL_SUCCESS_WITH_INFO;

        if (!successful)
        {
            return SQLResult::ExecuteFailed;
        }
    }

    // Get table size
    {
        SQLSMALLINT nCols = 0;
        SQLLEN nRows = 0;

        SQLNumResultCols(handleStatement, &nCols);
        SQLRowCount(handleStatement, &nRows);

        colums = nCols;
        rows = nRows;
    }
  
    if (OnResultEvent)
    {
        OnResultEvent(colums, rows);
    }

    printf("[Result] Rows:%zi Colums:%zi\n", rows, colums);
  
    printf("+----------------------+----------------------+----------------------+----------------------+\n");

    printf("|");

    for (size_t columIndex = 1; columIndex <= colums; ++columIndex)
    {
        wchar_t columnName[1024]{ 0 };
        const SQLSMALLINT columnNameSize = sizeof(columnName) / sizeof(wchar_t);
        SQLSMALLINT columnNameSizeWritten;

        SQLSMALLINT DataType;
        SQLULEN ColumnSize;
        SQLSMALLINT decimalDigits = 0;
        SQLSMALLINT isNullableID = 0;
        bool isNullable = false;
        bool isBaseType = false;

        const SQLRETURN resultDescriped = SQLDescribeColW
        (
            handleStatement,
            columIndex,
            columnName,
            columnNameSize,
            &columnNameSizeWritten,
            &DataType,
            &ColumnSize,
            &decimalDigits,
            &isNullableID
        );

        const SQLType type = ToSQLType(DataType);

        //SQLColAttribute();

        //isBaseType = DataType == SQL_COLUMN_DISTINCT_TYPE;
        isNullable = isNullableID == SQL_NULLABLE; // SQL_NO_NULLS

        const char* typeName = SQLTypeToString(type);

        if (OnColumInfoEvent)
        {
            OnColumInfoEvent(columIndex, type, isNullable, columnName, columnNameSizeWritten);
        }
        
        printf(" %-20ls |", columnName);
    }

    printf("\n");
    printf("+----------------------+----------------------+----------------------+----------------------+\n");

    SQLRETURN resultFetch = 0;
    for (size_t rowIndex = 0 ; SQL_SUCCEEDED(resultFetch = SQLFetch(handleStatement)); ++rowIndex)
    {
        printf("|");

        for (size_t columIndex = 1; columIndex <= colums; ++columIndex)
        {
            wchar_t fieldBuffer[1048] { 0 };
            const size_t fieldBufferSize = sizeof(fieldBuffer) / sizeof(wchar_t);
            SQLLEN readLength = 0;

            const SQLRETURN resultData = SQLGetData(handleStatement, columIndex, SQL_UNICODE_CHAR, fieldBuffer, fieldBufferSize, &readLength);
            const bool success = SQL_SUCCEEDED(resultData);

            if (success)
            {
                if (OnRowDataEvent)
                {
                    OnRowDataEvent(rowIndex, columIndex, fieldBuffer);
                }

                printf(" %-20ls |", fieldBuffer);
            }
        }

        printf("\n");
    }

    printf("+----------------------+----------------------+----------------------+----------------------+\n");
   
    // Free memory
    {
        const SQLRETURN resultFree = SQLFreeHandle(SQL_HANDLE_STMT, handleStatement);
        const bool successful = resultFree == SQL_SUCCESS || resultFree == SQL_SUCCESS_WITH_INFO;

        if (successful)
        {
            return SQLResult::MemoryFreeFailed;
        }
    }

    return SQLResult::Successful;
}