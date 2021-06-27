#include "UIDialogBox.h"

void BF::UIDialogBox::SetActiveState(bool shallBeOpen)
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

void BF::UIDialogBox::Open()
{
	SetActiveState(true);
}

void BF::UIDialogBox::Close()
{
	SetActiveState(false);
}

void BF::UIDialogBox::AddMessage(Dialog dialog)
{
	_messages.Add(dialog);
}

BF::Dialog BF::UIDialogBox::GetNextMessage()
{
	return _messages.GetNext();
}

bool BF::UIDialogBox::HasMessages()
{
	return !_messages.IsEmpty();
}
