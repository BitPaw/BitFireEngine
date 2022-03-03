#include "pch.h"
#include "CppUnitTest.h"

#include <Container/BitStreamHusk.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace BF;

namespace TestSystemResource
{
	TEST_CLASS(TestSystemResource)
	{
		public:
        TEST_METHOD(BitShift)
        {
            unsigned char bitStuff[4] = { 0b11000111, 0b001110001 ,0b10001110 ,0b00001111 };

            BitStreamHusk bitStreamHusk(bitStuff, 4);

            unsigned int nr = 1;

            for (size_t i = 0; i < 20; i++)
            {
                BitStreamHusk::PrintBinary(nr);

                nr <<= 1;
            }

            BitStreamHusk::PrintBinary((unsigned int)bitStuff);

            unsigned int a = bitStreamHusk.ExtractBitsAndMove(3);
            unsigned int b = bitStreamHusk.ExtractBitsAndMove(3);
            unsigned int c = bitStreamHusk.ExtractBitsAndMove(3);
            unsigned int d = bitStreamHusk.ExtractBitsAndMove(3);
            unsigned int e = bitStreamHusk.ExtractBitsAndMove(3);
            unsigned int f = bitStreamHusk.ExtractBitsAndMove(3);
            unsigned int g = bitStreamHusk.ExtractBitsAndMove(3);
            unsigned int h = bitStreamHusk.ExtractBitsAndMove(3);
            unsigned int i = bitStreamHusk.ExtractBitsAndMove(5);
            unsigned int j = bitStreamHusk.ExtractBitsAndMove(4);

            Assert::IsTrue(false, L"Noot implemented");
        }
	};
}
