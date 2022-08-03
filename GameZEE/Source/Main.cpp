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

void OnStartUp(BitFireEngine* const bitFireEngine)
{
    _worldShader.ID = -1;
    _hudShaderID.ID = -1;

    bitFireEngine->Load(_worldShader, L"Shader/WS.vert", L"Shader/WS.frag");
    bitFireEngine->Load(_hudShaderID, L"Shader/HUD.vert", L"Shader/HUD.frag");

    bitFireEngine->Load
    (
        skybox,
        L"Shader/SkyBox.vert",
        L"Shader/SkyBox.frag",
        L"Texture/SkyBox/Right.png",
        L"Texture/SkyBox/Left.png",
        L"Texture/SkyBox/Top.png",
        L"Texture/SkyBox/Bottom.png",
        L"Texture/SkyBox/Back.png",
        L"Texture/SkyBox/Front.png"
    );

    //GameSystem.Load(textureBix, "Model/Dialog/DialogBox.obj");

    bitFireEngine->Load(_blockTexture, L"Texture/Block.bmp", false);
    //GameSystem.Resource.Load("Model/Triangle.obj");

   // _worldGravity.IgnoreAxis.Set(true, true, true);
   // _worldGravity.PullForce = GravityForceEarth;
   // _worldGravity.PullDirection.Set(0, -1, 0);
   // GameSystem.Resource.Add(&_worldGravity);

    bitFireEngine->Load(_level, L"Level/MainMenu.lev");

    //GameSystem.Resource.Load(L"B:/Daten/Textures/PR/Countrry/Neo/FI/Country.obj");

    bitFireEngine->Load(_cubeModel, L"Model/Cube.obj", false);
    // _cubeModel.Move(0,50,0);
    // _cubeModel.Scale(100.0f);
    _cubeModel.ShaderUse(_worldShader.ID);
    _cubeModel.TextureUse(_blockTexture.ID);
    _cubeModel.Scale(100);
    _cubeModel.Move(250, 0, 0);

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

    bitFireEngine->Register(_audioSource);
    bitFireEngine->Load(_audioClip, L"Sound/CatFeet.wav", false);
    bitFireEngine->Use(_audioSource, _audioClip);

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

BF::Vector3<float> rot(0.0349066, 0, 0);

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
        _audioSource.PitchIncrease(value);

        changed = true;
    }

    if(InputButtonIsPressed(input.KeyBoardInput.L))
    {
        _audioSource.PitchReduce(value);

        changed = true;
    }

    if(changed)
    {
        bitFireEngine->Update(_audioSource);
    }
#endif

    KeyBoardCache& keyboard = input.KeyBoardInput;
    MouseCache& mouse = input.MouseInput;
    Camera& camera = bitFireEngine->MainCamera;
    Vector3<float> movement;

    if(InputButtonIsPressed(keyboard.ShitftLeft)) { movement.Add(0, -1, 0); }
    if(InputButtonIsPressed(keyboard.W)) { movement.Add(0, 0, 1); }
    if(InputButtonIsPressed(keyboard.A)) { movement.Add(-1, 0, 0); }
    if(InputButtonIsPressed(keyboard.S)) { movement.Add(0, 0, -1); }
    if(InputButtonIsPressed(keyboard.D)) { movement.Add(1, 0, 0); }
    if(InputButtonIsPressed(keyboard.SpaceBar))
    {
        camera.Velocity.Set(0.0f, 6.0f, .0f);

        //movement.Add(0, 1, 0);
    }

    camera.Move(movement);

    camera.Rotate(mouse.InputAxis[0], mouse.InputAxis[1]);

    camera.Update(_deltaTime);
    keyboard.IncrementButtonTick();
    mouse.ResetAxis();

    // auto x = GameSystem.MainCamera.MatrixModel.PositionXYZ();
    // printf("Camera Pos : %5.2f %5.2f %5.2f\n", x.X, x.Y, x.Z);
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