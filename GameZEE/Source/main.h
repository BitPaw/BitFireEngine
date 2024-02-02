#include <stdio.h>
#include <stdlib.h>

#include <BFEngine.h>


//BF::UIText* text;
//BF::Model* sphere;
PXTexture2D _blockTexture;

PXSkyBox _skybox;
PXRenderable _cubeModel;

PXShaderProgram _worldShader;
PXShaderProgram _hudShaderID;

//BF::AudioSource _audioSource;
float _deltaTime = 0;
PXModel* model;
PXModel textureBix;
//BF::Level _level;
//BF::AudioClip _audioClip;

#define EnableMusic 1



void OnNetworkUpdate(const BFEngine* bitFireEngine);
void OnStartUpEvent(BFEngine* const bitFireEngine);
void OnShutDownEvent(const BFEngine* bitFireEngine);
void OnGameUpdateEvent(const BFEngine* bitFireEngine, const float deltaTime);
void OnRenderUpdateEvent(BFEngine* const bitFireEngine, BFInputContainer* input);