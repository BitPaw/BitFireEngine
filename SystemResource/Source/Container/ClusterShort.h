#ifndef ClusterShortDEFINED

#define ClusterShortDEFINED

#define MakeShort(a, b) (((unsigned short)a) | ((unsigned short)b << 8))

struct ClusterShort
{
	union
	{
		struct
		{
			unsigned char A;
			unsigned char B;
		};

		unsigned char Data[2];

		unsigned short Value;
	};
};

#endif