#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include "Window/Window.h"
#include "Shader/ShaderLoader.h"
#include "IO/FileLoader.h"
#include "Mathmatic/Geometry/Shapes/Triangle.h"
#include "Mathmatic/Geometry/Shapes/Rectangle.h"
#include "Color/RGBA.h"
#include "IO/DataType/WaveFont.h"
#include "Window/VertexBuffer.h"
#include "Shader/ShaderFile.h"
#include "Graphics/Camera/Camera.h"
#include "Graphics/Camera/FirstPersonCamera.h"

#include <GLM/glm.hpp>

#include <chrono>
#include <thread>
#include "IO/TextureLoader.h"
#include "IO/DataType/Font/BitMapFontCharacter.h"
#include "IO/DataType/Font/BitMapFontLoader.h"


int main()
{
    
    //  _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    Window* window = new Window(800, 800, "SteelStorm");
    Camera* camera = new FirstPersonCamera();
    camera->Settings->Mode = CameraMode::Perspectdive;

  
    unsigned int shader;
    int location;
    int modelViewMapos;
    RGBA color(.2f, .3f, .9f, 1);
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 completematrix;

    // Shader
    try
    {
        ShaderFile* shaderFile = new ShaderFile("BitFire/Shader/VertexShader.vts", "BitFire/Shader/FragmentShader.fms");
        shaderFile->LoadShaderFiles();

        shaderFile->VertexShader = FileLoader::ReadCompleteFile(shaderFile->VertexShaderPath);
        shaderFile->FragmentShader = FileLoader::ReadCompleteFile(shaderFile->FragmentShaderPath);

       // shaderFile->VertexShader = "#version 330 core\n       layout(location = 0) in vec4 position; \n        layout(location = 1) in vec4 color; \n       out vec4 vertexColor;\n       uniform mat4 ModelViewProjection;\n     void main()\n        { \n            gl_Position = ModelViewProjection * position; \n            vertexColor = color; \n        }; ";
       // shaderFile->FragmentShader = "#version 330 core\n\nlayout(location = 0) out vec4 color;\n\nin vec4 vertexColor;\n\nuniform vec4 u_Color;\n\nvoid main()\n{\n  color = vertexColor;\n};";

        shader = ShaderLoader::CreateShader(shaderFile->VertexShader, shaderFile->FragmentShader);

        if (shader == -1)
        {
            printf("[!] Shader failed to load!\n");

            return -2; // <-- this will trigger, Shader is faulty.
        }

        glUseProgram(shader);

        location = glGetUniformLocation(shader, "u_Color");

        if (location == -1)
        {
            printf("[!] Uniform Location <u_Color> is missing!\n");
        }
        else
        {
            glUniform4f(location, .2f, .3f, .9f, 1);
        }

        modelViewMapos = glGetUniformLocation(shader, "ModelViewProjection");

        if (location == -1)
        {
            printf("[!] Uniform Location <ModelViewProjection> is missing!\n");
        }
        else
        {
            // ???
        }
    }
    catch (const std::exception& e)
    {
        printf("Shader loading failed : %s\n", e.what());
    }


    RenderObject* robjetcs = new RenderObject[1];
    /*
    RenderObject* aw;
    RenderObject* panzer;
    RenderObject* sphere;
    RenderObject* cube;
    RenderObject* quad;
    RenderObject* triangle;*/

    // Object Creation
    //{

        //renderObject = WaveFont::LoadFromFile("B:/Daten/Objects/cabinet/FilingCabinetOBJ.obj"); // ???
        //renderObject = WaveFont::LoadFromFile("B:/Daten/Objects/arwing/arwing_SNES.obj");  // ERRROR

        const float lowcolor = 0.2f;
        const float hicolor = 0.8f;

        // Hardcoded! This will fail if this object is not there!
        robjetcs[0] = *WaveFont::LoadFromFile("Cube.obj"); // <-- Simple Cube
       // panzer = WaveFont::LoadFromFile("C:/_WorkSpace/C++/Q.obj");
      
      //  panzer = WaveFont::LoadFromFile("C:/_WorkSpace/C++/Data/S.obj");
       // aw = WaveFont::LoadFromFile("C:/_WorkSpace/C++/Data/TigefffR.obj");
        /*

        if (false)
        {
            sphere = WaveFont::LoadFromFile("C:/_WorkSpace/C++/sphere.obj");

           

            for (size_t i = 0; i < sphere->_mesh->AmountOfVertexes; i++)
            {
                Vertex* vertex = &sphere->_mesh->VertexList[i];

                vertex->Color = new Position(vertex->TexturePoint->X, vertex->TexturePoint->Y, 0);
            }
        }

        if (false)
        {
            cube = WaveFont::LoadFromFile("C:/_WorkSpace/C++/Q.obj");
            
            cube->_mesh->VertexList[0].Color = new Position(hicolor, lowcolor, lowcolor);
            cube->_mesh->VertexList[1].Color = new Position(lowcolor, hicolor, lowcolor);
            cube->_mesh->VertexList[2].Color = new Position(lowcolor, lowcolor, hicolor);
            cube->_mesh->VertexList[3].Color = new Position(hicolor, hicolor, lowcolor);
            cube->_mesh->VertexList[4].Color = new Position(lowcolor, hicolor, hicolor);
        }

        if (false)
        {
            quad = new Rectangle();

            quad->_mesh->VertexList[0].Color = new Position(hicolor, lowcolor, lowcolor);
            quad->_mesh->VertexList[1].Color = new Position(lowcolor, hicolor, lowcolor);
            quad->_mesh->VertexList[2].Color = new Position(lowcolor, lowcolor, hicolor);
            quad->_mesh->VertexList[3].Color = new Position(hicolor, hicolor, lowcolor);
        }

        if (false)
        {
            triangle = new Triangle();

            triangle->_mesh->VertexList[0].Color = new Position(hicolor, lowcolor, lowcolor);
            triangle->_mesh->VertexList[1].Color = new Position(lowcolor, hicolor, lowcolor);
            triangle->_mesh->VertexList[2].Color = new Position(lowcolor, lowcolor, hicolor);
        }

    }
    /*
    float* positions = renderObject->_mesh->GetVertexData();
    unsigned int* ind = renderObject->_mesh->GetIndices();
    const unsigned int vertexSize = renderObject->_mesh->AmountOfVertexes;
    const unsigned int indicesSize = renderObject->_mesh->IndiceListSize;

    //robjetcs[0] = *aw;
    //robjetcs[1] = *panzer;
    //robjetcs[2] = *sphere;
    //robjetcs[3] = *cube;
  //  robjetcs[4] = *quad;
//    robjetcs[5] = *triangle;       
   






    BitMapFontCharacter* character = new BitMapFontCharacter();

    character->ID = 32;
    character->StartPosition.X = 0;
    character->StartPosition.Y = 0;
    character->Size.X = 0;
    character->Size.Y = 0;
    character->Offset.X = 0;
    character->Offset.Y = 71;
    character->XAdvance = 27;

    BitMapFont* bitMapFont = BitMapFontLoader::LoadFont("C:/_WorkSpace/C++/arial.fnt");

    std::string message = BitMapFontLoader::PrintCharacterLine(character);
    */

    VertexBuffer* vertexBuffer = new VertexBuffer(robjetcs[0]._mesh);

    try
    {
        while (!window->Exit)
        {
            // glUniform4f(location, color.Red, color.Green, color.Blue, color.Alpha);

            glClear(GL_COLOR_BUFFER_BIT);

            //float x = (rand() % 200) / 200.0f;
            //float y = (rand() % 200) / 200.0f;
            //float z = (rand() % 200) / 200.0f;

            // Input
            {
                if (window->KeyBoardInput->Letter.W)
                {
                    camera->Move(Direcion::Forward);
                }

                if (window->KeyBoardInput->Letter.A)
                {
                    camera->Move(Direcion::Left);
                }

                if (window->KeyBoardInput->Letter.S)
                {
                    camera->Move(Direcion::Backward);
                }

                if (window->KeyBoardInput->Letter.D)
                {
                    camera->Move(Direcion::Right);
                }

                if (window->KeyBoardInput->SpaceBar)
                {
                    camera->Move(Direcion::Up);
                }

                if (window->KeyBoardInput->FunktionKey.ShitftLeft)
                {
                    camera->Move(Direcion::Down);
                }



                //  printf("%.2f | %.2f\n", window->MouseInput->InputAxis.X, window->MouseInput->InputAxis.Y);




                if (window->KeyBoardInput->Letter.F)
                {
                    camera->Settings->Mode = camera->Settings->Mode == CameraMode::Perspectdive ? CameraMode::Orthographic : CameraMode::Perspectdive;

                    //  std::this_thread::sleep_for(std::chrono::milliseconds(1000));                
                }
                FirstPersonCamera* fc = (FirstPersonCamera*)camera;

                fc->Rotate(window->MouseInput->InputAxis.X, window->MouseInput->InputAxis.Y);

                // model = glm::rotate(model, 0.002f, glm::vec3(0, 1, 0));
            }

            if (true)
            {
                glm::vec3 trans = camera->_position;
                //Rotation pos = ((FirstPersonCamera*)camera)->CurrentRotation;
                Point pos = window->MouseInput->InputAxis;
                // printf("Cam [%.2f|%.2f|%.2f] [%.2f|%.2f] %s\n", trans.x, trans.y, trans.z, pos.X, pos.Y, (camera->Settings->Mode == CameraMode::Perspectdive ? "Per" : "Ort"));

               //  Point* point = &window->MouseInput->Position;

                // printf("Pos : %f | %f\n", point->X, point->Y);
            }

            /*

            VertexBuffer vertexBuffer(robjetcs[0]._mesh);
            unsigned int indsize = robjetcs[0]._mesh->IndiceListSize;

            for (size_t z = 0; z < 10; z++)
            {
                for (size_t y = 0; y < 10; y++)
                {
                    for (size_t x = 0; x < 10; x++)
                    {
                      

                        camera->Update();

                        const float blockSize = 2;

                        glm::mat4 diff = glm::translate(camera->_view, glm::vec3(blockSize * x, blockSize * z, blockSize * y));

                        completematrix = camera->_projection * diff * model;

                        glUniformMatrix4fv(modelViewMapos, 1, GL_FALSE, &completematrix[0][0]);

                        vertexBuffer.BindBuffer();
                        //glDrawArrays(GL_TRIANGLES, 0, NrVertices);
                       // glDrawElements(GL_TRIANGLES, indsize, GL_UNSIGNED_INT, nullptr);
                        glDrawElements(GL_LINE_LOOP, indsize, GL_UNSIGNED_INT, nullptr);
                        vertexBuffer.UnBindBuffer();
                    }
                }
            }*/

                for (size_t x = 0; x < 1; x++)
                {

                    //VertexBuffer vertexBuffer(robjetcs[x]._mesh);
                    vertexBuffer->ChangeMesh(robjetcs[x]._mesh);

                    unsigned int indsize = robjetcs[x]._mesh->IndiceListSize;
                    camera->Update();

                    const float blockSize = 5;

                    glm::mat4 diff = glm::translate(camera->_view, glm::vec3(blockSize * x, 0, 0));

                    completematrix = camera->_projection * diff * model;

                    //glUniformMatrix4fv(modelViewMapos, 1, GL_FALSE, &completematrix[0][0]);

                    vertexBuffer->BindBuffer();
                    //glDrawArrays(GL_TRIANGLES, 0, NrVertices);
                    glDrawElements(GL_TRIANGLES, indsize, GL_UNSIGNED_INT, nullptr);
                   // glDrawElements(GL_LINE_LOOP, indsize, GL_UNSIGNED_INT, nullptr);
                    vertexBuffer->UnBindBuffer();
                }
            
 
           
          
     

            window->Update();
        }
    }
    catch (const std::exception& e)
    {
        printf("[!] Error : %s\n", e.what());
    }

    glDeleteProgram(shader);
   
    delete window;

    return 0;
}