#include "InputButton.h"

BF::InputButton::InputButton()
{
    Value = 0x00;
}

bool BF::InputButton::IsShortPressed()
{
    return Value > 0 && Value < 0xA0;
}

bool BF::InputButton::IsLongPressed()
{
    return Value >= 0xA0;
}

bool BF::InputButton::IsPressed()
{
    return Value > 0;
}
