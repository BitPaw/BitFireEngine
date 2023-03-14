#ifndef SerializationINCLUDE
#define SerializationINCLUDE

#include <Format/Type.h>

#ifdef __cplusplus
extern "C"
{
#endif

	typedef enum SerializationType_
	{
		SerializationTypeInvalid,
		
		SerializationTypeBool,

		SerializationTypeIntegerSigned8,
		SerializationTypeIntegerUnsigned8,
		SerializationTypeIntegerSigned16,
		SerializationTypeIntegerUnsigned16,
		SerializationTypeIntegerSigned32,
		SerializationTypeIntegerUnsigned32,
		SerializationTypeIntegerSigned64,
		SerializationTypeIntegerUnsigned64,

		SerializationTypeFloat,
		SerializationTypeDouble,

		SerializationTypeStringASCII,
		SerializationTypeFloatUNICODE,
		SerializationTypeFloatUTF
	}
	SerializationType;

	// Example i want, xxxx("ID", &ID, sizeof(ID), TYpeUnyi64, )
	
	typedef struct SerializationTypeInfo_ SerializationTypeInfo;

	typedef struct SerializationTypeInfo_
	{
		// Field Info
		char* Name; // Name a field
		void* Adress; // Adress of field		
		PXSize Size; // Size of field
		SerializationType Type; // Type of field

		SerializationTypeInfo* Parent;
		unsigned char Depth;

	}
	SerializationTypeInfo;

	PXPublic void SerializationTypeInfoSet
	(
		SerializationTypeInfo* serializationTypeInfo,
		const char* name, 
		void* adress, 
		const PXSize size, 
		SerializationType type,
		SerializationTypeInfo* parent,
		unsigned char depth
	);


#ifdef __cplusplus
}
#endif

#endif