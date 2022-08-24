# ZLIB [RFC 1950]

## Info
ZLIB is a structure to aid compression formats.<br>
Currently the only format specified is DEFLATE, thus this is just a code husk for that format. 

## Structure

### Dependency
- ADLER32
- DEFLATE

### Compression Method and flags block (minimum 6 Bytes)
|Name|Length|Type| Description |
|:-:|:-:|:-:|:-:|
|Compression method |4  Bits| enum | 8 = deflate compression<br> 15 = Reserved|
|Compression info |4 Bits | unsigned char | Values above 7 are not allowed |
|Checksum | 5 Bit| unsigned short| - |
|Has Dictionary| 1 Bit | bool | - |
|Compression Level| 2 Bits | enum | 0 = fastest <br>1 = fast <br>2 = default <br>3 = slowest  |
| Compressed Data| x Byte | - | Content depends on 'Compression method' |
| Checksum - ADLER32  | 4 Bytes | unsigned int | - |
