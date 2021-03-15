#pragma once

#include "../Utility/ASCIIString.h"
#include "../Utility/List.hpp"
#include "../Resources/Model/Model.h"
#include "../Resources/Image/Image.h"
#include "../Resources/Font/Font.h"
#include "../Resources/Sound/Sound.h"
#include "../Resources/Dialog/Dialog.h"

namespace BF
{
	class Level
	{
	public:
		unsigned int ID;
		ASCIIString Name;

		// Physics Container
		List<Model> ModelList;
		List<Image> ImageList;
		List<Sound> SoundList;
		List<Font> FontList;
		List<Shader> ShaderList;
		List<Dialog> DialogList;

		Level()
		{
			ID = -1;
			Name.Copy("[N/A]");
		}
	};
}