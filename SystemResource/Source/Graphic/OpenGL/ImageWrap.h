#pragma once

namespace BF
{
	enum class ImageWrap
	{	
		Invalid,

		// Images will be used 'as is' and will not be streched whatsoever.
		NoModification,

		// Strech
		StrechEdges,	

		StrechEdgesAndMirror,

		// Tiles the image in a gridformat
		Repeat, 	

		// Tiles the image in a gridformat but also flip them every time.
		RepeatAndMirror,		
	};
}