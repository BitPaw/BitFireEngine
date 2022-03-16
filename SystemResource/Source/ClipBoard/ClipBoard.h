#pragma once

#include "../ErrorCode.h"
#include "ClipBoardFormat.h"

namespace BF
{
	class ClipBoard
	{
		public:
		// Open clipboard, close it imedidly after using!
		// Fails if another window has the clipboard open.
		ErrorCode Open();

		// Use this right after using!
		bool Close();

		ErrorCode Set(const ClipBoardFormat format, const void* data);

		bool Clear();
	};
}