#include "main.h"

#include <Device/InputButton.h>

#if !defined(_DEBUG) && defined(OSWindows5)
#include <windows.h>
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, char*, int nShowCmd)
#else
int main(int amountOFParameters, char** parameter)
#endif  
{
    BitFireEngine bitFireEngine;

    bitFireEngine.UpdateUICallBack = OnUpdateUI;
    bitFireEngine.StartUpCallBack = OnStartUp; // StartDoc
    bitFireEngine.ShutDownCallBack = OnShutDown;
    bitFireEngine.UpdateGameLogicCallBack = OnUpdateGameLogic;
    bitFireEngine.UpdateInputCallBack = OnUpdateInput;

    bitFireEngine.Start();

    while (bitFireEngine.IsRunning)
    {
        bitFireEngine.Update();
    }

    bitFireEngine.Stop();

    return EXIT_SUCCESS;
}

PXModel _cubeThing;

void OnStartUp(BitFireEngine* const bitFireEngine)
{    

    _worldShader.ID = -1;
    _hudShaderID.ID = -1;

    bitFireEngine->Load(_worldShader, "Shader/WS.vert", "Shader/WS.frag");
    bitFireEngine->Load(_hudShaderID, "Shader/HUD.vert", "Shader/HUD.frag");

    bitFireEngine->Load
    (
        skybox,
        "Shader/SkyBox.vert",
        "Shader/SkyBox.frag",
        "Texture/SkyBox/Right.png",
        "Texture/SkyBox/Left.png",
        "Texture/SkyBox/Top.png",
        "Texture/SkyBox/Bottom.png",
        "Texture/SkyBox/Back.png",
        "Texture/SkyBox/Front.png"
    );

    //GameSystem.Load(textureBix, "Model/Dialog/DialogBox.obj");

    bitFireEngine->Load(_blockTexture, L"Texture/Block.bmp", false);
    //bitFireEngine->Load("Model/Triangle.obj");

   // _worldGravity.IgnoreAxis.Set(true, true, true);
   // _worldGravity.PullForce = GravityForceEarth;
   // _worldGravity.PullDirection.Set(0, -1, 0);
   // GameSystem.Resource.Add(&_worldGravity);

    //bitFireEngine->Load(_level, L"Level/MainMenu.lev");

    //bitFireEngine->Load();

    //GameSystem.Resource.Load(L"B:/Daten/Textures/PR/Countrry/Neo/FI/Country.obj");





    // bitFireEngine->Load(_cubeModel, &_cubeThing, L"Model/Cube.obj", false);
   // bitFireEngine->Load(_cubeModel, &_cubeThing, L"Model/Triangle.obj", false);
    //bitFireEngine->Load(_cubeModel, &_cubeThing, L"B:/Daten/Objects/Moze/Moze.obj", false);
    //bitFireEngine->Load(_cubeModel, &_cubeThing, L"B:/Daten/Objects/arwing/arwing_SNES.obj", false);
    bitFireEngine->Load(_cubeModel, /*&_cubeThing,*/ "Model/Dust_II/DustII.obj", false);

    // _cubeModel.Move(0,50,0);
    // _cubeModel.Scale(100.0f);
    //_cubeModel.ShaderUse(_worldShader.ID);
    //_cubeModel.TextureUse(_blockTexture.ID);
    //_cubeModel.Scale(100);
   // _cubeModel.Move(250, 0, 0);

    //cube.EnablePhysics = true;
//cube.Mass = 1000;

// cube.MaterialListSize++;
// cube.MaterialList = new Material();

 //GameSystem.Resource.Add(cube.MaterialList[0].Texture, "C:/Users/BitPaw/Videos/TEST_PNG3.png", false);
 //cube.MeshList[0].RenderInfo.MaterialID = 0;




// textureBix.MatrixModel.Scale(10, 2, 1);






 //text = new BF::UIText("SampleText", *GameSystem.Resource.DefaultFont, -1, -0.8);
 //text->MeshList[0].RenderInformation.ShaderProgramID = hudShaderID.ID;
 //text->SetFont(*Resource.DefaultFont);
 //text->SetText(text->TextContent);
 //GameSystem.Resource.Add(*text);




 //-----<UI>----------------------------------------------------------------
#if 1




#endif
    //-------------------------------------------------------------------------




#if EnableMusic // Sound Enable
//BF::MID midi;
//midi.Load("Sound/CaveStory.mid");
//midi.Save("Sound/CaveStory_NEW.mid");

//sound.Load("Sound/Our.mp3");
//sound.Load("Sound/CaveStory.mid");

    //>>bitFireEngine->Register(_audioSource);
    //>>bitFireEngine->Load(_audioClip, L"Sound/CatFeet.wav", false);
    //>>bitFireEngine->Use(_audioSource, _audioClip);

    // GameSystem.LoopPart(audioSource, 100, 100);
    // GameSystem.Play(audioSource, sound);

#endif // Sound Enable
  //  GameSystem.MainCamera.Update(0);
   // GameSystem.MainCamera.Move(0, 0, -100);

    bitFireEngine->PrintContent(true);
}

void OnShutDown(const BitFireEngine* bitFireEngine)
{

}

//BF::Vector3<float> rot(0.0349066, 0, 0);

void OnUpdateGameLogic(const BitFireEngine* bitFireEngine, const float deltaTime)
{
    /*
    if (cube.MatrixModel.CurrentPosition().Y <= 0)
    {
       // cube.MatrixModel.Move(0, 200, 0);
        cube.Force.Add(0, 50, 0);
    }*/

    _deltaTime = deltaTime;
}

void OnUpdateInput(BitFireEngine* const bitFireEngine, BF::InputContainer& input)
{
#if EnableMusic
    bool changed = false;
    float value = 0.01f;

    if(InputButtonIsPressed(input.KeyBoardInput.O))
    {
        //>> _audioSource.PitchIncrease(value);

        changed = true;
    }

    if(InputButtonIsPressed(input.KeyBoardInput.L))
    {
        //>> _audioSource.PitchReduce(value);

        changed = true;
    }

    if(changed)
    {
        //>>   bitFireEngine->Update(_audioSource);
    }
#endif

    KeyBoardCache& keyboard = input.KeyBoardInput;
    MouseCache& mouse = input.MouseInput;
    PXCamera& camera = bitFireEngine->MainCamera;
    PXVector3F movement = {0,0,0};

    if(InputButtonIsPressed(keyboard.ShitftLeft)) { PXVector3FAddXYZ(&movement, 0, -1, 0, &movement); }
    if(InputButtonIsPressed(keyboard.W)) { PXVector3FAddXYZ(&movement,0, 0, 1, &movement); }
    if(InputButtonIsPressed(keyboard.A)) { PXVector3FAddXYZ(&movement,-1, 0, 0, &movement); }
    if(InputButtonIsPressed(keyboard.S)) { PXVector3FAddXYZ(&movement,0, 0, -1, &movement); }
    if(InputButtonIsPressed(keyboard.D)) { PXVector3FAddXYZ(&movement,1, 0, 0, &movement); }
    if(InputButtonIsPressed(keyboard.SpaceBar))
    {
        //camera.Velocity.Set(0.0f, 6.0f, .0f);

        PXVector3FAddXYZ(&movement, 0, 1, 0, &movement);
    }

    PXCameraMove(&camera, &movement);
    PXCameraRotateXYZ(&camera, mouse.InputAxis[0], mouse.InputAxis[1], 0);
}

void OnUpdateUI(const BitFireEngine* bitFireEngine)
{
    //sprintf_s(text->TextContent, "FPS: %4i", (BF::MathCeiling(1 / _deltaTime)));
    //text->SetText(text->TextContent);

    if(model == nullptr)
    {
        // model = GameSystem.Resource.GetModel(0);
    }
    else
    {
        // model->ModelMatrix.Rotate(rot);
    }
}