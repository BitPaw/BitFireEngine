#pragma once
#include <stdlib.h>
#include "Euklid_element.h"
class Euklid {	
public:
	Euklid_element* liste;
	int ggt;
	Euklid(int a, int b);
	void Advanced();
	void print();
};
