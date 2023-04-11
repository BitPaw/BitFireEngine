#include <stdio.h>
#include <stdlib.h>

#include <UI/UIText.h>
#include <System/BFEngine.h>


//BF::UIText* text;
//BF::Model* sphere;
PXTexture _blockTexture;

PXSkyBox skybox;
PXRenderable _cubeModel;

ShaderProgram _worldShader;
ShaderProgram _hudShaderID;

//BF::AudioSource _audioSource;
float _deltaTime = 0;
PXModel* model;
PXModel textureBix;
//BF::Level _level;
//BF::AudioClip _audioClip;

#define EnableMusic 1



void OnUpdateUI(const BFEngine* bitFireEngine);
void OnStartUp(BFEngine* const bitFireEngine);
void OnShutDown(const BFEngine* bitFireEngine);
void OnUpdateGameLogic(const BFEngine* bitFireEngine, const float deltaTime);
void OnUpdateInput(BFEngine* const bitFireEngine, BFInputContainer* input);