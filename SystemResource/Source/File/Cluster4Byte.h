#pragma once

#define MakeInt(a, b, c, d) (((unsigned int)a << 24) | ((unsigned int)b << 16) | ((unsigned int)c << 8) | ((unsigned int)d))

struct Cluster4Byte
{
	union
	{
		struct
		{
			unsigned char A;
			unsigned char B;
			unsigned char C;
			unsigned char D;
		};

		unsigned char Data[4];

		unsigned int Value;
	};

	Cluster4Byte(const unsigned int value);
};