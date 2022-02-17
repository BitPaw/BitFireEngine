#version 330

out vec4 fragcolor;

in vec2 TexturePosition;
in vec3 TextureScaling;

uniform sampler2D SpriteTexture;

void main()
{
	float x = (TexturePosition.x);// * TextureScaling.x;
	float y = (1-TexturePosition.y);// * TextureScaling.y;
	vec2 textureIndexPosition = vec2(x,y);
	vec4 textureData = texture(SpriteTexture, textureIndexPosition);// + vec4(vec3(TexturePosition, 0.0f), 1.0f);
	bool isTransparent = textureData.a == 0;
	
	if(isTransparent)
	{
		discard;
	}

	fragcolor = textureData;
}

