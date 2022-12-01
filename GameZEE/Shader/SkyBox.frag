#version 300 es

precision highp float;
precision mediump int;

out vec4 fragcolor;

in vec3 TexturePosition;

uniform samplerCube SkyBoxTexture;

void main()
{
	vec3 texturePositonFlipped = vec3(-TexturePosition.x, TexturePosition.y, -TexturePosition.z);
	vec4 textureColor = texture(SkyBoxTexture, texturePositonFlipped);

	fragcolor = textureColor;
}
