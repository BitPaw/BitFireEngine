#version 300 es

precision highp float;
precision mediump int;

out mediump vec4 fragcolor;

in mediump vec2 TexturePosition;
in mediump vec3 TextureScaling;

uniform sampler2D SpriteTexture;

void main()
{
	float x = (TexturePosition.x);// * TextureScaling.x;
	float y = (1.0f-TexturePosition.y);// * TextureScaling.y;
	vec2 textureIndexPosition = vec2(x,y);
	vec4 textureData = texture(SpriteTexture, textureIndexPosition);// + vec4(vec3(TexturePosition, 0.0f), 1.0f);
	bool isTransparent = textureData.a == 0.0f;
	
	if(isTransparent)
	{
		discard;
	}

	fragcolor = textureData;
}

