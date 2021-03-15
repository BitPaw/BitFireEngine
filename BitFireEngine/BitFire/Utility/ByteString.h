#pragma once

#include <string>

#include "../Utility/List.hpp"
#include "../IO/EndianType.h"
#include "../Mathematic/Math.h"

namespace BF
{
	class ByteString
	{
		private:
		List<unsigned char> _data;

		public:				
		unsigned char& operator[](unsigned int value);
		

		void ReSize(unsigned int size);
		unsigned int Size();		
		unsigned int ToUnsignedInt();
		void Copy(std::string byteString);

		static unsigned int ToUnsignedInt(EndianType type, unsigned char byteA, unsigned char byteB);
		static unsigned int ToUnsignedInt(EndianType type, unsigned char byteA, unsigned char byteB, unsigned char byteC, unsigned char byteD);	
	};
}