#pragma once

#include <Model/Model.h>
#include <Media/Image/Image.h>
#include <Media/Font/Font.h>
#include <Media/Sound/Sound.h>
#include <File/FileActionResult.hpp>
#include <Camera/Camera.h>

#include <Graphic/OpenGL/Texture.h>

#include <Video/Shader.h>

#include "../Dialog/Dialog.h"


namespace BF
{
	class Level : public Resource
	{
		public:
		// Physics Container
		List<Model*> ModelList;
		List<Texture*> TextureList;
		List<Sound*> SoundList;
		List<Font*> FontList;
		List<Shader*> ShaderList;
		List<Dialog*> DialogList;
		List<Camera*> CameraList;

		static bool IsLevelFile(const wchar_t* filePath);

		FileActionResult Load(const wchar_t* filePath);

		size_t FullSizeInMemory();
	};
}