#pragma once

#include "OpenEvent.h"
#include "CloseEvent.h"
#include "NewCharacterEvent.h"
#include "NewPageEvent.h"

#include "../../Utility/Queue.hpp"
#include "../../Resources/Dialog/Dialog.h"

namespace BF
{
	class DialogBox
	{
		private:
		Queue<Dialog> _messages;
		bool _isOpen;

		void SetActiveState(bool state);

		public:
		OpenEvent OnOpen;
		CloseEvent OnClose;
		NewPageEvent OnNewPage;
		NewCharacterEvent OnNewCharacter;

		void Open();
		void Close();
		void AddMessage(Dialog dialog);
		Dialog GetNextMessage();
		bool HasMessages();
	};
}