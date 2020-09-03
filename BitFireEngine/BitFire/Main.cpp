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

int main()
{
    Window* window = new Window();
    window->Create(500, 500, "SteelStorm");  


    Camera* camera = new Camera();
    RenderObject* renderObject;   

    //renderObject = wf->LoadFromFile("B:/Daten/Objects/cabinet/FilingCabinetOBJ.obj");
    //renderObject = wf->LoadFromFile("B:/Daten/Objects/arwing/arwing_SNES.obj");
    //renderObject = WaveFont::LoadFromFile("C:/_WorkSpace/C++/sphere.obj");
    //renderObject = wf->LoadFromFile("C:/_WorkSpace/C++/A.obj");
    //renderObject = new Rectangle();
   

   if (true)
   {
       renderObject = new Triangle();

       renderObject->_mesh->VertexList[0].Color = new Point(1, 0);
       renderObject->_mesh->VertexList[1].Color = new Point(1, 1);
       renderObject->_mesh->VertexList[2].Color = new Point(0, 1);
    }


    float* positions = renderObject->_mesh->GetVertexData();
    unsigned int* ind = renderObject->_mesh->GetIndices();
    const unsigned int vertexSize = renderObject->_mesh->AmountOfVertexes;
    const unsigned int indicesSize = renderObject->_mesh->IndiceListSize;

     glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);    
   
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
    //model = glm::scale(model, glm::vec3(1.2f));    
    glm::mat4 completematrix;

   // camera->Move(glm::vec3(0,0,-5));
   // model = glm::translate(model, glm::vec3(0,0,-1.1f));

    int modelViewMapos = glGetUniformLocation(shader, "ModelViewProjection");

    //camera->Move(glm::vec3(0,0,-5));
    //model = glm::translate(model, glm::vec3(0,0,-8));

    while (!window->Exit)
    {      
        glUniform4f(location, color.Red, color.Green, color.Blue, color.Alpha);

        glClear(GL_COLOR_BUFFER_BIT);

        //float x = (rand() % 200) / 200.0f;
        //float y = (rand() % 200) / 200.0f;
        //float z = (rand() % 200) / 200.0f;

       model = glm::rotate(model, 0.02f,glm::vec3(.2f,0.8,0.5f));

       completematrix = model; //* camera->GetUpdatedViewProjection();

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