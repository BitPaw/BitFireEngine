#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include "Window/Window.h"
#include "Shader/ShaderLoader.h"
#include "IO/FileLoader.h"
#include "Mathmatic/Geometry/Triangle.h"
#include "Mathmatic/Geometry/Rectangle.h"

int main()
{
    Window* window = new Window();
    window->Create(640, 480, "SteelStorm");


    RenderObject* renderObject = new Rectangle();
    //RenderObject* renderObject = new Triangle();

    float* positions = renderObject->_mesh->GetVertexData();
    unsigned int* ind = renderObject->_mesh->GetIndices();

    // Greate Buffer      
    {
        const unsigned int id = 1;
        const unsigned int vertexSize = renderObject->_mesh->AmountOfVertexes;
        const unsigned int indicesSize = renderObject->_mesh->AmountOfIndices;
        const unsigned int dimensionCount = 2;
        const size_t floatSize = sizeof(float);
        const size_t uintSize = sizeof(unsigned int);

        unsigned int vertexBuffer;
        glGenBuffers(id, &vertexBuffer); // Generate
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer); // Select
        glBufferData(GL_ARRAY_BUFFER, vertexSize * 2 * floatSize, positions, GL_STATIC_DRAW);

        // Write
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, dimensionCount, GL_FLOAT, GL_FALSE, dimensionCount * floatSize, 0);

        unsigned int indizieBuffer;
        glGenBuffers(id, &indizieBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indizieBuffer); // Select
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize * uintSize, ind, GL_STATIC_DRAW);
    }

    unsigned int shader;

    // Shader
    {
        // Hardcoded! This will not work outside the IDE. Path relative to .exe.
        std::string vertexShader = FileLoader::ReadFile("BitFire/Shader/VertexShader.vts");
        std::string fragmentShader = FileLoader::ReadFile("BitFire/Shader/FragmentShader.fms");

        shader = ShaderLoader::CreateShader(vertexShader, fragmentShader);
        glUseProgram(shader);
    }

    while (!window->Exit)
    {
        window->Update();
    }

    glDeleteProgram(shader);

    return 0;
}