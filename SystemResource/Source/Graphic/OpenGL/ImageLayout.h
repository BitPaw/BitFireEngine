#pragma once

namespace BF
{
	enum class ImageLayout
	{
        Invalid,

        // Returns the value of the texture element that is nearest to the specified texture coordinates.
        Nearest,

        // Returns the weighted average of the four texture elements that are closest to the specified texture coordinates.
        // These can include items wrapped or repeated from other parts of a texture, depending on the values of GL_TEXTURE_WRAP_Sand GL_TEXTURE_WRAP_T, and on the exact mapping.
        Linear,

        //Chooses the mipmap that most closely matches the size of the pixel being texturedand
        //uses the GL_NEAREST criterion(the texture element closest to the specified texture coordinates) to produce a texture value.
        MipMapNearestNearest,

        //Chooses the mipmap that most closely matches the size of the pixel being texturedand
        //uses the GL_LINEAR criterion(a weighted average of the four texture elements that are closest to the specified texture coordinates) to produce a texture value.
        MipMapLinearNearest,

        //Chooses the two mipmaps that most closely match the size of the pixel being texturedand
        //uses the GL_NEAREST criterion(the texture element closest to the specified texture coordinates)
        //to produce a texture value from each mipmap.The final texture value is a weighted average of those two values.
        MipMapNNearestLinear,

        //Chooses the two mipmaps that most closely match the size of the pixel being texturedand
        //uses the GL_LINEAR criterion(a weighted average of the texture elements that are closest to the specified texture coordinates)
        //to produce a texture value from each mipmap.The final texture value is a weighted average of those two values.
        MipMapLinearLinear
	};
}