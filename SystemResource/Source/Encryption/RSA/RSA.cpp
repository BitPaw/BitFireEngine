#include "RSA.h"
#include <math.h>
#include <iostream>
#include "Euklid.h"
#include <Text/Text.h>

RSA::RSA(int p, int q, int e)
{

	if (p == 0 || q == 0)
	{
		return;
	}

	if (p == q)
	{
		return;
	}

	if (Primes_Print(p) != 0 && Primes_Print(q) != 0)
	{
		return;
	}

	RSA::p = p;
	RSA::q = q;
	phi_n = (q - 1) * (p - 1);

	if (e<1 || e>phi_n)
	{
		return;
	}

	if (e % q == 0 || e % p == 0)
	{
		return;
	}

	Euklid euklid(phi_n, e);
	euklid.Advanced();
	euklid.print();

	if (euklid.ggt != 1)
	{
		return;
	}

	publicKey.n = p * q;
	publicKey.f = e;
	publicKey.valid = true;

	privateKey.n = p * q;
	privateKey.f = euklid.liste[0].y < 1 ? euklid.liste[0].y + phi_n : euklid.liste[0].y;
	privateKey.valid = true;
}
RSA::RSA(int n, int e)
{
	if (n == 0)
	{
		return;
	}

	unsigned int p = Primes_Print(n);

	if (Primes_Print(n / p) != 0)
	{
		return;
	}

	if (p == n / p)
	{
		return;
	}

	RSA::p = p;
	RSA::q = n / p;
	phi_n = (q - 1) * (p - 1);

	if (e<1 || e>phi_n)
	{
		return;
	}

	if (e % q == 0 || e % p == 0)
	{
		return;
	}

	Euklid euklid(phi_n, e);
	euklid.Advanced();
	euklid.print();

	if (euklid.ggt != 1)
	{
		return;
	}

	publicKey.n = p * q;
	publicKey.f = e;
	publicKey.valid = true;

	privateKey.n = p * q;
	privateKey.f = euklid.liste[0].y < 1 ? euklid.liste[0].y + phi_n : euklid.liste[0].y;
	privateKey.valid = true;

}
RSA::RSA()
{
	RSA::p = 0;
	RSA::q = 0;
	RSA::phi_n = 0;
	publicKey.valid = false;
	privateKey.valid = false;
}

RSAKey RSA::public_key()
{
	return publicKey;
}

RSAKey RSA::private_key()
{
	return privateKey;
}

char* RSA::encode_message(const char* m)
{
	if (!publicKey.valid || m == nullptr)
	{
		return nullptr;
	}
	int length = strlen(m);
	char* encoded = (char*)malloc(length * sizeof(char) + 1);
	strcpy(encoded, m);

	for (int i = 0; i < length; i++)
	{
		unsigned int current_char = encoded[i] >= 0 ? encoded[i] : 256 + encoded[i];

		current_char = current_char < (p* q) ? current_char : 1;

		encoded[i] = pow_mod(current_char, publicKey.f, publicKey.n);
	}
	return encoded;
}

int RSA::encode_message(int m)
{
	if (!publicKey.valid || m <= 0 || m >= (p * q))
	{
		return -1;
	}
	return pow_mod(m, publicKey.f, publicKey.n);
}

char* RSA::decode_message(const char* c)
{
	if (!privateKey.valid || c == nullptr)
	{
		return nullptr;
	}

	int length = strlen(c);
	char* decoded = (char*)malloc(length * sizeof(char) + 1);
	strcpy(decoded, c);

	for (int i = 0; i < length; i++)
	{
		unsigned int current_char = decoded[i] >= 0 ? decoded[i] : 256 + decoded[i];

		current_char = current_char < (p* q) ? current_char : 1;

		decoded[i] = pow_mod(current_char, privateKey.f, privateKey.n);
	}
	return decoded;
}

int RSA::decode_message(int c)
{
	if (!privateKey.valid || c <= 0 || c >= (p * q))
	{
		return -1;
	}
	return pow_mod(c, privateKey.f, privateKey.n);
}

unsigned int RSA::number_of_Publickeys()
{
	int rest = phi_n;
	if (!publicKey.valid)
	{
		return 0;
	}
	while (rest != 1)
	{
		int i = 2;
		while (rest % i != 0)
		{
			i++;
		}
		primes[i] = primes[i]++;
		rest /= i;
	}
	int result = 1;
	for (auto element : primes)
	{
		result *= pow(element.first, element.second - 1) * (element.first - 1);
	}
	return result;
}

unsigned int RSA::Primes(unsigned int input)
{
	int check_up_to = sqrt(input);
	for (int i = 2; i < check_up_to; i++)
	{
		if (input % i == 0)
		{
			return i;
		}
	}
	return 0;
}

unsigned int RSA::Primes_Print(unsigned int input)
{
	int check_up_to = sqrt(input);
	for (int i = 2; i < check_up_to; i++)
	{
		if (input % i == 0)
		{
			printf("%d teilt %d\n", i, input);
			return i;
		}
		for (int j = 2; j <= i; j++)
		{
			if (i % j == 0 && j != i)
			{
				break;
			}
			else if (i % j == 0 && j == i)
			{
				printf("%d teilt nicht %d\n", j, input);
			}

		}
	}
	return 0;
}

unsigned int pow_mod(unsigned int base, unsigned int exp, unsigned int mod)
{
	unsigned int result = 1;
	for (int i = 0; i < exp; i++)
	{
		result *= base;
		result %= mod;
	}
	return result;
}