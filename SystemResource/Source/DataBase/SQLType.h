#pragma once

namespace BF
{
	enum class SQLType
	{
		Invalid,
		Unkown,

		// C Types
		Character, // tinyint
		Integer,
		LongLong, // bigint
		Float,
		Double,
		Short, // smallint

		StringANSI, // char Array
		StringUNICODE, // wchar_t Array


		// SQL - Variable Types
		Numeric, 
		Decimal,
		Real, // like float
			
		DATETIME,
		
		TYPE_DATE,
		TYPE_TIME,
		TYPE_TIMESTAMP
	};

	const SQLType ToSQLType(const unsigned int sqlType);

	const char* SQLTypeToString(const SQLType sqlType);
}