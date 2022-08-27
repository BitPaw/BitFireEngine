#ifndef ClusterLongLongDEFINED
#define ClusterLongLongDEFINED

#define MakeLongLong(a, b, c, d, e, f, g, h) MakeLongLongLE(a, b, c, d, e, f, g, h)

#define MakeLongLongBE(a, b, c, d, e, f, g, h) \
(((unsigned long long)a << 56LL) | \
((unsigned long long)b << 48LL) | \
((unsigned long long)c << 40LL) | \
((unsigned long long)d << 32LL) | \
((unsigned long long)e << 24LL) | \
((unsigned long long)f << 16LL) | \
((unsigned long long)g << 8LL) | \
((unsigned long long)h));

#define MakeLongLongLE(a, b, c, d, e, f, g, h) \
(((unsigned long long)a) | \
((unsigned long long)b << 8LL) | \
((unsigned long long)c << 16LL) | \
((unsigned long long)d << 24LL) | \
((unsigned long long)e << 32LL) | \
((unsigned long long)f << 40LL) | \
((unsigned long long)g << 48LL) | \
((unsigned long long)h << 56LL));

#ifdef __cplusplus
extern "C"
{
#endif

	typedef struct ClusterLongLong_
	{
		union
		{
			struct
			{
				unsigned char A;
				unsigned char B;
				unsigned char C;
				unsigned char D;
				unsigned char E;
				unsigned char F;
				unsigned char G;
				unsigned char H;
			};

			unsigned char Data[8];

			unsigned long long Value;
		};
	}ClusterLongLong;

#ifdef __cplusplus
}
#endif

#endif