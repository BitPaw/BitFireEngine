#include <stdio.h>
#include <stdlib.h>

#include <Video/Shader.h>
#include <Model/Model.h>
#include <Math/Math.h>
#include <Math/Geometry/Rectangle.hpp>
#include <Math/Geometry/Form/Cube.h>
#include <Time/StopWatch.h>

#include <Graphic/OpenGL/SkyBox.h>
#include <Graphic/OpenGL/Sprite.h>
#include <UI/DialogBox/UIDialogBox.h>
#include <UI/UIText.h>
#include <Entity/Sign.h>
#include <Physic/GravityCube.h>
#include <File/Format/FNT/FNT.h>
#include <System/BitFireEngine.h>

using namespace BF;

float _deltaTime = 0;
BF::Renderable _rectangleMesh;

FNT fnt;
Font _font;

BF::Texture testTextue;

BF::SkyBox skybox;
ShaderProgram worldShader;
ShaderProgram hudShaderID;

BF::GravityCube _gravityField;

BF::Camera* _camera = nullptr;
BF::Sprite _playerCharacterLuna;
BF::Sprite _backGround;
BF::Sprite _playerCharacterNyte;
BF::Sprite _lamp;
BF::Sprite _fireplace;
BF::Sign _sign;
BF::Sprite _floor;

BF::UIDialogBox _dialogBox;

bool moveCamera = false;


BF::Model _cubeModel;
ShaderProgram _simplex;

// UI
BF::Sprite _menuFrame;
BF::Sprite _menuButtonA;
BF::UIText _buttonTextA;
BF::Sprite _menuButtonB;
BF::Sprite _menuButtonC;

void OnUpdateUI(const BitFireEngine* bitFireEngine);
void OnStartUp(BitFireEngine* const bitFireEngine);
void OnShutDown(const BitFireEngine* bitFireEngine);
void OnUpdateGameLogic(const BitFireEngine* bitFireEngine, const float deltaTime);
void OnUpdateInput(BitFireEngine* const bitFireEngine, BF::InputContainer& input);