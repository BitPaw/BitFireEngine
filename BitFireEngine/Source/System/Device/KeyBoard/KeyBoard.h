#pragma once

#include "../InputButton.h"

namespace BF
{
	class KeyBoard
	{

		public:
		InputButton A;
		InputButton B;
		InputButton C;
		InputButton D;
		InputButton E;
		InputButton F;
		InputButton G;
		InputButton H;
		InputButton I;
		InputButton J;
		InputButton K;
		InputButton L;
		InputButton M;
		InputButton N;
		InputButton O;
		InputButton P;
		InputButton Q;
		InputButton R;
		InputButton S;
		InputButton T;
		InputButton U;
		InputButton V;
		InputButton W;
		InputButton X;
		InputButton Y;
		InputButton Z;

		InputButton Zero;
		InputButton One;
		InputButton Two;
		InputButton Three;
		InputButton Four;
		InputButton Five;
		InputButton Six;
		InputButton Seven;
		InputButton Eight;
		InputButton Nine;

		InputButton ShitftLeft;
		InputButton ShitftRight;

		InputButton SpaceBar;

		KeyBoard();

		void IncrementButtonTick();
		void Reset();
	};
}