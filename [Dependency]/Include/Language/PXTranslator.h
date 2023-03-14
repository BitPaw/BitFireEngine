#ifndef PXTranslatorINCLUDE
#define PXTranslatorINCLUDE

#include <OS/Error/PXActionResult.h>
#include <Format/Type.h>
#include <File/PXDataStream.h>

#ifdef __cplusplus
extern "C"
{
#endif
   
	PXPublic PXActionResult PXTranslatorEnglishToGerman(PXDataStream* const inputStreamEnglish, PXDataStream* const outputStreamGerman);
	PXPublic PXActionResult PXTranslatorGermanToEnglish(PXDataStream* const inputStreamGerman, PXDataStream* const outputStreamEnglish);

#ifdef __cplusplus
}
#endif

#endif