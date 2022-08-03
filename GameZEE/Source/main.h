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

BF::UIText* text;
//BF::Model* sphere;
BF::Texture _blockTexture;

BF::Level _level;

BF::SkyBox skybox;
BF::Renderable _cubeModel;

ShaderProgram _worldShader;
ShaderProgram _hudShaderID;

BF::AudioSource _audioSource;
BF::GravityCube _worldGravity;
float _deltaTime = 0;
BF::Model* model;
BF::Model textureBix;
//BF::Level _level;
BF::AudioClip _audioClip;

#define EnableMusic 1



void OnUpdateUI(const BitFireEngine* bitFireEngine);
void OnStartUp(BitFireEngine* const bitFireEngine);
void OnShutDown(const BitFireEngine* bitFireEngine);
void OnUpdateGameLogic(const BitFireEngine* bitFireEngine, const float deltaTime);
void OnUpdateInput(BitFireEngine* const bitFireEngine, BF::InputContainer& input);