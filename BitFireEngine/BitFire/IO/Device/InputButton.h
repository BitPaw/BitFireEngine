#pragma once

namespace BF
{
	struct InputButton
	{
		public:
		unsigned char Value;

		InputButton();

		inline void IncrementIfAlreadyPressed()	
		{
			if (Value > 0 && Value != 0xFF)
			{
				Value++;
			}			
		}

		bool IsShortPressed();
		bool IsLongPressed();
		bool IsPressed();
	};
}