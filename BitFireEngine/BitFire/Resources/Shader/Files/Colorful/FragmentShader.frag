#version 330 core

layout(location = 0) out vec4 color;

in vec4 vertexColor;

//uniform vec4 u_Color;

void main()
{
  //color = vec4(0.2f, 0.3f, 0.8f, 1.0f);

  //color = u_Color;

  color = vertexColor;
};