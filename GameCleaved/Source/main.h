//#include <stdio.h>
//#include <stdlib.h>

// Engine
#include <BFEngine.h>
#include <Entity/BFSign.h>

// PXUltima
#include <OS/Time/PXStopWatch.h>

float _deltaTime = 0;
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
BFSign _sign;
PXSprite _floor;

//BFUIDialogBox _dialogBox;

PXShaderProgram _simplex;

// UI
PXSprite _menuFrame;
PXSprite _menuButtonA;
//BFUIText _buttonTextA;
PXSprite _menuButtonB;
PXSprite _menuButtonC;

void OnUpdateUI(const BFEngine* bitFireEngine);
void OnStartUp(BFEngine* const bitFireEngine);
void OnShutDown(const BFEngine* bitFireEngine);
void OnUpdateGameLogic(const BFEngine* bitFireEngine, const float deltaTime);
void OnUpdateInput(BFEngine* const bitFireEngine, BFInputContainer* input);