#include "TrippelIndex.h"

BF::TrippelIndex::TrippelIndex() : TrippelIndex(-1, -1, -1)
{

}

BF::TrippelIndex::TrippelIndex(const unsigned int a, const unsigned int b, const unsigned int c)
{
	A = a;
	B = b;
	C = c;
}
