#version 330

out vec4 fragcolor;

in vec3 TexturePosition;

uniform samplerCube Skybox;

void main()
{
   fragcolor = texture(Skybox, TexturePosition);
}