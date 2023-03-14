#ifndef PXFTPINCLUDE
#define PXFTPLINCLUDE

#include <Format/Type.h>

#ifdef __cplusplus
extern "C"
{
#endif

	typedef enum PXFTPCommand_
	{
		PXFTPCommandInvalid,
		PXFTPCommandUser,
		PXFTPCommandPassword, // PASS
		PXFTPCommandAccount, // ACCT
		PXFTPCommandWorkingDirectoryChange, // CWD
		PXFTPCommandDirectoryGoToParent, // CDUP
		PXFTPCommandSMNT, // SMNT
		PXFTPCommandQuit, // QUIT
		PXFTPCommandREIN, // REIN
		PXFTPCommandPORT,
		PXFTPCommandPASV,
		PXFTPCommandTYPE,
		PXFTPCommandSTRU,
		PXFTPCommandMODE,
		PXFTPCommandRETR,
		PXFTPCommandSTOR,
		PXFTPCommandStoreUnique,
		PXFTPCommandAPPE,
		PXFTPCommandALLO,
		PXFTPCommandREST,
		PXFTPCommandFileRenameFrom, // RNFR
		PXFTPCommandFileRenameTo, // RNTO
		PXFTPCommandAbort, // ABOR
		PXFTPCommandDelete, // DELE
		PXFTPCommandDirectoryRemove,
		PXFTPCommandMKD,
		PXFTPCommandDirectoryPrint,
		PXFTPCommandList,
		PXFTPCommandNLST,
		PXFTPCommandSITE,
		PXFTPCommandSYST,
		PXFTPCommandSTAT,
		PXFTPCommandHELP,
		PXFTPCommandNOOP,
	}
	PXFTPCommand;

	typedef enum PXFTPResult_
	{
		PXFTPResultInvalid,

		// 1xx
		// 110 Restart marker reply.
		// 120 Service ready in nnn minutes.
		// 125 Data connection already open; transfer starting.
		// 150 File status okay; about to open data connection.
		// 120 Service ready in nnn minutes.
		// 150 File status okay; about to open data connection.

		//---------------------------------------------------------------------

		// 2xx

		PXFTPResultOK, // 200 Command okay.
		PXFTPResultCommandNotImplemented, // 202 Command not implemented, superfluous at this site.
		PXFTPResultSystemStatus, // 211 System status, or system help reply.
		PXFTPResultDirectoryStatus, // 212 Directory status.
		PXFTPResultFileStatus, // 213 File status.
		PXFTPResultHelp, // 214 Help message.
		PXFTPResultName, // 215 NAME system type.
		PXFTPResultLoginReady, // 220 Service ready for new user.
		PXFTPResultServiceClosed, // 221 Service closing control connection.Logged out if appropriate.
		PXFTPResultServiceReady, // 225 Data connection open; no transfer in progress.
		PXFTPResultPassiveModeNowActive,// 227 Entering Passive Mode(h1, h2, h3, h4, p1, p2).
		PXFTPResultLoginCompleate,// 230 User logged in, proceed.
		PXFTPResultFileActionOK,// 250 Requested file action okay, completed.
		PXFTPResultPathNameCreated,// 257 "PATHNAME" created. 
		//---------------------------------------------------------------------


		// 3xx
		PXFTPResultLoginUserOKButPasswordMissing, // 331 User name okay, need password.
		PXFTPResultLoginAccountNeeded, // 332 Need account for login.
		PXFTPResultActionPending, // 350 Requested file action pending further information.
		//---------------------------------------------------------------------

		// 4xx
		PXFTPResultServiceNotAvailable, // 421 Service not available, closing control connection.
		PXFTPResultConnectionCantBeOpened, // 425 Can’t open data connection.
		PXFTPResultConnectionClosed, // 426 Connection closed; transfer aborted.
		// 450 Requested file action not taken.File unavailable(e.g., file busy).
		PXFTPResultActionAborted, // 451 Requested action aborted : local error in processing.
		// 452 Requested action not taken.Insufficient storage space in system.
		//---------------------------------------------------------------------

		// 5xx
		PXFTPResultCommandInvalid, // 500 Syntax error, command unrecognized.	This may include errors such as command line too long.
		PXFTPResultParameterSyntaxError, // 501 Syntax error in parameters or arguments.
		
		// 503 Bad sequence of commands.
		// 504 Command not implemented for that parameter.
		// 500 Syntax error, command unrecognized.This may include errors such as command line too long.
		// 501 Syntax error in parameters or arguments.
		// 502 Command not implemented.
		// 503 Bad sequence of commands.
		// 504 Command not implemented for that parameter.
		PXFTPResultUserNotLoggedIn, // 530 Not logged in.
		// 532 Need account for storing files.
		// 550 Requested action not taken.File unavailable(e.g., file not found, no access).
		// 551 Requested action aborted : page type unknown.
		PXFTPResultSpaceTooSmal, //  552 Requested file action aborted.Exceeded storage allocation(for current directory or dataset).
		PXFTPResultFileNameRejected, // 553 Requested action not taken.File name not allowed.
		//---------------------------------------------------------------------

	}
	PXFTPResult;

	PXPublic PXFTPResult PXFTPResultParse(const unsigned short resultID);



	PXPublic PXSize PXFTPCommandBuildBare(const char* tag, char* const dataBuffer, const PXSize dataBufferSize);
	PXPublic PXSize PXFTPCommandBuild(const char* tag, const char* middle, char* const dataBuffer, const PXSize dataBufferSize);


	// USER <SP> <username> <CRLF>
	PXPublic PXSize PXFTPCommandBuildUser(const char* username, char* const dataBuffer, const PXSize dataBufferSize);

	// 	PASS <SP> <password> <CRLF>
	PXPublic PXSize PXFTPCommandBuildPassword(const char* password, char* const dataBuffer, const PXSize dataBufferSize);

	// ACCT <SP> <account - information> <CRLF>
	//PXPublic PXSize PXFTPCommandBuildAccountInfo(const char* username, char* const dataBuffer, const PXSize dataBufferSize);

	// CWD <SP> <pathname> <CRLF>
	PXPublic PXSize PXFTPCommandBuiltWorkDirectoryChange(const char* pathname, char* const dataBuffer, const PXSize dataBufferSize);

	// CDUP <CRLF>
	PXPublic PXSize PXFTPCommandBuildCDUP(char* const dataBuffer, const PXSize dataBufferSize);

	// SMNT <SP> <pathname> <CRLF>
	PXPublic PXSize PXFTPCommandBuildSMNT(const char* pathname, char* const dataBuffer, const PXSize dataBufferSize);

	// QUIT <CRLF>
	PXPublic PXSize PXFTPCommandBuildQUIT(char* const dataBuffer, const PXSize dataBufferSize);

	// REIN <CRLF>
	PXPublic PXSize PXFTPCommandBuildREIN(char* const dataBuffer, const PXSize dataBufferSize);

	// PORT <SP> <host - port> <CRLF>
	PXPublic PXSize PXFTPCommandBuildPORT(const char* port, char* const dataBuffer, const PXSize dataBufferSize);

	// PASV <CRLF>
	PXPublic PXSize PXFTPCommandBuildPASV(char* const dataBuffer, const PXSize dataBufferSize);

	// 	TYPE <SP> <type - code> <CRLF>
	PXPublic PXSize PXFTPCommandBuildTYPE(const char* code, char* const dataBuffer, const PXSize dataBufferSize);

	// STRU <SP> <structure - code> <CRLF>
	PXPublic PXSize PXFTPCommandBuildSTRU(const char* code, char* const dataBuffer, const PXSize dataBufferSize);

	// MODE <SP> <mode - code> <CRLF>
	PXPublic PXSize PXFTPCommandBuildMODE(const char* mode, char* const dataBuffer, const PXSize dataBufferSize);

	// RETR <SP> <pathname> <CRLF>
	PXPublic PXSize PXFTPCommandBuildRETR(const char* pathname, char* const dataBuffer, const PXSize dataBufferSize);

	// STOR <SP> <pathname> <CRLF>		
	PXPublic PXSize PXFTPCommandBuildSTOR(const char* pathname, char* const dataBuffer, const PXSize dataBufferSize);

	// STOU <CRLF>
	PXPublic PXSize PXFTPCommandBuildSTOU(char* const dataBuffer, const PXSize dataBufferSize);

	// APPE <SP> <pathname> <CRLF>
	PXPublic PXSize PXFTPCommandBuildAPPE(const char* marker, char* const dataBuffer, const PXSize dataBufferSize);

	// ALLO <SP> <decimal - integer>	[<SP> R <SP> <decimal - integer>] <CRLF>
	PXPublic PXSize PXFTPCommandBuildALLO(const char* text, char* const dataBuffer, const PXSize dataBufferSize);

	// REST <SP> <marker> <CRLF>
	PXPublic PXSize PXFTPCommandBuildREST(const char* marker, char* const dataBuffer, const PXSize dataBufferSize);

	// RNFR <SP> <pathname> <CRLF>
	PXPublic PXSize PXFTPCommandBuildRNFR(const char* pathname, char* const dataBuffer, const PXSize dataBufferSize);

	// RNTO <SP> <pathname> <CRLF>
	PXPublic PXSize PXFTPCommandBuildRNTO(const char* pathname, char* const dataBuffer, const PXSize dataBufferSize);

	// ABOR <CRLF>
	PXPublic PXSize PXFTPCommandBuildAbort(char* const dataBuffer, const PXSize dataBufferSize);

	// DELE <SP> <pathname> <CRLF>
	PXPublic PXSize PXFTPCommandBuildDELE(const char* pathname, char* const dataBuffer, const PXSize dataBufferSize);

	// RMD <SP> <pathname> <CRLF>
	PXPublic PXSize PXFTPCommandBuildDirectoryRemove(const char* pathname, char* const dataBuffer, const PXSize dataBufferSize);

	// MKD <SP> <pathname> <CRLF>
	PXPublic PXSize PXFTPCommandBuildMKD(const char* pathname, char* const dataBuffer, const PXSize dataBufferSize);

	// PWD <CRLF>
	PXPublic PXSize PXFTPCommandBuildDirectoryPrint(char* const dataBuffer, const PXSize dataBufferSize);

	// LIST[<SP> <pathname>] <CRLF>
	PXPublic PXSize PXFTPCommandBuildDirectoryListAllFromCurrnet(char* const dataBuffer, const PXSize dataBufferSize);
	PXPublic PXSize PXFTPCommandBuildLIST(const char* pathname, char* const dataBuffer, const PXSize dataBufferSize);

	// NLST[<SP> <pathname>] <CRLF>
	PXPublic PXSize PXFTPCommandBuildNLST(const char* pathname, char* const dataBuffer, const PXSize dataBufferSize);

	// SITE <SP> <string> <CRLF>
	PXPublic PXSize PXFTPCommandBuildSITE(const char* text, char* const dataBuffer, const PXSize dataBufferSize);

	// SYST <CRLF>
	PXPublic PXSize PXFTPCommandBuildSYST(char* const dataBuffer, const PXSize dataBufferSize);

	// STAT[<SP> <pathname>] <CRLF>
	PXPublic PXSize PXFTPCommandBuildStat(const char* pathname, char* const dataBuffer, const PXSize dataBufferSize);

	// HELP[<SP> <string>] <CRLF>
	PXPublic PXSize PXFTPCommandBuildHelp(const char* helpString, char* const dataBuffer, const PXSize dataBufferSize);

	// NOOP <CRLF>
	PXPublic PXSize PXFTPCommandBuildNoOperation(char* const dataBuffer, const PXSize dataBufferSize);

#ifdef __cplusplus
}
#endif

#endif
