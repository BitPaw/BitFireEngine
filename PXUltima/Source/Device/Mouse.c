#include "Mouse.h"

#include <Text/Text.h>

void MouseInputReset(Mouse* mouse)
{
}

void MouseInputPrint(Mouse* mouse)
{
	const size_t buttonTextSize = 2 + 4 * 8+1;
	char buttons[34+1];
	
	TextFromBinaryDataA(&mouse->Buttons, sizeof(unsigned int), buttons, buttonTextSize);

	printf
	(
		"+-----------+---------------|\n"
		"| Position  | %-5i / %-5i |\n"
		"| InputAxis | %-5i / %-5i |\n"
		"| Buttons   | %s |\n"
		"+-----------+---------------|\n",
		mouse->Position[0],
		mouse->Position[1],
		mouse->InputAxis[0],
		mouse->InputAxis[1],
		buttons
	);
}