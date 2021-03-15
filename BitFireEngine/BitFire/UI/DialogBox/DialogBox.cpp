#include "DialogBox.h"

void BF::DialogBox::SetActiveState(bool shallBeOpen)
{
	bool isAlreadyInThisState = shallBeOpen == _isOpen;

	if (isAlreadyInThisState)
	{
		throw;
	}
	else
	{
		_isOpen = shallBeOpen;

		if (shallBeOpen)
		{
			//OnOpen;
			
		}
		else
		{
			//OnClose;
		}
	}
}

void BF::DialogBox::Open()
{
	SetActiveState(true);
}

void BF::DialogBox::Close()
{
	SetActiveState(false);
}

void BF::DialogBox::AddMessage(Dialog dialog)
{
	_messages.Add(dialog);
}

BF::Dialog BF::DialogBox::GetNextMessage()
{
	return _messages.GetNext();
}

bool BF::DialogBox::HasMessages()
{
	return !_messages.IsEmpty();
}
