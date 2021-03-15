#pragma once

#include "../Utility/Queue.hpp"
#include "../Resources/Dialog/Dialog.h"

namespace BF
{
	class DialogBox
	{
		private:
		Queue<Dialog> _messages;

		public:
		void AddMessage(Dialog dialog);
		Dialog GetNextMessage();
		bool HasMessages();
	};
}