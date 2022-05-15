#version 300 es

precision highp float;
precision mediump int;

out vec4 fragcolor;

in vec3 TexturePosition;

uniform samplerCube SkyBoxTexture;

void main()
{
	vec4 textureColor = texture(SkyBoxTexture, TexturePosition);

	fragcolor = textureColor;
}
