#pragma once

struct Adler32
{
	private:
	static const unsigned int _base = 65521U;
	static const unsigned int _nMax = 5552;

	public:
	static unsigned long Calculate(unsigned long adler, const unsigned char* buf, unsigned int len);
	static unsigned long Combine(unsigned long adler1, unsigned long adler2, __int64 len2);
};