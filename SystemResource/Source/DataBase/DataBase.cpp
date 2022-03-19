#include "DataBase.h"


#include <stdio.h>

BF::DataBase::DataBase()
{
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

void BF::DataBase::Connect
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
            return;
        }
    }

    // Set the ODBC version environment attribute  
    {
        const SQLRETURN result = SQLSetEnvAttr(_handleEnvironment, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0);
        const bool successful = result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO;

        if (!successful)
        {
            return;
        }
    }

    // Allocate connection handle  
    {
        const SQLRETURN result = SQLAllocHandle(SQL_HANDLE_DBC, _handleEnvironment, &_handleConnection);
        const bool successful = result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO;

        if (!successful)
        {
            return;
        }
    }
           
    // Set login timeout to 5 seconds  
    SQLSetConnectAttr(_handleConnection, SQL_LOGIN_TIMEOUT, (SQLPOINTER)5, 0);

    /*                {
        //const wchar_t* connectionString = L"DRIVER={SQL Server};";
        const wchar_t* connectionString = L"DSN=BFDB;";
        SQLSMALLINT connectionStringLength = SQL_NTSL;

        SQLWCHAR outConnection[1024]{0};
        const SQLSMALLINT outConnectionLength = sizeof(outConnection) / sizeof(SQLWCHAR);
        SQLSMALLINT outConnectionLengthWritten = 0;

       // SQL_NEED_DATA

        /*
        SQL_SUCCESS
             SQL_SUCCESS_WITH_INFO,
            SQL_NEED_DATA,
            SQL_ERROR,
            SQL_INVALID_HANDLE,
            SQL_STILL_EXECUTING.* /

        SQLRETURN resulkt = SQLBrowseConnectW
        (
            connectionHandle,
            (wchar_t*)connectionString,
            connectionStringLength,
            outConnection,
            outConnectionLength,
            &outConnectionLengthWritten
        );

        printf("sdf\n");
    }*/






    SQLUSMALLINT direction = SQL_FETCH_FIRST;
    bool finished = false;

                                                               
    printf("+---[ODBC Drivers]-------------------------------------------+--------------+\n");

    while (!finished)
    {
        SQLWCHAR driverDescription[1024]{ 0 };
        const SQLSMALLINT driverDescriptionSize = sizeof(driverDescription) / sizeof(SQLWCHAR);
        SQLSMALLINT driverDescriptionSizeWritten = 0;

        SQLWCHAR driverAttributes[1024]{ 0 };
        const SQLSMALLINT driverAttributesSize = sizeof(driverAttributes) / sizeof(SQLWCHAR);
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

    printf("+------------------------------------------------------------+--------------+\n");



    SQLWCHAR connectionString[2048]{ 0 };
    SQLWCHAR connectionStringResult[2048]{ 0 };

    //wprintf(connectionString, "Driver={SQL Server Native Client 11.0};Server=SqlHostName;Database=SomeSqlDatabase;UID=YourUserName;PWD=YourPassword");

    const SQLSMALLINT connectionStringResultSize = sizeof(connectionStringResult) / sizeof(SQLWCHAR);
    SQLSMALLINT connectionStringResultWrittenSize = 0;
    const size_t connectionStringSize = wsprintf
    (
        connectionString,
        L"Driver={MySQL ODBC 8.0 Unicode Driver};Server=%ls;Database=%ls;UID=%ls;PWD=%ls;",
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

    bool successfulConnected = resultDriverConnect == SQL_SUCCESS || resultDriverConnect == SQL_SUCCESS_WITH_INFO;




    /*

    wprintf();


    // Connect to data source

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
    );0* /

    // Allocate statement handle  
    if (successfulConnected)
    {
        

        // Process data  



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
    }    */
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

void BF::DataBase::Execute(const wchar_t* sqlStatement)
{
    SQLHSTMT hstmt = 0;
        
    if (_handleConnection == 0)
    {
        return; // No Connection
    }

    // Alloc statement
    {
        const SQLRETURN retcode = SQLAllocHandle(SQL_HANDLE_STMT, _handleConnection, &hstmt);
        const bool sucessfulAlloc = retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO;

        if (!sucessfulAlloc)
        {
            return; // Out of memory
        }
    }
       
 

    SQLRETURN sqlRet = SQLExecDirectW(hstmt, (SQLWCHAR*)sqlStatement, SQL_NTSL);

    SQLSMALLINT nCols = 0;
    SQLLEN nRows = 0;

    SQLNumResultCols(hstmt, &nCols);
    SQLRowCount(hstmt, &nRows);

    size_t rowIndex = 0;

    printf("[Result] Rows:%i Colums:%i\n", nRows, nCols);

    while (SQL_SUCCEEDED(sqlRet = SQLFetch(hstmt)))
    {
        for (size_t i = 1; i <= nCols; ++i)
        {
            wchar_t fieldBuffer[2048] = { 0 };
            const size_t fieldBufferSize = sizeof(fieldBuffer) / sizeof(wchar_t);
            SQLLEN readLength = 0;

            const SQLRETURN resultData = SQLGetData(hstmt, i, SQL_UNICODE_CHAR, fieldBuffer, fieldBufferSize, &readLength);
            const bool success = SQL_SUCCEEDED(sqlRet);

            if (success)
            {
                printf("%ls, ", fieldBuffer);
            }
        }

        printf("\n");
    }

   
    SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
}