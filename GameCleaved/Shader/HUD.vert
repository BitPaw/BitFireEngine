#version 330

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec4 color;
layout(location = 3) in vec2 texturePosition;

out vec3 vertexPosition;
out vec3 vertexNormal;
out vec4 vertexColor;
out vec2 vertexTexturePosition;

uniform mat4 MatrixModel;

void main() 
{
    gl_Position = MatrixModel * vec4(position,1);
	
    vertexColor = color;
    vertexNormal = normal;
    vertexPosition = position;
    vertexTexturePosition = texturePosition;
}