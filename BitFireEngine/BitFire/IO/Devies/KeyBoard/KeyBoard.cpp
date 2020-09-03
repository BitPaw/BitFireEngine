#include "KeyBoard.h"

KeyBoard::KeyBoard()
{
	Reset();
}

void KeyBoard::Reset()
{
	Letter.Reset();
	FunktionKey.Reset();

	SpaceBar = false;
}