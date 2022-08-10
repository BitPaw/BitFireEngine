#ifndef ColorInclude
#define ColorInclude

#ifdef __cplusplus
extern "C"
{
#endif

	typedef enum ColorFormat_
	{
		ColorFormatInvalid,
		ColorFormatRGB,
		ColorFormatYCbCr
	}
	ColorFormat;

	typedef struct ColorRGB_
	{
		unsigned char Red;
		unsigned char Green;
		unsigned char Blue;
	}
	ColorRGB;

	typedef struct ColorYCbCr_
	{
		unsigned char Y;
		unsigned char Cb;
		unsigned char Cr;
	}
	ColorYCbCr;

	//---[ Public-Functions ]----------------------------------------------

	extern void ConvertColorRGBToYCbCr(const ColorRGB* const colorRGB, ColorYCbCr* const ColorYCbCr);
	extern void ConvertColorYCbCrToRGB(const ColorYCbCr* const colorYCbCr, ColorRGB* const colorRGB);

#ifdef __cplusplus
}
#endif

#endif



