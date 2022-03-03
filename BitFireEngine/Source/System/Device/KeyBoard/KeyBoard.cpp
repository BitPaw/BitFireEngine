#include "KeyBoard.h"

BF::KeyBoard::KeyBoard()
{
	Reset();
}

void BF::KeyBoard::IncrementButtonTick()
{
	A.IncrementIfAlreadyPressed();
	B.IncrementIfAlreadyPressed();
	C.IncrementIfAlreadyPressed();
	D.IncrementIfAlreadyPressed();
	E.IncrementIfAlreadyPressed();
	F.IncrementIfAlreadyPressed();
	G.IncrementIfAlreadyPressed();
	H.IncrementIfAlreadyPressed();
	I.IncrementIfAlreadyPressed();
	J.IncrementIfAlreadyPressed();
	K.IncrementIfAlreadyPressed();
	L.IncrementIfAlreadyPressed();
	M.IncrementIfAlreadyPressed();
	N.IncrementIfAlreadyPressed();
	O.IncrementIfAlreadyPressed();
	P.IncrementIfAlreadyPressed();
	Q.IncrementIfAlreadyPressed();
	R.IncrementIfAlreadyPressed();
	S.IncrementIfAlreadyPressed();
	T.IncrementIfAlreadyPressed();
	U.IncrementIfAlreadyPressed();
	V.IncrementIfAlreadyPressed();
	W.IncrementIfAlreadyPressed();
	X.IncrementIfAlreadyPressed();
	Y.IncrementIfAlreadyPressed();
	Z.IncrementIfAlreadyPressed();

	Zero.IncrementIfAlreadyPressed();
	One.IncrementIfAlreadyPressed();
	Two.IncrementIfAlreadyPressed();
	Three.IncrementIfAlreadyPressed();
	Four.IncrementIfAlreadyPressed();
	Five.IncrementIfAlreadyPressed();
	Six.IncrementIfAlreadyPressed();
	Seven.IncrementIfAlreadyPressed();
	Eight.IncrementIfAlreadyPressed();
	Nine.IncrementIfAlreadyPressed();

	ShitftLeft.IncrementIfAlreadyPressed();
	ShitftRight.IncrementIfAlreadyPressed();

	SpaceBar.IncrementIfAlreadyPressed();
}

void BF::KeyBoard::Reset()
{

}