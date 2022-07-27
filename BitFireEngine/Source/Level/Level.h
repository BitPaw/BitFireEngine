#pragma once

#include <File/Image.h>
#include <File/Font.h>

#include <Model/Model.h>
#include <Media/Sound/Sound.h>
#include <Error/ActionResult.h>
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

		ActionResult Load(const wchar_t* filePath);

		size_t FullSizeInMemory();
	};
}