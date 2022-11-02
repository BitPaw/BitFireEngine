#include <stdio.h>
#include <stdlib.h>

#include <UI/UIText.h>
#include <Entity/Sign.h>
#include <Physic/GravityCube.h>
#include <System/BitFireEngine.h>

using namespace BF;

BF::UIText* text;
//BF::Model* sphere;
PXTexture _blockTexture;

BF::Level _level;

PXSkyBox skybox;
PXRenderable _cubeModel;

ShaderProgram _worldShader;
ShaderProgram _hudShaderID;

//BF::AudioSource _audioSource;
BF::GravityCube _worldGravity;
float _deltaTime = 0;
Model* model;
Model textureBix;
//BF::Level _level;
//BF::AudioClip _audioClip;

#define EnableMusic 1



void OnUpdateUI(const BitFireEngine* bitFireEngine);
void OnStartUp(BitFireEngine* const bitFireEngine);
void OnShutDown(const BitFireEngine* bitFireEngine);
void OnUpdateGameLogic(const BitFireEngine* bitFireEngine, const float deltaTime);
void OnUpdateInput(BitFireEngine* const bitFireEngine, BF::InputContainer& input);