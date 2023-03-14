#ifndef YAMLINCLUDE
#define YAMLINCLUDE

#include <OS/Error/PXActionResult.h>
#include <Format/Type.h>
#include <File/PXDataStream.h>
#include <Serialization/Serialization.h>

#ifdef __cplusplus
extern "C"
{
#endif

	typedef enum YAMLLineType_
	{
		YAMLLineTypeInvalid,
		YAMLLineTypeUnkown,
		YAMLLineTypeComment,
		YAMLLineTypeKeyDeclare,
		YAMLLineTypeKeyValueSeperator,
		YAMLLineTypeKeyValueDeclare,

		YAMLLineTypeListElement,
		YAMLLineTypeSeperator,
		YAMLLineTypeNotationStyleBlock,
		YAMLLineTypeNotationStyleExtendedLine
	}
	YAMLLineType;

	PXPrivate YAMLLineType YAMLPeekLine(const void* line, const PXSize size);

	PXPublic PXActionResult YAMLFileCompile(PXDataStream* const inputStream, PXDataStream* const outputStream);

	PXPublic PXActionResult YAMLFileParse(PXDataStream* const ymlTokenInputStream, SerializationTypeInfo* const serializationTypeInfoList, const PXSize serializationTypeInfoListSize);

#ifdef __cplusplus
}
#endif

#endif
