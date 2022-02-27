#pragma once

namespace BF
{
	struct InputButton
	{
		public:
		unsigned char Value;

		InputButton();

		inline void Reset()
		{
			Value = 0x00;
		}

		inline void Increment()
		{
			if (Value != 0xFF)
			{
				++Value;
			}
		}

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