#include <Math/Primes.h>
#include <Math/Math.h>

#ifdef Primesdebug
#include <stdio.h>
#endif

unsigned int BF::Primes::firstPrimeInX(unsigned int input)
{
	int check_up_to = MathSquareRoot(input);
	#if Primesdebug
	printf("Checking up to %d if the Number is Prime\n", check_up_to);
	#endif
	for (int i = 2; i <= check_up_to; i++)
	{
		if (i > 2 && !(i & 0b1)) continue;
		if (input % i == 0)
		{
			#if Primesdebug
			printf("%d teilt %d\n", i, input);
			#endif
			return i;
		}
		#if Primesdebug
		for (int j = 2; j <= i; j++)
		{
			if (j > 2 && !(j & 0b1)) continue;
			if (i % j == 0 && j == i)
			{
				printf("%d teilt nicht %d\n", j, input);
			}
		}
		#endif
	}
	#if Primesdebug
	printf("%d ist eine Priemzahl\n", input);
	#endif
	return input;
}

unsigned int BF::Primes::Eula_phi(unsigned int input)
{
	if (firstPrimeInX(input) == input)
	{
		return input - 1;
	}

	unsigned int primes[28] = { 0 };

	BF::Primes::Primefactors(input, primes, 14);

	int result = 1;
	for (unsigned int i = 0; i < 14; i++)
	{
		if (primes[i * 2] == 0)
		{
			break;
		}
		result *= MathPower(primes[i * 2], primes[i * 2 + 1] - 1) * (primes[i * 2] - 1);
	}
	return result;
}

int BF::Primes::Primefactors(unsigned int input, unsigned int* result, unsigned int size)
{
	int rest = input;
	while (rest != 1)
	{
		int prime = firstPrimeInX(rest);
		for (int i = 0; i < size; i++)
		{
			if (result[i * 2] == prime)
			{
				result[i * 2 + 1]++;
				break;
			}
			if (result[i * 2] == 0)
			{
				result[i * 2] = prime;
				result[i * 2 + 1] = 1;
				break;
			}
		}
		rest /= prime;
	}
	return 0;
}
