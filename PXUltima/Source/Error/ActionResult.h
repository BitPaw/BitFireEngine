#ifndef ActionResultInclude
#define ActionResultInclude

#ifdef __cplusplus
extern "C"
{
#endif

	typedef enum ActionResult_
	{
		ResultInvalid,

		// File


		ResultSuccessful,

		ResultEmptyPath,

		// Classic
		ResultFileNotFound,
		ResultOutOfMemory,
		ResultFileEmpty,

		ResultWriteFailure,

		//
		ResultFileOpenFailure,
		ResultFileCloseFailure,
		ResultFileReadFailure,
		ResultFileCopyFailure,
		ResultFileCreateFailure,

		ResultFileMemoryMappingFailed,

		// Parsing
		ResultInvalidHeaderSignature,
		ResultInvalidVersion,

		ResultFormatNotSupported,
		ResultFormatNotAsExpected

	}
	ActionResult;

#ifdef __cplusplus
}
#endif

#endif