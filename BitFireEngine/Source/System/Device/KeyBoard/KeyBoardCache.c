#include "KeyBoardCache.h"

#include <OS/Memory/PXMemory.h>
#include <Device/InputButton.h>

void KeyBoardCacheConstruct(KeyBoardCache* const keyBoardCache)
{
	KeyBoardCacheReset(keyBoardCache);
}

void KeyBoardCacheIncrementButtonTick(KeyBoardCache* const keyBoardCache)
{
	InputButtonIncrementIfAlreadyPressed(&keyBoardCache->A);
	InputButtonIncrementIfAlreadyPressed(&keyBoardCache->B);
	InputButtonIncrementIfAlreadyPressed(&keyBoardCache->C);
	InputButtonIncrementIfAlreadyPressed(&keyBoardCache->D);
	InputButtonIncrementIfAlreadyPressed(&keyBoardCache->E);
	InputButtonIncrementIfAlreadyPressed(&keyBoardCache->F);
	InputButtonIncrementIfAlreadyPressed(&keyBoardCache->G);
	InputButtonIncrementIfAlreadyPressed(&keyBoardCache->H);
	InputButtonIncrementIfAlreadyPressed(&keyBoardCache->I);
	InputButtonIncrementIfAlreadyPressed(&keyBoardCache->J);
	InputButtonIncrementIfAlreadyPressed(&keyBoardCache->K);
	InputButtonIncrementIfAlreadyPressed(&keyBoardCache->L);
	InputButtonIncrementIfAlreadyPressed(&keyBoardCache->M);
	InputButtonIncrementIfAlreadyPressed(&keyBoardCache->N);
	InputButtonIncrementIfAlreadyPressed(&keyBoardCache->O);
	InputButtonIncrementIfAlreadyPressed(&keyBoardCache->P);
	InputButtonIncrementIfAlreadyPressed(&keyBoardCache->Q);
	InputButtonIncrementIfAlreadyPressed(&keyBoardCache->R);
	InputButtonIncrementIfAlreadyPressed(&keyBoardCache->S);
	InputButtonIncrementIfAlreadyPressed(&keyBoardCache->T);
	InputButtonIncrementIfAlreadyPressed(&keyBoardCache->U);
	InputButtonIncrementIfAlreadyPressed(&keyBoardCache->V);
	InputButtonIncrementIfAlreadyPressed(&keyBoardCache->W);
	InputButtonIncrementIfAlreadyPressed(&keyBoardCache->X);
	InputButtonIncrementIfAlreadyPressed(&keyBoardCache->Y);
	InputButtonIncrementIfAlreadyPressed(&keyBoardCache->Z);

	InputButtonIncrementIfAlreadyPressed(&keyBoardCache->Zero);
	InputButtonIncrementIfAlreadyPressed(&keyBoardCache->One);
	InputButtonIncrementIfAlreadyPressed(&keyBoardCache->Two);
	InputButtonIncrementIfAlreadyPressed(&keyBoardCache->Three);
	InputButtonIncrementIfAlreadyPressed(&keyBoardCache->Four);
	InputButtonIncrementIfAlreadyPressed(&keyBoardCache->Five);
	InputButtonIncrementIfAlreadyPressed(&keyBoardCache->Six);
	InputButtonIncrementIfAlreadyPressed(&keyBoardCache->Seven);
	InputButtonIncrementIfAlreadyPressed(&keyBoardCache->Eight);
	InputButtonIncrementIfAlreadyPressed(&keyBoardCache->Nine);

	InputButtonIncrementIfAlreadyPressed(&keyBoardCache->ShitftLeft);
	InputButtonIncrementIfAlreadyPressed(&keyBoardCache->ShitftRight);

	InputButtonIncrementIfAlreadyPressed(&keyBoardCache->SpaceBar);
}

void KeyBoardCacheReset(KeyBoardCache* const keyBoardCache)
{
	MemoryClear(keyBoardCache, sizeof(KeyBoardCache));
}