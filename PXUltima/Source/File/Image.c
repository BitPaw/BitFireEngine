#include "Image.h"

#include <Memory/Memory.h>
#include <File/File.h>
#include <Text/Text.h>

#include <File/Format/BMP/BMP.h>
#include <File/Format/GIF/GIF.h>
#include <File/Format/JPEG/JPEG.h>
#include <File/Format/PNG/PNG.h>
#include <File/Format/TGA/TGA.h>
#include <File/Format/TIFF/TIFF.h>

#include <File/Font.h>
#include <Math/Math.h>

#include <File/Format/FNT/FNT.h>

size_t ImageBytePerPixel(const ImageDataFormat imageDataFormat)
{
    switch(imageDataFormat)
    {
        default:
        case ImageDataFormatInvalid:
            return 0;

        case ImageDataFormatAlphaMask:
        case ImageDataFormatAlphaMaskBinary:
            return 1;

        case ImageDataFormatBGR:
        case ImageDataFormatRGB:
            return 3;

        case ImageDataFormatRGBA:
        case ImageDataFormatBGRA:
            return 4;
    }
}

size_t ImageBitsPerPixel(const ImageDataFormat imageDataFormat)
{
    return ImageBytePerPixel(imageDataFormat) * 8u;
}

void ImageConstruct(Image* const image)
{
    MemorySet(image, sizeof(Image), 0);
}

void ImageDestruct(Image* const image)
{
    MemoryRelease(image->PixelData, image->PixelDataSize);

    ImageConstruct(image);
}

ImageFileFormat ImageGuessFormat(const wchar_t* const filePath)
{
    wchar_t extension[ExtensionMaxSize];

    FilePathExtensionGetW(filePath, PathMaxSize, extension, ExtensionMaxSize);

    if(TextCompareIgnoreCaseWA(extension, ExtensionMaxSize, "BMP", 3u))  return ImageFileFormatBitMap;
    if(TextCompareIgnoreCaseWA(extension, ExtensionMaxSize, "GIF", 3u))  return ImageFileFormatGIF;
    if(TextCompareIgnoreCaseWA(extension, ExtensionMaxSize, "JPG", 4u))  return ImageFileFormatJPEG;
    if(TextCompareIgnoreCaseWA(extension, ExtensionMaxSize, "JPEG", 4u))  return ImageFileFormatJPEG;
    if(TextCompareIgnoreCaseWA(extension, ExtensionMaxSize, "PNG", 3u))  return ImageFileFormatPNG;
    if(TextCompareIgnoreCaseWA(extension, ExtensionMaxSize, "TGA", 3u))  return ImageFileFormatTGA;
    if(TextCompareIgnoreCaseWA(extension, ExtensionMaxSize, "TIFF", 4u))  return ImageFileFormatTIFF;

    return ImageFileFormatUnkown;
}

ActionResult ImageLoadA(Image* image, const char* filePath)
{
    wchar_t filePathW[PathMaxSize];

    TextCopyAW(filePath, PathMaxSize, filePathW, PathMaxSize);

    ActionResult actionResult = ImageLoadW(image, filePathW);

    return actionResult;  
}

ActionResult ImageLoadW(Image* const image, const wchar_t* const filePath)
{
    File file;

    FileConstruct(&file);
    ImageConstruct(image);

    {
        const ActionResult fileLoadingResult = FileMapToVirtualMemoryW(&file, filePath, 0, MemoryReadOnly);
        const unsigned char sucessful = fileLoadingResult == ResultSuccessful;

        if(!sucessful)
        {
            return fileLoadingResult;
        }
    }

    {
        const ImageFileFormat imageFormatHint = ImageGuessFormat(filePath);
        const ActionResult fileParsingResult = ImageLoadD(image, file.Data, file.DataSize, imageFormatHint);
        const unsigned char success = fileParsingResult == ResultSuccessful;

        if(success)
        {
            return ResultSuccessful;
        }

        ActionResult fileGuessResult = ResultInvalid;
        unsigned int fileFormatID = 1;

        do
        {
            const ImageFileFormat imageFileFormat = fileGuessResult + fileFormatID;

            fileGuessResult = ImageLoadD(image, file.Data, file.DataSize, imageFileFormat);

            fileFormatID++;
        }
        while(fileGuessResult == ResultInvalidHeaderSignature);

        return fileGuessResult;
    }

    FileDestruct(&file);
}

ActionResult ImageLoadD(Image* const image, const void* const data, const size_t dataSize, const ImageFileFormat guessedFormat)
{
    size_t bytesRead = 0;
    ParseToImage parseToImage = 0;

    switch(guessedFormat)
    {
        case ImageFileFormatBitMap:
        {
            parseToImage = BMPParseToImage;
            break;
        }
        case ImageFileFormatGIF:
        {
            parseToImage = GIFParseToImage;
            break;
        }
        case ImageFileFormatJPEG:
        {
            parseToImage = JPEGParseToImage;
            break;
        }
        case ImageFileFormatPNG:
        {
            parseToImage = PNGParseToImage;
            break;
        }
        case ImageFileFormatTGA:
        {
            parseToImage = TGAParseToImage;
            break;
        }
        case ImageFileFormatTIFF:
        {
            parseToImage = TIFFParseToImage;
            break;
        }
        default:
        {
            return ResultFormatNotSupported;
        }
    }

    const ActionResult actionResult = parseToImage(image, data, dataSize, &bytesRead);

    return actionResult;
}

ActionResult ImageSaveA(Image* const image, const char* const filePath, const ImageFileFormat fileFormat, const ImageDataFormat dataFormat)
{
    wchar_t filePathW[PathMaxSize];

    TextCopyAW(filePath, PathMaxSize, filePathW, PathMaxSize);

    ActionResult actionResult = ImageSaveW(image, filePathW, fileFormat, dataFormat);

    return actionResult;
}

ActionResult ImageSaveW(Image* const image, const wchar_t* const filePath, const ImageFileFormat fileFormat, const ImageDataFormat dataFormat)
{
    wchar_t filePathW[PathMaxSize];
    wchar_t* fileExtension = 0;

    size_t fileSize = 0;
    size_t writtenBytes = 0;
    File file;  

    SerializeFromImage serializeFromImageFunction = 0;

    FileConstruct(&file);

    switch(fileFormat)
    {    
        case ImageFileFormatBitMap:
        {
            fileSize = BMPFilePredictSize(image->Width, image->Height, ImageBitsPerPixel(dataFormat));
            serializeFromImageFunction = BMPSerializeFromImage;
            fileExtension = L"bmp";
            break;
        }
        case ImageFileFormatPNG:
        {
            fileSize = PNGFilePredictSize(image->Width, image->Height, ImageBitsPerPixel(dataFormat));
            serializeFromImageFunction = PNGSerializeFromImage;
            fileExtension = L"png";
            break;
        }
        case ImageFileFormatTGA:
        {
            fileSize = TGAFilePredictSize(image->Width, image->Height, ImageBitsPerPixel(dataFormat));
            serializeFromImageFunction = TGASerializeFromImage;
            fileExtension = L"tga";
            break;
        }
        case ImageFileFormatJPEG:
        {
            fileSize = JPEGFilePredictSize(image->Width, image->Height, ImageBitsPerPixel(dataFormat));
            serializeFromImageFunction = JPEGSerializeFromImage;
            fileExtension = L"jpg";
            break;
        }
        case ImageFileFormatTIFF:
        {
            fileSize = TIFFFilePredictSize(image->Width, image->Height, ImageBitsPerPixel(dataFormat));
            serializeFromImageFunction = TIFFSerializeFromImage;
            fileExtension = L"tiff";
            break;
        }
        case ImageFileFormatGIF:
        {
            fileSize = GIFFilePredictSize(image->Width, image->Height, ImageBitsPerPixel(dataFormat));
            serializeFromImageFunction = GIFSerializeFromImage;
            fileExtension = L"gif";
            break;
        }
        case ImageFileFormatUnkown:
        default:
            return ResultFormatNotSupported;
    }


    // Chnage file extension
    {
        FilePathSwapExtensionW(filePath, filePathW, fileExtension);
    }

    {
        const ActionResult mappingResult = FileMapToVirtualMemoryW(&file, filePathW, fileSize, MemoryWriteOnly);
        const unsigned char sucessful = ResultSuccessful == mappingResult;

        if(!sucessful)
        {
            FileDestruct(&file);
            return mappingResult;
        }
    }

    {
        const ActionResult serializeResult = serializeFromImageFunction(image, file.Data, file.DataSize, &file.DataCursor);
        const unsigned char sucessful = ResultSuccessful == serializeResult;

        if(!sucessful)
        {
            FileDestruct(&file);
            return serializeResult;
        }
    }

    FileDestruct(&file);

    return ResultSuccessful;
}

ActionResult ImageSaveD(Image* const image, void* const data, const size_t dataSize, const ImageFileFormat fileFormat, const ImageDataFormat dataFormat)
{
    return ResultInvalid;
}

void ImageResize(Image* image, const ImageDataFormat format, const size_t width, const size_t height)
{
    const size_t bbp = ImageBytePerPixel(format);
    const size_t newSize = width * height * bbp;
    const size_t oldSize = image->PixelDataSize;

    if(newSize == oldSize)
    {
        return;
    }

    const void* newadress = MemoryReallocate(image->PixelData, sizeof(unsigned char) * newSize);

    if(!newadress)
    {
        return;
    }

    image->Format = format;
    image->Width = width;
    image->Height = height;
    image->PixelData = newadress;
    image->PixelDataSize = newSize;
} 

void ImageFlipHorizontal(Image* image)
{
    const size_t bbp = ImageBytePerPixel(image->Format);
    const size_t rowSize = (image->Width * bbp);
    const size_t length = (image->Width * bbp) / 2;

    for(size_t x = 0; x < length; x += bbp) // 
    {
        const size_t xB = rowSize - x - bbp;

        for(size_t y = 0; y < image->Height; y++)
        {
            const size_t indexA = x + (y * rowSize);
            const size_t indexB = xB + (y * rowSize);
            unsigned char tempByte[4] = { 0,0,0,0 };
            unsigned char* pixelA = (unsigned char*)image->PixelData + indexA;
            unsigned char* pixelB = (unsigned char*)image->PixelData + indexB;

            MemoryCopy(pixelA, 4, tempByte, bbp);
            MemoryCopy(pixelB, 4, pixelA, bbp);
            MemoryCopy(tempByte, 4, pixelB, bbp);
        }
    }
}

void ImageFlipVertical(Image* image)
{
    const size_t bbp = ImageBytePerPixel(image->Format);;
    const size_t scanLineWidthSize = image->Width * bbp;
    const size_t scanLinesToSwap = image->Height / 2u;
    unsigned char* copyBufferRow = MemoryAllocate(sizeof(unsigned char) * scanLineWidthSize);

    if(!copyBufferRow)
    {
        return;
    }

    for(size_t scanlineIndex = 0; scanlineIndex < scanLinesToSwap; scanlineIndex++)
    {
        unsigned char* bufferA = (unsigned char*)image->PixelData + (scanlineIndex * scanLineWidthSize);
        unsigned char* bufferB = (unsigned char*)image->PixelData + ((image->Height - scanlineIndex) * scanLineWidthSize) - scanLineWidthSize;

        MemoryCopy(bufferB, scanLineWidthSize, copyBufferRow, scanLineWidthSize); // A -> Buffer 'Save A'
        MemoryCopy(bufferA, scanLineWidthSize, bufferB, scanLineWidthSize); // B -> A 'Move B to A(override)'
        MemoryCopy(copyBufferRow, scanLineWidthSize, bufferA, scanLineWidthSize); // Buffer -> B 'Move SaveCopy (A) to B'
    }

    MemoryRelease(copyBufferRow, scanLineWidthSize);
}

void ImageRemoveColor(Image* image, unsigned char red, unsigned char green, unsigned char blue)
{
}

void* ImageDataPoint(const Image* const image, const size_t x, const size_t y)
{
    const size_t index = x * 3u + y * image->Width;

    return (unsigned char*)image->PixelData + index;
}

void ImageDrawRectangle
(
    Image* const image, 
    const size_t x,
    const size_t y,
    const size_t width, 
    const size_t height, 
    const unsigned char red, 
    const unsigned char green, 
    const unsigned char blue, 
    const unsigned char alpha
)
{
    //unsigned char* data = ImageDataPoint(image, x, y);

    const size_t mimimumInBoundsX = MathMinimum(x + width, image->Width);
    const size_t mimimumInBoundsY = MathMinimum(y + height, image->Height);
    
    for (size_t cy = y; cy < mimimumInBoundsY; ++cy)
    {
        for (size_t cx = x; cx < mimimumInBoundsX; ++cx)
        {
            const size_t index = cx *3u + cy * image->Width*3u;

            ((unsigned char*)image->PixelData)[index+0] = red;
            ((unsigned char*)image->PixelData)[index+1] = green;
            ((unsigned char*)image->PixelData)[index+2] = blue;
        }
    }      
}

void ImageDrawTextA(Image* const image, const size_t x, const size_t y, const size_t width, const size_t height, const CFont* const font, const char* text)
{
    wchar_t textW[1024];

    TextCopyAW(text, 1024, textW, 1024);

    ImageDrawTextW(image, x, y, width, height, font, textW);
}

void ImageDrawTextW
(
    Image* const image,
    const size_t x,
    const size_t y,
    const size_t width,
    const size_t height,
    const CFont* const font,
    const wchar_t* text
)
{
    float fontSize = 0.002;
    float lastPositionX = x;


   // FNTPrtinf(&font->BitMapFont);

    for (size_t i = 0; (i < 1024u) && (text[i] != '\0'); ++i)
    {
        const wchar_t character = text[i];
        const FNTCharacter* fntCharacter = FNTGetCharacter(&font->FontElement[0], character);

        if (!fntCharacter)
        {
            // Add red box?

            continue;
        }

        float offsetX = fntCharacter->Offset[0];
        float offsetY = fntCharacter->Offset[1];
        float positionX = fntCharacter->Position[0];
        float positionY = fntCharacter->Position[1];
        float sizeX = fntCharacter->Size[0];
        float sizeY = fntCharacter->Size[1];
             
#if 0
        ImageDrawRectangle
        (
            image, 
            lastPositionX+ offsetX, 
            y+ offsetY,
            sizeX,
            sizeY, 
            0xFF,
            0,
            0xFF, 
            0
        );
#endif
        ImageMerge
        (
            image,
            lastPositionX + offsetX, 
            y + offsetY, 
            positionX,
            positionY,
            sizeX,
            sizeY,       
            &font->FontElement[0].FontPageList[0].FontTextureMap
        );

        lastPositionX += fntCharacter->XAdvance;
        //lastPositionX += 15;
    }
}

void ImageMerge
(
    Image* const image,
    const size_t x,
    const size_t y,
    const size_t insertX,
    const size_t insertY,
    const size_t insertWidth,
    const size_t insertHeight,
    const Image* const imageInsert
)
{

    //unsigned char* data = ImageDataPoint(image, x, y);

    const size_t sourceMimimumInBoundsX = MathMinimum(x + insertWidth, image->Width);
    const size_t sourceMimimumInBoundsY = MathMinimum(y + insertHeight, image->Height);
    const size_t targetMimimumInBoundsX = MathMinimum(insertX + insertWidth, imageInsert->Width);
    const size_t targetMimimumInBoundsY = MathMinimum(insertY + insertHeight, imageInsert->Height);

    const size_t sourceBytesPerPixel = ImageBytePerPixel(image->Format);
    const size_t targetBytesPerPixel = ImageBytePerPixel(imageInsert->Format);
    const size_t bytesPerPixel = MathMinimum(sourceBytesPerPixel, targetBytesPerPixel);

    for (size_t cy = 0u; cy < insertHeight; ++cy)
    {
        for (size_t cx = 0u; cx < insertWidth; ++cx)
        {
            const size_t indexSource = (cx + x) * sourceBytesPerPixel + (cy + y) * image->Width * sourceBytesPerPixel;
            const size_t indexTarget = (cx + insertX) * targetBytesPerPixel + (cy + insertY) * imageInsert->Width * targetBytesPerPixel;

            unsigned char* source = ((unsigned char*)image->PixelData) + indexSource;
            unsigned char* target = ((unsigned char*)imageInsert->PixelData) + indexTarget;

            if(targetBytesPerPixel == 4)
            {
                if(target[3] == 0)
                {
                    continue;
                }
            }

            for(size_t i = 0; i < bytesPerPixel; ++i)
            {
                source[i] = target[i];
            }
        }
    }
}