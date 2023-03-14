#ifndef SoundINCLUDE
#define SoundINCLUDE

#include <Format/Type.h>

#ifdef __cplusplus
extern "C"
{
#endif

	typedef struct PXSound_
	{
		unsigned short NumerOfChannels;
		unsigned int SampleRate;
		unsigned short BitsPerSample;

		PXSize DataSize;
		void* Data;
	}
	PXSound;


#ifdef __cplusplus
}
#endif

#endif
