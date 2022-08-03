#include "InputButton.h"

unsigned char InputButtonReset(unsigned char* value)
{
	*value = 0x00;
}

unsigned char InputButtonIncrement(unsigned char* value)
{
	if(*value != 0xFF)
	{
		++(*value);
	}
}

unsigned char InputButtonIncrementIfAlreadyPressed(unsigned char* value)
{
	if(*value > 0 && *value != 0xFF)
	{
		++(*value);
	}
}

unsigned char InputButtonIsShortPressed(const unsigned char value)
{
  return value > 0 && value < 0xA0;
}

unsigned char InputButtonIsLongPressed(const unsigned charvalue)
{
    return charvalue >= 0xA0;
}

unsigned char InputButtonIsPressed(const unsigned char value)
{
    return value > 0;
}
