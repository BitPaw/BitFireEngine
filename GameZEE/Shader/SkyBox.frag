#version 330

out vec4 fragcolor;

in vec3 TexturePosition;

uniform samplerCube Skybox;

void main()
{
	vec3 texturePositionCurrected = vec3(-TexturePosition.x, TexturePosition.y, -TexturePosition.z);

	fragcolor = texture(Skybox, texturePositionCurrected);
}