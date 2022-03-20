#include "SQLType.h"

#include <Windows.h>
#include <sql.h>

const BF::SQLType BF::ToSQLType(const unsigned int sqlType)
{
    switch (sqlType)
    {
        // Mysql?
        case -9: return SQLType::StringUNICODE;

        // is this thenCorrect?
        case  SQL_VARCHAR:return SQLType::StringANSI;

        case SQL_UNKNOWN_TYPE: return SQLType::Unkown;
        case SQL_CHAR:return SQLType::Character;
        case SQL_NUMERIC:return SQLType::Numeric;
        case SQL_DECIMAL:return SQLType::Decimal;
        case SQL_INTEGER:return SQLType::Integer;
        case SQL_SMALLINT:return SQLType::Short;
        case SQL_FLOAT:return SQLType::Float;
        case SQL_REAL:return SQLType::Real;
        case SQL_DOUBLE:return SQLType::Double;
#if (ODBCVER >= 0x0300)
        case  SQL_DATETIME:return SQLType::DATETIME;
#endif
     

        /* One-parameter shortcuts for date/time data types */
#if (ODBCVER >= 0x0300)
        case SQL_TYPE_DATE :return SQLType::TYPE_DATE;
        case SQL_TYPE_TIME :return SQLType::TYPE_TIME;
        case SQL_TYPE_TIMESTAMP :return SQLType::TYPE_TIMESTAMP;
#endif

        default:
            return SQLType::Invalid;
    }
}

const char* BF::SQLTypeToString(const SQLType sqlType)
{
    switch (sqlType)
    {
        default:
        case BF::SQLType::Invalid: return "Invalid";
        case BF::SQLType::Unkown: return "Unkown";
        case BF::SQLType::Character: return "Character";
        case BF::SQLType::Numeric:return "Numeric";
        case BF::SQLType::Decimal:return "Decimal";
        case BF::SQLType::Integer:return "Integer";
        case BF::SQLType::Short:return "Short";
        case BF::SQLType::Float:return "Invalid";
        case BF::SQLType::Real:return "Real";
        case BF::SQLType::Double :return "Double";
        case BF::SQLType::DATETIME:return "DATETIME";
        case BF::SQLType::StringANSI:return "StringANSI";
        case BF::SQLType::StringUNICODE:return "StringUNICODE";
        case BF::SQLType::TYPE_DATE:return "TYPE_DATE";
        case BF::SQLType::TYPE_TIME:return "TYPE_TIME";
        case BF::SQLType::TYPE_TIMESTAMP:return "TYPE_TIMESTAMP";
    }
}
