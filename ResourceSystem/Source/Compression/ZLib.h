#pragma once

class ZLib
{
	public:
	static int Compress(const char* source, const char* target);
	static int Compress(const char* source, const char* target, int level);
	static int Decompress(const char* source, const char* target);
};