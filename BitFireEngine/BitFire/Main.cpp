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
#include "Graphics/Camera.h"

#include <GLM/glm.hpp>

#include <chrono>
#include <thread>

int main()
{
    Window* window = new Window();
    window->Create(500, 500, "SteelStorm");  

    if (false)
    {
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
    }

    if (true)
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }


    Camera* camera = new Camera();
    RenderObject* renderObject;   

    // Object Creation
    {

        //renderObject = WaveFont::LoadFromFile("B:/Daten/Objects/cabinet/FilingCabinetOBJ.obj"); // ???
        //renderObject = WaveFont::LoadFromFile("B:/Daten/Objects/arwing/arwing_SNES.obj");  // ERRROR

        const float lowcolor = 0.2f;
        const float hicolor = 0.8f;

        if (false)
        {
            renderObject = WaveFont::LoadFromFile("C:/_WorkSpace/C++/sphere.obj");

            for (size_t i = 0; i < renderObject->_mesh->AmountOfVertexes; i++)
            {
                Vertex* vertex = &renderObject->_mesh->VertexList[i];

                vertex->Color = new Position(vertex->TexturePoint->X, vertex->TexturePoint->Y, 0);
            }
        }

        if (false)
        {
            renderObject = WaveFont::LoadFromFile("C:/_WorkSpace/C++/A.obj");

            renderObject->_mesh->VertexList[0].Color = new Position(hicolor, lowcolor, lowcolor);
            renderObject->_mesh->VertexList[1].Color = new Position(lowcolor, hicolor, lowcolor);
            renderObject->_mesh->VertexList[2].Color = new Position(lowcolor, lowcolor, hicolor);
            renderObject->_mesh->VertexList[3].Color = new Position(hicolor, hicolor, lowcolor);
            renderObject->_mesh->VertexList[4].Color = new Position(lowcolor, hicolor, hicolor);
        }

        if (false)
        {
            renderObject = new Rectangle();

            renderObject->_mesh->VertexList[0].Color = new Position(hicolor, lowcolor, lowcolor);
            renderObject->_mesh->VertexList[1].Color = new Position(lowcolor, hicolor, lowcolor);
            renderObject->_mesh->VertexList[2].Color = new Position(lowcolor, lowcolor, hicolor);
            renderObject->_mesh->VertexList[3].Color = new Position(hicolor, hicolor, lowcolor);
        }


        if (true)
        {
            renderObject = new Triangle();

            renderObject->_mesh->VertexList[0].Color = new Position(hicolor, lowcolor, lowcolor);
            renderObject->_mesh->VertexList[1].Color = new Position(lowcolor, hicolor, lowcolor);
            renderObject->_mesh->VertexList[2].Color = new Position(lowcolor, lowcolor, hicolor);
        }

    }

    float* positions = renderObject->_mesh->GetVertexData();
    unsigned int* ind = renderObject->_mesh->GetIndices();
    const unsigned int vertexSize = renderObject->_mesh->AmountOfVertexes;
    const unsigned int indicesSize = renderObject->_mesh->IndiceListSize;


   
    VertexBuffer vertexBuffer(renderObject->_mesh);
   
    unsigned int shader;
    int location;
    RGBA color(.2f, .3f, .9f, 1);    
    
    // Shader
    {
        // Hardcoded! This will not work outside the IDE. Path relative to .exe.
        ShaderFile* shaderFile = new ShaderFile("BitFire/Shader/VertexShader.vts", "BitFire/Shader/FragmentShader.fms");
        shaderFile->LoadShaderFiles();
        
        shaderFile->VertexShader = FileLoader::ReadCompleteFile(std::string(shaderFile->VertexShaderPath));
        shaderFile->FragmentShader = FileLoader::ReadCompleteFile(std::string(shaderFile->FragmentShaderPath));

        shader = ShaderLoader::CreateShader(shaderFile->VertexShader, shaderFile->FragmentShader);
        glUseProgram(shader);    

        location = glGetUniformLocation(shader, "u_Color");
      
        if (location == -1)
        {
            // error
        }

        glUniform4f(location, .2f, .3f, .9f, 1);
    }


    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 completematrix;
    int modelViewMapos = glGetUniformLocation(shader, "ModelViewProjection");

    while (!window->Exit)
    {      
       // glUniform4f(location, color.Red, color.Green, color.Blue, color.Alpha);

        glClear(GL_COLOR_BUFFER_BIT);

        //float x = (rand() % 200) / 200.0f;
        //float y = (rand() % 200) / 200.0f;
        //float z = (rand() % 200) / 200.0f;

        // Input
        {
            const float movementspeed = 0.01f;

            if (window->KeyBoardInput->W == true)
            {
                camera->Move(glm::vec3(0, movementspeed, 0));  
            }

            if (window->KeyBoardInput->A == true)
            {             
                camera->Move(glm::vec3(-movementspeed, 0, 0));         
            }

            if (window->KeyBoardInput->S == true)
            {
                camera->Move(glm::vec3(0, -movementspeed, 0));          
            }

            if (window->KeyBoardInput->D == true)
            {
                camera->Move(glm::vec3(movementspeed, 0, 0));                  
            }

            if (window->KeyBoardInput->F == true)
            {
                camera->Settings->Mode = camera->Settings->Mode == Perspectdive ? Orthographic : Perspectdive;

              //  std::this_thread::sleep_for(std::chrono::milliseconds(1000));

                
            }

            if (window->KeyBoardInput->E == true)
            {
                camera->Move(glm::vec3(0, 0, -movementspeed));
            }
            if (window->KeyBoardInput->R == true)
            {
                camera->Move(glm::vec3(0, 0, movementspeed));
            }

            if (window->KeyBoardInput->G == true)
            {
                model = glm::rotate(model, 0.02f, glm::vec3(0, 1, 0));
            }

            model = glm::rotate(model, 0.02f, glm::vec3(0, 1, 0));
        }
        
        if (true)
        {
            glm::vec3 trans = glm::vec3((camera->GetUpdatedViewProjection())[3]);
            printf("Camera [%f | %f | %f] %s\n", trans.x, trans.y, trans.z, (camera->Settings->Mode == Perspectdive ? "Perspectdive" : "Orthographic"));
        }


        completematrix = camera->_projection * camera->_view * model;

        /*
        glm::mat4 w = glm::perspective(60.f, 1.0f, 0.01f, 14000.0f);
        w = glm::translate(w, glm::vec3(0,0,-1));

        completematrix = model * w;
        */

        //glUniform4f(location, color.Red, color.Green, color.Blue, color.Alpha);

        glUniformMatrix4fv(modelViewMapos, 1, GL_FALSE, &completematrix[0][0]);

        vertexBuffer.BindBuffer();
        //glDrawArrays(GL_TRIANGLES, 0, NrVertices);
        glDrawElements(GL_TRIANGLES, indicesSize, GL_UNSIGNED_INT, nullptr);
        vertexBuffer.UnBindBuffer();

        window->Update();
    }

    glDeleteProgram(shader);
   
    return 0;
}