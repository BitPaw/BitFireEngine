#pragma once

#define Primesdebug 0

namespace BF
{
	class Primes
	{
		public:
			static unsigned int firstPrimeInX(unsigned int input);
			static unsigned int Eula_phi(unsigned int input);
			static int Primefactors(unsigned int input, unsigned int* result, unsigned int size);
	};
}