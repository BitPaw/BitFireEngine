#pragma once

#include "Numbers.h"
#include "Alphabet.h"
#include "FunctionKeys.h"

namespace BF
{
	class KeyBoard
	{
		public:
		Numbers Number;
		Alphabet Letter;
		FunctionKeys FunktionKey;
		bool SpaceBar;

		KeyBoard();

		void Reset();
	};
}