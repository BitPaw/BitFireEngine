#include "PortableNetworkGraphicFileHeader.h"

const unsigned char PortableNetworkGraphicFileHeader::FileHeaderSize = 8;
const unsigned char PortableNetworkGraphicFileHeader::FileHeader[8]{ 0x89, 0x50 , 0x4E , 0x47 , 0x0D , 0x0A , 0x1A , 0x0A };
