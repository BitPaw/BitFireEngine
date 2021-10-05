#pragma once

namespace BF
{
	struct JPEGFrameComponent
	{
		unsigned char ID;
		unsigned char Width;
		unsigned char Height;
		unsigned char Key;

		JPEGFrameComponent();
	};
}