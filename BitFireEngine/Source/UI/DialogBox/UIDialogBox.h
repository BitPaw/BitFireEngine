#pragma once

#include <Container/Queue.hpp>

#include "../UIText.h"

#include "../../Dialog/Dialog.h"
#include "../../Resource/Sprite.h"

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
		Sprite BackGroundTexture;
		UIText Content;

		void Open();
		void Close();
		void AddMessage(Dialog dialog);
		Dialog GetNextMessage();
		bool HasMessages();
	};
}