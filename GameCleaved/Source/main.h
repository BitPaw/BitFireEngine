#include <stdio.h>
#include <stdlib.h>

// Engine
#include <BFEngine.h>
#include <Entity/BFSprite.h>
#include <Entity/BFSign.h>

// PXUltima
#include <Graphic/PXGraphic.h>
#include <OS/Time/PXStopWatch.h>
#include <UI/UIText.h>

float _deltaTime = 0;
PXRenderable _rectangleMesh;

PXFont _font;

PXTexture testTextue;

PXSkyBox _skybox;
PXShaderProgram _worldShader;
PXShaderProgram _hudShaderID;

//PXGravityCube _gravityField;

BFSprite _playerCharacterLuna;
BFSprite _backGround;
BFSprite _playerCharacterNyte;
BFSprite _lamp;
BFSprite _fireplace;
BFSign _sign;
BFSprite _floor;

//BFUIDialogBox _dialogBox;


PXModel _cubeModel;
PXShaderProgram _simplex;

// UI
BFSprite _menuFrame;
BFSprite _menuButtonA;
//BFUIText _buttonTextA;
BFSprite _menuButtonB;
BFSprite _menuButtonC;

void OnUpdateUI(const BFEngine* bitFireEngine);
void OnStartUp(BFEngine* const bitFireEngine);
void OnShutDown(const BFEngine* bitFireEngine);
void OnUpdateGameLogic(const BFEngine* bitFireEngine, const float deltaTime);
void OnUpdateInput(BFEngine* const bitFireEngine, BFInputContainer* input);