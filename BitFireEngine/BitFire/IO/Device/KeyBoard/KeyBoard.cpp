#include "KeyBoard.h"

BF::KeyBoard::KeyBoard()
{
	Reset();
}

void BF::KeyBoard::Reset()
{
	Letter.Reset();
	FunktionKey.Reset();

	SpaceBar = false;
}