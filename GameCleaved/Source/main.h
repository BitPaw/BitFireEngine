//#include <stdio.h>
//#include <stdlib.h>

// Engine
#include <Engine/PXEngine.h>

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

PXPrivate void PXAPI OnStartUpEvent(void* const owner, PXEngine* const pxEngine);
PXPrivate void PXAPI OnShutDownEvent(void* const owner, PXEngine* const pxEngine);
PXPrivate void PXAPI OnGameUpdateEvent(void* const owner, PXEngine* const pxEngine);
PXPrivate void PXAPI OnRenderUpdateEvent(void* const owner, PXEngine* const pxEngine);