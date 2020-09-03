#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include "Window/Window.h"
#include "Shader/ShaderLoader.h"
#include "IO/FileLoader.h"
#include "Mathmatic/Geometry/Triangle.h"
#include "Mathmatic/Geometry/Rectangle.h"
#include "Color/RGBA.h"
#include "IO/WaveFont.h"

int main()
{
    Window* window = new Window();
    window->Create(640, 480, "SteelStorm");  

    RenderObject* renderObject;
    //RenderObject* renderObject = new Rectangle();
    //RenderObject* renderObject = new Triangle();
   
    WaveFont* wf = new WaveFont();
    
    // Hardcoded! This will not work outside the IDE. Path relative to .exe.
    renderObject = wf->LoadFromFile("Sphere.obj"); // <-- Just a Ball, nothing special

    float* positions = renderObject->_mesh->GetVertexData();
    unsigned int* ind = renderObject->_mesh->GetIndices();

    // Greate Buffer      
    {      
        const unsigned int id = 1;
        const unsigned int vertexSize = renderObject->_mesh->AmountOfVertexes;
        const unsigned int indicesSize = renderObject->_mesh->AmountOfIndices;
        const unsigned int dimensionCount = 3;
        const size_t floatSize = sizeof(float);
        const size_t uintSize = sizeof(unsigned int);

        unsigned int vertexBuffer;
        glGenBuffers(id, &vertexBuffer); // Generate
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer); // Select
        glBufferData(GL_ARRAY_BUFFER, vertexSize * 3 * floatSize, positions, GL_STATIC_DRAW);
 
        // Write
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, dimensionCount, GL_FLOAT, GL_FALSE, dimensionCount * floatSize, 0);
 
        unsigned int indizieBuffer;
        glGenBuffers(id, &indizieBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indizieBuffer); // Select
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize * uintSize, ind, GL_STATIC_DRAW);
    }

    unsigned int shader;
    int location;
    RGBA color(.2f, .3f, .9f, 1);    
    
    // Shader
    {
        // Hardcoded! This will not work outside the IDE. Path relative to .exe.
        std::string vertexShader = FileLoader::ReadCompleteFile("BitFire/Shader/VertexShader.vts");
        std::string fragmentShader = FileLoader::ReadCompleteFile("BitFire/Shader/FragmentShader.fms");

        shader = ShaderLoader::CreateShader(vertexShader, fragmentShader);
        glUseProgram(shader);
    

        location = glGetUniformLocation(shader, "u_Color");
      
        if (location == -1)
        {
            // error
        }

        glUniform4f(location, .2f, .3f, .9f, 1);
    }

    
    bool cc = false;
    float val = 0.02;

    while (!window->Exit)
    {      
        // Spaghetti for Ping-Pong color.
        if (cc)
        {
            color.Red += val;

            if (color.Red >= 1)
            {
                cc = false;
            }
        }
        else
        {
            color.Red -= val;

            if (color.Red <= 0)
            {
                cc = true;
            }
        }

        glUniform4f(location, color.Red, color.Green, color.Blue, color.Alpha);

        window->Update();
    }

    glDeleteProgram(shader);
   
    return 0;
}