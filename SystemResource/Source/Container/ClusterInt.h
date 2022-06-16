#ifndef ClusterIntDEFINED

#define ClusterIntDEFINED

#define MakeInt(a, b, c, d) (((unsigned int)a) | ((unsigned int)b << 8) | ((unsigned int)c << 16) | ((unsigned int)d << 24))

struct ClusterInt
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
};

#endif