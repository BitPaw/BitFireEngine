#ifndef ClusterIntDEFINED
#define ClusterIntDEFINED

#define MakeInt(a, b, c, d) MakeIntLE(a, b, c, d)
#define MakeIntBE(a, b, c, d) (((unsigned int)a << 24) | ((unsigned int)b << 16) | ((unsigned int)c << 8) | ((unsigned int)d))
#define MakeIntLE(a, b, c, d) (((unsigned int)a) | ((unsigned int)b << 8) | ((unsigned int)c << 16) | ((unsigned int)d << 24))

#ifdef __cplusplus
extern "C"
{
#endif

	typedef struct ClusterInt_
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
	}ClusterInt;

#ifdef __cplusplus
}
#endif

#endif