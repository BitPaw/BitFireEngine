#pragma once

#include "ResourceType.h"

#include "Shader/Shader.h"
#include "Shader/ShaderLoader.h"
#include "Image/Image.h"
#include "Image/ImageWrap.h"
#include "Image/ImageLoader.h"
#include "Model/Model.h"
#include "Model/ModelLoader.h"
#include "Sound/Sound.h"
#include "Font/Font.h"
#include "Font/FontLoader.h"
#include "Dialog/Dialog.h"

#include "../Utility/LinkedList.hpp"
#include "../Utility/AsciiString.h"
#include "../Graphics/Camera/FirstPersonCamera.h"
#include "../Level/Level.h"

namespace BF
{
    /*
    Stores resources and manages them to the GPU.
    */
	class ResourceManager
	{
	private:
        unsigned int _lastUsedShaderProgram = -1;

		LinkedList<Model*> _modelList;
        LinkedList<Image*> _imageList;
        LinkedList<Sound*> _soundList;
        LinkedList<Font*> _fontList;
        LinkedList<ShaderProgram*> _shaderProgramList;
        LinkedList<Dialog*> _dialogList;
        LinkedList<Level*> _levelList;

        unsigned int _defaultShaderID;
        unsigned int _defaultTextureID;

        int ImageWrapToOpenGLFormat(ImageWrap imageWrap);
        int ImageLayoutToOpenGLFormat(ImageLayout layout);

        void UpdateVBOData(Model& model);

        unsigned int CompileShader(unsigned int type, AsciiString& shaderString);

	public:
        FirstPersonCamera MainCamera;

		void PushToGPU(Model& model);
		void PushToGPU(Image& image);
		//void Add(Sound& sound);
		//void RegisterGPU(Font& font);
		void PushToGPU(ShaderProgram& shader);

		void Load(AsciiString& filePath);

        void AddShaderProgram(AsciiString& vertexShader, AsciiString& fragmentShader);

        void RenderModels(GameTickData& gameTickData);

		void PrintContent(bool detailed);
	};
}







/*
Image* a = ImageLoader::LoadFromFile("A:/W.bmp");
RegisterImage(a);
a->FlipHorizontal();
_openGL->MainWindow->SetCursorTexture(a);
_openGL->MainWindow->SetIcon(a);

Image* sandTexture = ImageLoader::LoadFromFile("A:/sand.bmp");
RegisterImage(sandTexture);

dirtTexture = ImageLoader::LoadFromFile("A:/W.bmp");
RegisterImage(dirtTexture);

Image* cobblestoneTexture = ImageLoader::LoadFromFile("A:/cobblestone.bmp");
RegisterImage(cobblestoneTexture);

Cube cube;
// Model* cubeModel = ModelLoader::ToModel(&cube);


// _currentMainCamera.UpdateSystemLink();

 // Shader
 AsciiString vertex("A:/_WorkSpace/BitFireEngine/Shader/WorldSpace.vert");
 AsciiString fragment("A:/_WorkSpace/BitFireEngine/Shader/WorldSpace.frag");

 worldShader = new ShaderWorldSpace();
 worldShader->AddShader
 (
     vertex,
     fragment
 );


 AttachShaderProgramm(worldShader);
 worldShader->FetchData();

 LevelLoader::worldShader = worldShader;

 ShaderHUD* hudShader = new ShaderHUD();
 AsciiString vertexHUD("A:/_WorkSpace/BitFireEngine/Shader/HUD.vert");
 AsciiString fragmentHUD("A:/_WorkSpace/BitFireEngine/Shader/HUD.frag");

 hudShader->AddShader // !!!! aaloc
 (
     vertexHUD,
     fragmentHUD
 );


 AttachShaderProgramm(hudShader);


















 AsciiString blockTexture("A:/_WorkSpace/BitFireEngine/Texture/Block.bmp");


 // Texture
 dirtTexture = ImageLoader::LoadFromFile(blockTexture);

 //RegisterImage(dirtTexture);






// Image* png = ImageLoader::LoadFromFile("Font/segoe.png");

 // Font
 AsciiString fontTextureFilePath("A:/_WorkSpace/BitFireEngine/Font/segoe.bmp");
 AsciiString fontFilePath("A:/_WorkSpace/BitFireEngine/Font/segoe.fnt");

 Image* fontTexture = ImageLoader::LoadFromFile(fontTextureFilePath);
 fontTexture->FlipHorizontal(); // !!! alloc

 FNT* fnt = FNTLoader::LoadFromFile(fontFilePath); // very bad alloc
 fnt->PrintData();
 RegisterImage(fontTexture);

 // Model
 AsciiString uiText("BitFireEngine 21.01.2021");
 text = new Text(uiText, fnt, -1, -0.9f);

 text->progremm = hudShader;
 text->ShaderID = hudShader->ID;
 //text->Scale(0.003, 0.003, 0.003);
//  text->SetTextPosition(1, 1);
  text->UsedTextureList.Add(fontTexture->Information.TextureID);
 // text->PrintModelData();
 // text->PrintObjectData();

  //RegisterModel(text);








  if (false)
  {
      AsciiString modelDust("A:/_WorkSpace/BitFireEngine/Model/Dust_II.obj");


      Model* map = ModelLoader::LoadFromFile(modelDust);
      //cubeModel->UsedTextureList.Add(fontTexture->Information.TextureID);
      //cubeModel->ScaleTexturePoints(50, 50);

      map->progremm = worldShader;
      map->ShaderID = worldShader->ID;
      //map->Rotate(0, 90, 0);

      map->Scale(0.05, 0.05, 0.05);
      map->Move(0, -13.5, 0);

      RegisterModel(map);




  }
  else
  {

  }




  AsciiString modelCube("A:/_WorkSpace/BitFireEngine/Model/QF.obj");

  cube = ModelLoader::LoadFromFile(modelCube);
  cube->progremm = worldShader;
  cube->ShaderID = worldShader->ID;
  cube->Scale(10, 10, 10);
  cube->UsedTextureList.Add(dirtTexture->Information.TextureID);


  cube->Move(-10,0,-30);
  RegisterModel(cube);


  /*





  Triangle triangle;

  Model* triangleModel = ModelLoader::ToModel(&triangle);
  triangleModel->Scale(20, 20, 20);
  RegisterModel(triangleModel);


  Rectangle rect2(0,0,25,25);

  Model* rect2eModel = ModelLoader::ToModel(&rect2);
  rect2eModel->Scale(20, 20, 20);
  RegisterModel(rect2eModel);

  /*

  Model* country = ModelLoader::LoadFromFile("A:/S.obj");
  country->UsedTextureList.Add(image->Information.TextureID);
  country->Scale(BF::Vector3(4, 6, 4));
 // country->Scale(BF::Vector3(0.02, 0.02, 0.02));
 country->MoveBy(BF::Vector3(-10, -2, 0));

  RegisterModel(country);








    if (lastUIUpdate > 0.05f && false)
      {
          lastUIUpdate = 0;
          Position<float> position = cube->CurrentRotation(); // _currentMainCamera->CurrentPosition;

          snprintf
          (
              &textbuffer[0],
              25,
              "P(%3.1f|%3.1f|%3.1f)\0",
              position.X,
              position.Y,
              position.Z
          );

          text->SetText(textbuffer);

          RegisterModel(text);
          float dT = _gameTickData.DeltaTime * 1;

          cube->Rotate(0.5 * dT, 0.13 * dT, 0.22 * dT);
          RegisterModel(cube);
      }
  */