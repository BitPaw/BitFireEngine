#version 330

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec4 color;
layout(location = 3) in vec2 texturePosition;

out vec3 TexturePosition;

uniform mat4 MatrixModel;
uniform mat4 MatrixView;
uniform mat4 MatrixProjection;

void main() 
{
    TexturePosition = position;

    gl_Position = MatrixProjection * MatrixView * vec4(position, 1.0);
};