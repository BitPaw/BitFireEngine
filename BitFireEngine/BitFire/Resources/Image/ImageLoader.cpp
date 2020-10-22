#include "ImageLoader.h"
#include "../../OpenGL/OpenGLAPI.h"

BF::IImage* BF::ImageLoader::LoadFromFile(std::string filePath)
{    
    Image* image = nullptr;
    ImageFormat imageFormat = ImageFormat::Unkown;
    TextFile textFile(filePath);
    std::string fileExtension = textFile.GetFileExtension();

    bool isBMP = fileExtension == "bmp";
    bool isGIF = fileExtension == "gif";
    bool isJPEG = fileExtension == "jpeg";
    bool isPNG = fileExtension == "png";
    bool isTIFF = fileExtension == "tiff";

    if (isBMP) imageFormat = ImageFormat::BMP;
    if (isGIF) imageFormat = ImageFormat::GIF;
    if (isJPEG) imageFormat = ImageFormat::JPEG;
    if (isPNG) imageFormat = ImageFormat::PNG;
    if (isTIFF) imageFormat = ImageFormat::TIFF;

    switch (imageFormat)
    {
        case ImageFormat::BMP:
        {
            MessageSystem::PushMessage(MessageType::Info, "[.BMP] BitMap File detected.");

            BMP* bmp = BMPLoader::LoadFromFile(filePath);

            image = BMPToImage(bmp);

            break;
        }          

        case ImageFormat::GIF:
            MessageSystem::PushMessage(MessageType::Info, "[.GIF] GIF File detected.");
            break;

        case ImageFormat::JPEG:        
            MessageSystem::PushMessage(MessageType::Info, "[.JPEG] JPEG File detected.");
            break;        

        case ImageFormat::PNG:
            MessageSystem::PushMessage(MessageType::Info, "[.PNG] PNG File detected.");
            break;

        case ImageFormat::TIFF:
            MessageSystem::PushMessage(MessageType::Info, "[.TIFF] TIFF File detected.");
            break;

        case ImageFormat::Unkown:
        default:
            throw "Unsuported Type/File";
    }

    OpenGLAPI* openGLAPI = OpenGLAPI::Instance();

    openGLAPI->Render->RegisterImage(image);

    return image;
}

BF::Image* BF::ImageLoader::BMPToImage(BMP* bitmap)
{
    Image* image = new Image();
    unsigned int dynamicIndex = 0;
    int height = bitmap->Height;
    int width = bitmap->Width;
    int dimension = 4;
    int size = bitmap->Pixel.Size.Value;


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
    
    for (unsigned int i = 0; i < bitmap->Pixel.Size.Value; i++)
    {
        RGB8Bit* pixel = &bitmap->Pixel[i];

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