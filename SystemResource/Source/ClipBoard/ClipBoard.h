#pragma once

#include <Error/ActionResult.h>

#include "ClipBoardFormat.h"

namespace BF
{
	class ClipBoard
	{
		public:
		// Open clipboard, close it imedidly after using!
		// Fails if another window has the clipboard open.
		ActionResult Open();

		// Use this right after using!
		bool Close();

		ActionResult Set(const ClipBoardFormat format, const void* data);

		bool Clear();
	};
}
