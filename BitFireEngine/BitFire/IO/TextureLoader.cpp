#include "TextureLoader.h"


Texture* TextureLoader::LoadTexture(std::string filePath)
{
   // const unsigned int amount = 1;
   // unsigned int textureID;
    Texture* texture = nullptr;
        
    /*
    glGenTextures(amount, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, texture->Height, texture->Height, GL_RGBA, GL_UNSIGNED_BYTE, textureBuffer);
    glBindTexture(GL_TEXTURE_2D, 0);
    */

    char* data;

    std::ifstream ifs(filePath, std::ios::binary | std::ios::ate);
    std::ifstream::pos_type size = ifs.tellg();

    data = new char[size];

    ifs.seekg(0, std::ios::beg);
    ifs.read(data, size);

    printf("Byte read <%i>\n", size);

    texture = new Texture();
    texture->Data = reinterpret_cast<unsigned char*>(data);

    return texture;
}
