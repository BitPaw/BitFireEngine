#include "TrippelIndex.h"

TrippelIndex::TrippelIndex() : TrippelIndex(-1, -1, -1)
{

}

TrippelIndex::TrippelIndex(const unsigned int a, const unsigned int b, const unsigned int c)
{
	A = a;
	B = b;
	C = c;
}
