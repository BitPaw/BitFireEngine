#pragma once

#include "Endian.h"

namespace BF
{
	struct QuadWord
	{
		public:
		unsigned char ByteData[8];

		QuadWord();
		QuadWord
		(
			unsigned char byteA, 
			unsigned char byteB,
			unsigned char byteC,
			unsigned char byteD, 
			unsigned char byteE,
			unsigned char byteF,
			unsigned char byteG,
			unsigned char byteH
		);

		void Set
		(
			unsigned char byteA,
			unsigned char byteB,
			unsigned char byteC,
			unsigned char byteD,
			unsigned char byteE,
			unsigned char byteF,
			unsigned char byteG,
			unsigned char byteH
		);
		unsigned long long ExtractLongLong(Endian endian);
		void InsertLongLong(Endian endian, unsigned long long value);
	};
}