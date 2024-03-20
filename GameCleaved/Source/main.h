//#include <stdio.h>
//#include <stdlib.h>

// Engine
#include <BFEngine.h>

// PXUltima
#include <OS/Time/PXStopWatch.h>
#include <Engine/Dialog/PXDialogBox.h>

PXRenderable _rectangleMesh;

PXFont* _font;


PXSkyBox* _skybox;
PXShaderProgram* _worldShader = 0;

//PXGravityCube _gravityField;

// Sprites - Imgame
PXSprite* _backGround = 0;

PXSprite* _playerCharacterLuna = 0;
PXSprite* _playerCharacterNyte = 0;
PXSprite* _lamp = 0;
PXSprite* _fireplace = 0;
PXSprite* _sign = 0;
PXSprite* _floor = 0;

PXEngineSound* _dialogLetterPopSFX;

PXEngineDialogBox pxDialogBox;


// UI
PXSprite* _menuFrame = 0;
PXSprite* _menuButtonA = 0;
//BFUIText _buttonTextA;
PXSprite* _menuButtonB = 0;
PXSprite* _menuButtonC = 0;

void PXAPI OnNetworkUpdate(const BFEngine* bitFireEngine);
void PXAPI OnStartUpEvent(BFEngine* const bitFireEngine);
void PXAPI OnShutDownEvent(const BFEngine* bitFireEngine);
void PXAPI OnGameUpdateEvent(const BFEngine* bitFireEngine, const float deltaTime);
//void PXAPI OnRenderUpdateEvent(BFEngine* const bitFireEngine, BFInputContainer* input);