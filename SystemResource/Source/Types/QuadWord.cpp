#include "QuadWord.h"

BF::QuadWord::QuadWord()
{
	ByteData[0] = 0;
	ByteData[1] = 0;
	ByteData[2] = 0;
	ByteData[3] = 0;
	ByteData[4] = 0;
	ByteData[5] = 0;
	ByteData[6] = 0;
	ByteData[7] = 0;
}

BF::QuadWord::QuadWord(unsigned char byteA, unsigned char byteB, unsigned char byteC, unsigned char byteD, unsigned char byteE, unsigned char byteF, unsigned char byteG, unsigned char byteH)
{
	ByteData[0] = byteA;
	ByteData[1] = byteB;
	ByteData[2] = byteC;
	ByteData[3] = byteD;
	ByteData[4] = byteE;
	ByteData[5] = byteF;
	ByteData[6] = byteG;
	ByteData[7] = byteH;
}

void BF::QuadWord::Set(unsigned char byteA, unsigned char byteB, unsigned char byteC, unsigned char byteD, unsigned char byteE, unsigned char byteF, unsigned char byteG, unsigned char byteH)
{
	ByteData[0] = byteA;
	ByteData[1] = byteB;
	ByteData[2] = byteC;
	ByteData[3] = byteD;
	ByteData[4] = byteE;
	ByteData[5] = byteF;
	ByteData[6] = byteG;
	ByteData[7] = byteH;
}

unsigned long long BF::QuadWord::ExtractLongLong(Endian endian)
{
	unsigned long long a = ByteData[0];
	unsigned long long b = ByteData[1];
	unsigned long long c = ByteData[2];
	unsigned long long d = ByteData[3];
	unsigned long long e = ByteData[4];
	unsigned long long f = ByteData[5];
	unsigned long long g = ByteData[6];
	unsigned long long h = ByteData[7];

	switch (endian)
	{
		case Endian::Big:
			return
				(a << 56LL) |
				(b << 48LL) |
				(c << 40LL) |
				(d << 32LL) |
				(e << 24LL) |
				(f << 16LL) |
				(g << 8LL) |
				(h);

		default:
		case Endian::Little:
			return
				(a) |
				(b << 8LL) |
				(c << 16LL) |
				(d << 24LL) |
				(e << 32LL) |
				(f << 40LL) |
				(g << 48LL) |
				(h << 56LL);
	}
}

void BF::QuadWord::InsertLongLong(Endian endian, unsigned long long value)
{

}
