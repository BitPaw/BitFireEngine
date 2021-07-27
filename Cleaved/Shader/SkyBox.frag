#version 330

precision mediump float;

layout(location = 0) out vec4 fragcolor;

in vec3 TexturePosition;

uniform samplerCube Skybox;

void main()
{
   fragcolor = texture(Skybox, TexturePosition);
}