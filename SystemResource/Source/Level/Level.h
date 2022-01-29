#pragma once

#include "../Model/Model.h"
#include "../Image/Image.h"
#include "../Font/Font.h"
#include "../Sound/Sound.h"
#include "../Dialog/Dialog.h"
#include "../Camera/Camera.h"
#include "../Shader/Shader.h"

#include "../File/FileActionResult.hpp"

namespace BF
{
	class Level : public Resource
	{
		public:
		// Physics Container
		List<Model*> ModelList;
		List<Image*> ImageList;
		List<Sound*> SoundList;
		List<Font*> FontList;
		List<Shader*> ShaderList;
		List<Dialog*> DialogList;
		List<Camera*> CameraList;

		Level();

		static bool IsLevelFile(const wchar_t* filePath);

		FileActionResult Load();
	};
}