#include "ImageLoader.h"

#include "../../Time/StopWatch.h"
#include "PNG/PNG.h"

BF::ImageFileExtension BF::ImageLoader::CheckImageFormat(AsciiString& fileExtension)
{
    bool isBMP = fileExtension.CompareIgnoreCase("bmp");
    bool isGIF = fileExtension.CompareIgnoreCase("gif");
    bool isJPEG = fileExtension.CompareIgnoreCase("jpeg");
    bool isPNG = fileExtension.CompareIgnoreCase("png");
    bool isTGA = fileExtension.CompareIgnoreCase("tga");
    bool isTIFF = fileExtension.CompareIgnoreCase("tiff");

    if (isBMP) return ImageFileExtension::BMP;
    if (isGIF) return ImageFileExtension::GIF;
    if (isJPEG) return ImageFileExtension::JPEG;
    if (isPNG) return ImageFileExtension::PNG;
    if (isTGA) return ImageFileExtension::TGA;
    if (isTIFF) return ImageFileExtension::TIFF;

    return ImageFileExtension::Unkown;
}

bool BF::ImageLoader::IsImageFileExtension(AsciiString& fileExtension)
{
    return CheckImageFormat(fileExtension) != ImageFileExtension::Unkown;
}

BF::Image* BF::ImageLoader::LoadFromFile(AsciiString& filePath)
{
    Image* image = new Image();
    TextFile textFile(filePath);
    AsciiString fileExtension = textFile.FileExtension;
    ImageFileExtension imageFormat = CheckImageFormat(fileExtension);

    switch (imageFormat)
    {
        case ImageFileExtension::BMP:
        {
            BMP bitmap;
            bitmap.Load(filePath);   
            bitmap.Convert(*image);
            break;
        }
        case ImageFileExtension::GIF:
        {
            break;
        }
        case ImageFileExtension::JPEG:
        {
            break;
        }  
        case ImageFileExtension::PNG:
        {
            PNG png;
            png.Load(filePath);
            png.Convert(*image);
            break;
        }
        case ImageFileExtension::TGA:
        {            
            TGA tga;
            tga.Load(filePath);
            tga.Convert(*image);            
            break;
        }
        case ImageFileExtension::TIFF:
        {
            break;
        }           

        case ImageFileExtension::Unkown:
        default:
            throw "Unsuported Type/File";
    }

    image->FilePath.Copy(filePath);

    return image;
}
