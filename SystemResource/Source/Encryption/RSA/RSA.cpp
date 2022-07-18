#include "RSA.h"

#include "Euklid.h"

#include <Text/Text.h>

#include <Hardware/Memory/Memory.h>
#include <Math/Primes.h>
#include <Math/Math.h>

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

	if (BF::Primes::firstPrimeInX(p) != p && BF::Primes::firstPrimeInX(q) != q)
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

#if RSAdebug
	euklid.print();
#endif

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

	unsigned int p = BF::Primes::firstPrimeInX(n);

	if (BF::Primes::firstPrimeInX(n / p) != 0)
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

#if RSAdebug
	euklid.print();
#endif

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
	int length = TextLengthA(m, TextUnkownLength);
	char* encoded = BF::Memory::Allocate<char>(length + 1);

	TextCopyA(m, length, encoded, length);

	for (int i = 0; i < length; i++)
	{
		unsigned int current_char = encoded[i] >= 0 ? encoded[i] : 256 + encoded[i];

		current_char = current_char < (p* q) ? current_char : 1;

		encoded[i] = MathPowerModulo(current_char, publicKey.f, publicKey.n);
	}
	return encoded;
}

unsigned int RSA::encode_message(unsigned int m)
{
	if (!publicKey.valid || m <= 0 || m >= (p * q))
	{
		return -1;
	}
	return MathPowerModulo(m, publicKey.f, publicKey.n);
}

char* RSA::decode_message(const char* c)
{
	if (!privateKey.valid || c == nullptr)
	{
		return nullptr;
	}

	int length = TextLengthA(c, TextUnkownLength);
	char* decoded = BF::Memory::Allocate<char>(length + 1);
	TextCopyA(c, length, decoded, length);

	for (int i = 0; i < length; i++)
	{
		unsigned int current_char = decoded[i] >= 0 ? decoded[i] : 256 + decoded[i];

		current_char = current_char < (p* q) ? current_char : 1;

		decoded[i] = MathPowerModulo(current_char, privateKey.f, privateKey.n);
	}
	return decoded;
}

unsigned int RSA::decode_message(unsigned int c)
{
	if (!privateKey.valid || c <= 0 || c >= (p * q))
	{
		return -1;
	}
	return MathPowerModulo(c, privateKey.f, privateKey.n);
}

unsigned int RSA::number_of_Publickeys()
{
	if (!publicKey.valid)
	{
		return 0;
	}
	return BF::Primes::Eula_phi(phi_n);
}