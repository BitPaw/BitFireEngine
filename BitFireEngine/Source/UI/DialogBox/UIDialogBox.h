#pragma once

#include "../../../../SystemResource/Source/Container/Queue.hpp"
#include "../../../../SystemResource/Source/Dialog/Dialog.h"

namespace BF
{
	class UIDialogBox
	{
		private:
		Queue<Dialog> _messages;
		bool _isOpen;

		void SetActiveState(bool state);

		public:
		//OpenEvent OnOpen;
		//CloseEvent OnClose;
		//NewPageEvent OnNewPage;
		

		void Open();
		void Close();
		void AddMessage(Dialog dialog);
		Dialog GetNextMessage();
		bool HasMessages();
	};
}