#include "KeyBoardCache.h"

#include <Device/InputButton.h>

BF::KeyBoardCache::KeyBoardCache()
{
	Reset();
}

void BF::KeyBoardCache::IncrementButtonTick()
{
	InputButtonIncrementIfAlreadyPressed(&A);
	InputButtonIncrementIfAlreadyPressed(&B);
	InputButtonIncrementIfAlreadyPressed(&C);
	InputButtonIncrementIfAlreadyPressed(&D);
	InputButtonIncrementIfAlreadyPressed(&E);
	InputButtonIncrementIfAlreadyPressed(&F);
	InputButtonIncrementIfAlreadyPressed(&G);
	InputButtonIncrementIfAlreadyPressed(&H);
	InputButtonIncrementIfAlreadyPressed(&I);
	InputButtonIncrementIfAlreadyPressed(&J);
	InputButtonIncrementIfAlreadyPressed(&K);
	InputButtonIncrementIfAlreadyPressed(&L);
	InputButtonIncrementIfAlreadyPressed(&M);
	InputButtonIncrementIfAlreadyPressed(&N);
	InputButtonIncrementIfAlreadyPressed(&O);
	InputButtonIncrementIfAlreadyPressed(&P);
	InputButtonIncrementIfAlreadyPressed(&Q);
	InputButtonIncrementIfAlreadyPressed(&R);
	InputButtonIncrementIfAlreadyPressed(&S);
	InputButtonIncrementIfAlreadyPressed(&T);
	InputButtonIncrementIfAlreadyPressed(&U);
	InputButtonIncrementIfAlreadyPressed(&V);
	InputButtonIncrementIfAlreadyPressed(&W);
	InputButtonIncrementIfAlreadyPressed(&X);
	InputButtonIncrementIfAlreadyPressed(&Y);
	InputButtonIncrementIfAlreadyPressed(&Z);

	InputButtonIncrementIfAlreadyPressed(&Zero);
	InputButtonIncrementIfAlreadyPressed(&One);
	InputButtonIncrementIfAlreadyPressed(&Two);
	InputButtonIncrementIfAlreadyPressed(&Three);
	InputButtonIncrementIfAlreadyPressed(&Four);
	InputButtonIncrementIfAlreadyPressed(&Five);
	InputButtonIncrementIfAlreadyPressed(&Six);
	InputButtonIncrementIfAlreadyPressed(&Seven);
	InputButtonIncrementIfAlreadyPressed(&Eight);
	InputButtonIncrementIfAlreadyPressed(&Nine);

	InputButtonIncrementIfAlreadyPressed(&ShitftLeft);
	InputButtonIncrementIfAlreadyPressed(&ShitftRight);

	InputButtonIncrementIfAlreadyPressed(&SpaceBar);
}

void BF::KeyBoardCache::Reset()
{

}