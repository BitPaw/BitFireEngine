#include "DataBase.h"

#include <Windows.h>
#include <sqlext.h>  
#include <sqltypes.h>
#include <stdio.h>

void BF::DataBase::ConnectToFile(const wchar_t* filaPath)
{
}

void BF::DataBase::ConnectToServer(const wchar_t* serverName)
{
    SQLHENV henv;
    SQLHDBC hdbc;
    SQLHSTMT hstmt;

    SQLCHAR* OutConnStr = (SQLCHAR*)malloc(255);
    SQLSMALLINT* OutConnStrLen = (SQLSMALLINT*)malloc(255);

    // Allocate environment handle  
    SQLRETURN retcode = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv);

    // Set the ODBC version environment attribute  
    if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
    {
        retcode = SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0);

        // Allocate connection handle  
        if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
        {
            retcode = SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc);

            // Set login timeout to 5 seconds  
            if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
            {
                SQLSetConnectAttr(hdbc, SQL_LOGIN_TIMEOUT, (SQLPOINTER)5, 0);


                const SQLHDBC connectionHandle = hdbc;

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
                );

                bool successfulConnected = retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO;

                    // Allocate statement handle  
                if (successfulConnected)
                {
                    retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);

                    // Process data  



                    SQLUSMALLINT infoType = SQL_PROCEDURES;
                    wchar_t bufferLength[1024];
                    SQLSMALLINT   cbInfoValueMax = sizeof(bufferLength);
                    SQLSMALLINT pcbInfoValue = 0;

                    SQLRETURN infoResult = SQLGetInfoW
                    (
                        connectionHandle,
                        infoType,
                        bufferLength,
                        cbInfoValueMax,
                        &pcbInfoValue
                    );


                    SQLRETURN sqlRet = SQLExecDirectW(hstmt, (SQLWCHAR*)L" select* from waffle;", SQL_NTSL);

                    SQLSMALLINT nCols = 0;
                    SQLLEN nRows = 0;
                    SQLLEN nIdicator = 0;
                    wchar_t buf[2048] = { 0 };
                    size_t bufSize = sizeof(buf);

                    SQLNumResultCols(hstmt, &nCols);
                    SQLRowCount(hstmt, &nRows);

                    size_t rowIndex = 0;

                    while (SQL_SUCCEEDED(sqlRet = SQLFetch(hstmt)))
                    {
                        printf("Row (%zi/%zi) \n", ++rowIndex, nRows);
                
                        for (size_t i = 1; i <= nCols; ++i)
                        {
                            sqlRet = SQLGetData(hstmt, i, SQL_UNICODE_CHAR, buf, bufSize, &nIdicator);

                            if (SQL_SUCCEEDED(sqlRet))
                            {
                                printf("Column (%zi/%zi) Data:%ls\n", i, nCols, buf);                   
                            }
                        }
                    } 

                    //------------------
                    if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
                    {
                        SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
                    }

                    SQLDisconnect(hdbc);
                }

                SQLFreeHandle(SQL_HANDLE_DBC, hdbc);
            }
        }
       SQLRETURN returnResult = SQLFreeHandle(SQL_HANDLE_ENV, henv);
    }
}