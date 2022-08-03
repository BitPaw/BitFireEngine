#pragma once

namespace BF
{
	struct KeyBoardCache
	{
		public:
		unsigned char A;
		unsigned char B;
		unsigned char C;
		unsigned char D;
		unsigned char E;
		unsigned char F;
		unsigned char G;
		unsigned char H;
		unsigned char I;
		unsigned char J;
		unsigned char K;
		unsigned char L;
		unsigned char M;
		unsigned char N;
		unsigned char O;
		unsigned char P;
		unsigned char Q;
		unsigned char R;
		unsigned char S;
		unsigned char T;
		unsigned char U;
		unsigned char V;
		unsigned char W;
		unsigned char X;
		unsigned char Y;
		unsigned char Z;

		unsigned char Zero;
		unsigned char One;
		unsigned char Two;
		unsigned char Three;
		unsigned char Four;
		unsigned char Five;
		unsigned char Six;
		unsigned char Seven;
		unsigned char Eight;
		unsigned char Nine;

		unsigned char ShitftLeft;
		unsigned char ShitftRight;

		unsigned char SpaceBar;

		KeyBoardCache();

		void IncrementButtonTick();
		void Reset();
	};
}