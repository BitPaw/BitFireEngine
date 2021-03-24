#pragma once

#include "../IImage.h"
#include "Chunk/PNGChunk.h"
#include "Chunk/PNGHeader.h"
#include "Chunk/PNGPalette.h"
#include "Chunk/PNGPrimaryChromaticities.h"
#include "Chunk/PNGImageGamma.h"
#include "Chunk/PNGSignificantBits.h"
#include "Chunk/PNGBackgroundColor.h"
#include "Chunk/PNGPaletteHistogram.h"
#include "Chunk/PNGTransparency.h"

#include "../../Compression/ZLIB/ZLibHeader.h"
#include "Chunk/PNGStandardRGBColorSpace.h"
#include "Chunk/PNGStandardRGBColorSpace.h"
#include "Chunk/PNGPhysicalPixelDimensions.h"


namespace BF
{
	struct PNG : public IImage
	{
		public:
		PNGHeader Header; // IHDR
		PNGPalette Palette; // PLTE

		PNGPrimaryChromaticities PrimaryChromaticities; // cHRM
		PNGImageGamma ImageGamma; // gAMA
		PNGSignificantBits SignificantBits; // sBIT
		PNGBackgroundColor BackgroundColor; // bKGD
		PNGPaletteHistogram PaletteHistogram; // hIST
		PNGTransparency Transparency; // tRNS

		PNGStandardRGBColorSpace StandardRGBColorSpace;

		// oFFs
		PNGPhysicalPixelDimensions PhysicalPixelDimensions;// pHYs
		// sCAL
		// tIME
		// tEXt
		// zTXt
		// fRAc
		// gIFg
		// gIFt
		// gIFx
		
		/*
		Chunk Type 	Multiple	Optional 	Position
		IHDR 		No 			No 			First chunk
		cHRM 		No 			Yes 		Before PLTE and IDAT
		gAMA 		No 			Yes 		Before PLTE and IDAT
		sBIT 		No 			Yes			Before PLTE and IDAT
		PLTE 		No 			Yes			Before IDAT
		bKGD 		No 			Yes 		After PLTE and before IDAT
		hIST 		No 			Yes 		After PLTE and before IDAT
		tRNS 		No 			Yes			After PLTE and before IDAT
		oFFs 		No 			Yes			Before IDAT
		pHYs 		No 			Yes			Before IDAT
		sCAL 		No 			Yes 		Before IDAT
		IDAT 		Yes 		No 			Contiguous with other IDATs
	 	tIME 		No 			Yes			Any
		tEXt 		Yes			Yes			Any
		zTXt 		Yes			Yes 		Any
		fRAc 		Yes			Yes 		Any
		gIFg 		Yes			Yes 		Any
		gIFt 		Yes			Yes 		Any
		gIFx 		Yes			Yes 		Any
		IEND 		No 			No 			Last chunk
		*/



		// Temp
		ZLibHeader zlib;

		void PrintData();
	};
}