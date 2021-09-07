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
	switch (endian)
	{
		case Endian::Big:
			return
				(ByteData[0] << 56LL) |
				(ByteData[1] << 48LL) |
				(ByteData[2] << 40LL) |
				(ByteData[3] << 32LL) |
				(ByteData[4] << 24LL) |
				(ByteData[5] << 16LL) |
				(ByteData[6] << 8LL) |
				(ByteData[7]);

		default:
		case Endian::Little:
			return
				(ByteData[0]) |
				(ByteData[1] << 8LL) |
				(ByteData[2] << 16LL) |
				(ByteData[3] << 24LL) |
				(ByteData[4] << 32LL) |
				(ByteData[5] << 40LL) |
				(ByteData[6] << 48LL) |
				(ByteData[7] << 56LL);
	}
}

void BF::QuadWord::InsertLongLong(Endian endian, unsigned long long value)
{

}
