#include "ImageLoader.h"

BF::ImageFormat BF::ImageLoader::CheckImageFormat(AsciiString& fileExtension)
{
    bool isBMP = fileExtension.CompareIgnoreCase("bmp");
    bool isGIF = fileExtension.CompareIgnoreCase("gif");
    bool isJPEG = fileExtension.CompareIgnoreCase("jpeg");
    bool isPNG = fileExtension.CompareIgnoreCase("png");
    bool isTIFF = fileExtension.CompareIgnoreCase("tiff");

    if (isBMP) return ImageFormat::BMP;
    if (isGIF) return ImageFormat::GIF;
    if (isJPEG) return ImageFormat::JPEG;
    if (isPNG) return ImageFormat::PNG;
    if (isTIFF) return ImageFormat::TIFF;

    return ImageFormat::Unkown;
}

bool BF::ImageLoader::IsImageFileExtension(AsciiString& fileExtension)
{
    return CheckImageFormat(fileExtension) != ImageFormat::Unkown;
}

BF::Image* BF::ImageLoader::LoadFromFile(AsciiString& filePath)
{    
    Image* image = new Image();
    TextFile textFile(filePath);
    AsciiString fileExtension = textFile.FileExtension;
    ImageFormat imageFormat = CheckImageFormat(fileExtension); 

    switch (imageFormat)
    {
        case ImageFormat::BMP:
        {
            Log::Write(LogMessageType::Event, "[.BMP] BitMap File detected.");

            BMP* bmp = BMPLoader::LoadFromFile(filePath);

            image = BMPToImage(bmp);
                        
            break;
        }          

        case ImageFormat::GIF:
            Log::Write(LogMessageType::Event, "[.GIF] GIF File detected.");
            break;

        case ImageFormat::JPEG:        
            Log::Write(LogMessageType::Event, "[.JPEG] JPEG File detected.");
            break;        

        case ImageFormat::PNG:            
            {
                PNG png;
                PNGLoader::LoadFromFile(filePath, png);                
                PNGLoader::PNGToImage(png, *image);
                break;
            }

            break;

        case ImageFormat::TIFF:
            Log::Write(LogMessageType::Event, "[.TIFF] TIFF File detected.");
            break;

        case ImageFormat::Unkown:
        default:
            throw "Unsuported Type/File";
    }

    image->FilePath.Copy(filePath);

    return image;
}



BF::Image* BF::ImageLoader::BMPToImage(BMP* bitmap)
{
    Image* image = new Image();
    unsigned int dynamicIndex = 0;
    int height = bitmap->Height;
    int width = bitmap->Width;
    int dimension = 4;
    int size = bitmap->Pixel.Size();


    size *= dimension;
    image->Height = height;
    image->Width = width;

    image->PixelData.ReSize(size);
    /*
    
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            RGB8Bit* pixel = bitmap->GetPixel(x, y);

            image->PixelData[dynamicIndex++] = pixel->Red;
            image->PixelData[dynamicIndex++] = pixel->Green;
            image->PixelData[dynamicIndex++] = pixel->Blue;
            image->PixelData[dynamicIndex++] = '\xFF';
        }
    } 
    */
    
    for (unsigned int i = 0; i < bitmap->Pixel.Size(); i++)
    {
        RGB<unsigned char>* pixel = &bitmap->Pixel[i];

        image->PixelData[dynamicIndex++] = pixel->Red;
        image->PixelData[dynamicIndex++] = pixel->Green;
        image->PixelData[dynamicIndex++] = pixel->Blue;
        image->PixelData[dynamicIndex++] = '\xFF';
    }

    return image;
}

BF::Image* BF::ImageLoader::GIFToImage(GIF* bitmap)
{
    return nullptr;
}

BF::Image* BF::ImageLoader::JPEGToImage(JPEG* bitmap)
{
    return nullptr;
}

BF::Image* BF::ImageLoader::PNGToImage(PNG* bitmap)
{
    return nullptr;
}

BF::Image* BF::ImageLoader::TIFFToImage(TIFF* bitmap)
{
    return nullptr;
}