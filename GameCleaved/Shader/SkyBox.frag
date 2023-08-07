#version 300 es

precision highp float;
precision mediump int;

out vec4 fragcolor;

in vec3 TexturePosition;

uniform samplerCube SkyBoxTexture;

void main()
{
	vec4 textureColor = texture(SkyBoxTexture, TexturePosition);

	textureColor = textureColor * vec4((TexturePosition.x + 1.0f) / 2.0f, (TexturePosition.y + 1.0f) / 2.0f, 1.0f - (TexturePosition.y * TexturePosition.x ) / 2.0f ,1.0f);

	//vec4 textureColor = vec4(1.0f,0.5f,0.0f, 1.0f);

	fragcolor = textureColor;
}
