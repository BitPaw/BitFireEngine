#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 normal;
layout(location = 2) in vec4 color;

out vec4 vertexColor;

uniform mat4 ModelViewProjection;

void main() 
{
  //gl_Position = position;
  gl_Position = ModelViewProjection * position;
  vertexColor = color *normal ;
  //vertexColor = vec4(0.1f,0,0.1f,1);
};