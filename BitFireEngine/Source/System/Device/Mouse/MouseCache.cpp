#include "MouseCache.h"

BF::MouseCache::MouseCache()
{
	ResetInput();
}

void BF::MouseCache::ResetInput()
{
	Position[0] = 0;
	Position[1] = 0;
	ResetAxis();

	LeftButton = 0;
	ScrollButton = 0;
	RightButton = 0;

	CustomButton1 = 0;
	CustomButton2 = 0;
	CustomButton3 = 0;
	CustomButton4 = 0;
	CustomButton5 = 0;
}

void BF::MouseCache::ResetAxis()
{
	InputAxis[0] = 0;
	InputAxis[1] = 0;
}