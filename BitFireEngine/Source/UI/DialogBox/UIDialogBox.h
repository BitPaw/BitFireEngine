#pragma once

#include "OpenEvent.h"
#include "CloseEvent.h"
#include "NewCharacterEvent.h"
#include "NewPageEvent.h"

#include "../../../ResourceSystem/Dialog/Dialog.h"
#include "../../../ResourceSystem/Container/Queue.hpp"

namespace BF
{
	class UIDialogBox
	{
		private:
		Queue<Dialog> _messages;
		bool _isOpen;

		void SetActiveState(bool state);

		public:
		OpenEvent OnOpen;
		CloseEvent OnClose;
		NewPageEvent OnNewPage;
		

		void Open();
		void Close();
		void AddMessage(Dialog dialog);
		Dialog GetNextMessage();
		bool HasMessages();
	};
}