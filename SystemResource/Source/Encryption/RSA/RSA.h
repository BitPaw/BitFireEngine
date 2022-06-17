#pragma once

#include "RSAKeys.h"

#define RSAdebug 0

class RSA
{
	public:
	unsigned int p = 0;
	unsigned int q = 0;
	unsigned int phi_n = 0;
	RSAKey publicKey;
	RSAKey privateKey;

	RSA(int p, int q, int e);
	RSA(int n, int e);
	RSA();

	RSAKey public_key();
	RSAKey private_key();
	char* encode_message(const char* m);
	unsigned int encode_message(unsigned int m);
	char* decode_message(const char* c);
	unsigned int decode_message(unsigned int c);
	unsigned int number_of_Publickeys();
};