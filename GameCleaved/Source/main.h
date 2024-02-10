//#include <stdio.h>
//#include <stdlib.h>

// Engine
#include <BFEngine.h>

// PXUltima
#include <OS/Time/PXStopWatch.h>
#include <Engine/Dialog/PXDialogBox.h>

PXRenderable _rectangleMesh;

PXFont _font;

PXTexture2D testTextue;

PXSkyBox _skybox;
PXShaderProgram _worldShader;
PXShaderProgram _hudShaderID;

//PXGravityCube _gravityField;

// Sprites - Imgame
PXSprite _backGround;




PXSprite _playerCharacterLuna;
PXSprite _playerCharacterNyte;
PXSprite _lamp;
PXSprite _fireplace;
PXSprite _sign;
PXSprite _floor;

PXEngineSound _dialogLetterPopSFX;

PXEngineDialogBox pxDialogBox;


//BFUIDialogBox _dialogBox;

PXShaderProgram _simplex;

// UI
PXSprite _menuFrame;
PXSprite _menuButtonA;
//BFUIText _buttonTextA;
PXSprite _menuButtonB;
PXSprite _menuButtonC;

void OnNetworkUpdate(const BFEngine* bitFireEngine);
void OnStartUpEvent(BFEngine* const bitFireEngine);
void OnShutDownEvent(const BFEngine* bitFireEngine);
void OnGameUpdateEvent(const BFEngine* bitFireEngine, const float deltaTime);
void OnRenderUpdateEvent(BFEngine* const bitFireEngine, BFInputContainer* input);