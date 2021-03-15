#include "ByteString.h"

unsigned char& BF::ByteString::operator[](unsigned int value)
{	
	return _data[value];	
}

void BF::ByteString::ReSize(unsigned int size)
{
	_data.ReSize(size);
}

unsigned int BF::ByteString::Size()
{
	return _data.Size();
}

unsigned int BF::ByteString::ToUnsignedInt()
{
	return 0;
}

void BF::ByteString::Copy(std::string byteString)
{
	unsigned int length = byteString.length();

	ReSize(length);

	for (unsigned int i = 0; i < length; i++)
	{
		_data[i] = byteString[i];
	}
}

unsigned int BF::ByteString::ToUnsignedInt(EndianType type, unsigned char byteA, unsigned char byteB)
{
	switch (type)
	{
		case BF::EndianType::Big:
			return (byteA) | (byteB << 8);

		default:
		case BF::EndianType::Little:
			return (byteA << 8) | (byteB);
	}
}

unsigned int BF::ByteString::ToUnsignedInt(EndianType type, unsigned char byteA, unsigned char byteB, unsigned char byteC, unsigned char byteD)
{
	switch (type)
	{
		case BF::EndianType::Big:
			return (byteA) | (byteB << 8) | (byteC << 16) | (byteD << 24);

		default:
		case BF::EndianType::Little: 
			return (byteA << 24) | (byteB << 16) | (byteC << 8) | (byteD); 
	}	
}