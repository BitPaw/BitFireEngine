# File Transfer Protocol (FTP)<br>[RFC 959]

## Reponse codes
|ID|Discription|
|:-:|:-|
|110|Restart marker reply|
| 120 | Service ready in nnn minutes|
| 125 | Data connection already open; transfer starting|
| 150 | File status okay; about to open data connection|
| 200 | Command okay|
| 202 | Command not implemented, superfluous at this site|
| 211 | System status, or system help reply|
| 212 | Directory status|
| 213 | File status|
| 214 | Help message|
| 215 | NAME system type|
| 220 | Service ready for new user|
| 221 | Service closing control connection|
| 225 | Data connection open; no transfer in progress|
| 226 | Closing data connection|
| 227 | Entering Passive Mode (h1,h2,h3,h4,p1,p2)|
| 230 | User logged in, proceed|
| 250 | Requested file action okay, completed|
| 257 | "PATHNAME" created|
| 331 | User name okay, need password|
| 332 | Need account for login|
| 350 | Requested file action pending further information|
|421|Service not available, closing control connection|
|425|Can’t open data connection|
|426|Connection closed; transfer aborted|
|450|Requested file action not taken|
|451|Requested action aborted. Local error in processing|
|452|Requested action not taken|
| 500 | Syntax error, command unrecognized|
| 501 | Syntax error in parameters or arguments|
| 502 | Command not implemented|
| 503 | Bad sequence of commands|
| 504 | Command not implemented for that parameter|
| 530 | Not logged in|
| 532 | Need account for storing files|
| 550 | Requested action not taken|
| 551 | Requested action aborted: page type unknown|
| 552 | Requested file action aborted|
| 553 | Requested action not taken|



## Commands

|Command|\<Space>|Parameter|\<CR>|\<LF>|
|:-:|:-:|:-:|:-:|:-:|
|xxx|\x20|xxx|\r|\n|


|Name|Command|Parameter|
|:-|:-:|:-:|
|User Name|USER|username|
|Password|PASS|password|
|Account|ACCT|account-information|
|Change working directory|CWD|pathname|
|Change to parent directory|CDUP|-|
|Structure mount|SMNT|pathname|
|Logout|QUIT|-|
|Reinitialize|REIN|-|
|Data port|PORT|host-port|
|Passive|PASV|-|
|Representation type|TYPE|type-code|
|File structure|STRU|structure-code|
|Transfer mode|MODE|mode-code|
|Retrieve|RETR|pathname|
|Store|STOR|pathname|
|Store unique|STOU|-|
|Append|APPE|pathname|
|Allocate|ALLO|decimal-integer|
|Restart|REST|marker|
|Rename from|RNFR|pathname|
|Rename to|RNTO|pathname|
|Abort|ABOR|-|
|Delete Element|DELE|pathname|
|Remove Directory|RMD|pathname|
|Make Directory|MKD|pathname|
|Print Working Directory|PWD|-|
|List Elements|LIST|[pathname]|
|Name List|NLST|[pathname] |
|Site parameters|SITE|string|
|System|SYST|-|
|Status|STAT|[pathname]|
|Help|HELP|[string]|
|No operation|NOOP|-|
