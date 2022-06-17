#include <Math/Primes.h>
#include <Math/Math.h>
#include <map>

#ifdef Primesdebug
#include <stdio.h>
#endif

unsigned int BF::Primes::firstPrimeInX(unsigned int input)
{
	int check_up_to = BF::Math::SquareRoot(input);
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

	std::map<int, int> primes;
	int rest = input;

	while (rest != 1)
	{
		int i = firstPrimeInX(rest);
		primes[i] = primes[i]++;
		rest /= i;
	}
	int result = 1;
	for (auto element : primes)
	{
		result *= BF::Math::Power(element.first, element.second - 1) * (element.first - 1);
	}
	return result;
}
