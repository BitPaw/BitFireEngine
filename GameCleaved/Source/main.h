//#include <stdio.h>
//#include <stdlib.h>

// Engine
#include <BFEngine.h>
#include <Entity/BFSign.h>

// PXUltima
#include <OS/Time/PXStopWatch.h>

PXRenderable _rectangleMesh;

PXFont _font;

PXTexture2D testTextue;

PXSkyBox _skybox;
PXShaderProgram _worldShader;
PXShaderProgram _hudShaderID;

//PXGravityCube _gravityField;

// Sprites - Imgame
PXSprite _backGround;

// Sprites - menu
PXSprite _dialogBox;
PXSprite _dialogBoxCharacterImage;


PXSprite _playerCharacterLuna;
PXSprite _playerCharacterNyte;
PXSprite _lamp;
PXSprite _fireplace;
PXSprite _sign;
PXSprite _floor;

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