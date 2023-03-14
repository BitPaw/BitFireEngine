# Executable and Linkable Format (ELF)

## Info
UNIX general executable format.<br>
It is like a Windows EXE and DLL mixed together.

### Extensions
- .elf
- .so
- .o
- .out

## Structure
### Header
#### Signature - 4 Bytes

|||||
|:-:|:-:|:-:|:-:|
|0x7F|E|L|F|

#### Info - (32-Bit : 30 Bytes / 64-Bit : 60 Bytes)

|Name|Size|Type|Description|
|:-:|:-:|:-:|:-|
|Bit Format|1 Byte|unsigned char<br>(enum)|1 = 32-Bit<br>2 = 64-Bit|
|Endianness|1 Byte|unsigned char<br>(enum)|1 = little endian<br>2 = big endian|
|Version|1 Byte|unsigned char<br>(enum)| 1 = original and current version of ELF|
|Application binary<br>interface type|1 Byte|unsigned char<br>(enum)| ... |
|Application binary<br>interface version|1 Byte|unsigned char<br>(enum)| ... |
|** Padding **|7 Bytes| - | Unused, fill with 0x00|
|Type|2 Bytes|unsigned short<br>(enum)| ... |
|Machine|2 Bytes|unsigned short<br>(enum)| ... |
|Version|4 Bytes|unsigned int<br>(enum)| 1 = original version of ELF |
|Entry Point|32-Bit = 4 Bytes<br>64-Bit = 8 Bytes|void*| Address of the entry point from where the process starts executing|
|Program Header<br>Table Offset|32-Bit = 4 Bytes<br>64-Bit = 8 Bytes|void*| start of the program header table<br>Often to expect 32-bit:0x34 or 64-Bit:0x40|
|Section Header<br>Table Offset|32-Bit = 4 Bytes<br>64-Bit = 8 Bytes|void*| Points to the start of the section header table|
|Flags|4 Bytes|xxxxxxxxxxxxxx| Interpretation of this field depends on the target architecture. 
|ehsize|2 Bytes|xxxxxxxxxxxxxx| Size of this header, normally 64 Bytes for 64-bit and 52 Bytes for 32-bit format |
|phentsize|2 Bytes|xxxxxxxxxxxxxx| Size of a program header table entry |
|phnum|2 Bytes|xxxxxxxxxxxxxx| Number of entries in the program header table|
|shentsize|2 Bytes|xxxxxxxxxxxxxx| Size of a section header table entry |
|shnum|2 Bytes|xxxxxxxxxxxxxx| Number of entries in the section header table |
|shstrndx|2 Bytes|xxxxxxxxxxxxxx| Index of the section header table entry that contains the section names|
|** End of header **|x Bytes|xxxxxxxxxxxxxx| xxxxxxxxxxxxxx |

## Links
- https://en.wikipedia.org/wiki/Executable_and_Linkable_Format
