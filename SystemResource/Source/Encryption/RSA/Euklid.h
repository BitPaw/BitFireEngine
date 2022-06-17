#pragma once

#include "Euklid_element.h"

#define Eukliddebug 0

class Euklid
{
	public:
	Euklid_element* liste;
	int ggt;

	Euklid(int a, int b);

	void Advanced();
#if Eukliddebug
	void print();
#endif
};