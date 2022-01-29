#pragma once
#include <map>
#include "RSAKeys.h"

unsigned int pow_mod(unsigned int base, unsigned int exp, unsigned int mod);

class RSA 
{
	std::map<int,int> primes;
public:
	unsigned int p=0;
	unsigned int q=0;
	unsigned int phi_n=0;
	RSAKey publicKey;
	RSAKey privateKey;
	RSA(int p,int q,int e);
	RSA(int n, int e);
	RSA();
	RSAKey public_key();
	RSAKey private_key();
	char* encode_message(const char* m);
	int encode_message(int m);
	char* decode_message(const char* c);
	int decode_message(int c);
	unsigned int number_of_Publickeys();
	unsigned int Primes(unsigned int input);
	unsigned int Primes_Print(unsigned int input);
};

