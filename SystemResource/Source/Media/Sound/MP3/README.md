# MP3 File (.mp3)

## Structure
File <b>can</b> begin with a 'ID3' Chunk. It contains meta data.<br>
There are multible headers, after each header a data chunks follows.<br>
Header + Data chunks order is repeated trough the whole file.<br>

### MetaDataTag-Chunk
To find are either ID3v1 and ID3v2 or APEv2.
Encoders and decoders can ignore this chunk.<br>
As this is not a standard to the MP3 format itself, it can be ignored.

### MP3-Header-Chunk (4 Bytes)
Values stored in Big-Endian order.

|Offset|Size|Type|Name|Expected content|
|:-:|:-:|:-:|:-:|:-:|
|0| 12 Bits | unsigned short | Signature | ??? |
|1 Byte + 4 Bits | 1 Bit | bool   |Version| 1 = MPEG |
|1 Byte + 5 Bits|2 Bit| bool   |Layer| 1 = Layer 3 |
|1 Byte + 7 Bits|1 Bit| bool   |Error Protection| 1 = No |
|2 Byte + 0 Bits |4 Bit| unsigned char | Bitrate | 1010 = 160 |
|2 Byte + 4 Bits|2 Bits| unsigned char   |Frequency| 0 = 44100 Hz |
|2 Byte + 6 Bits|1 Bit| bool   |Padding Bit| 0 = Frame is not padded |
|2 Byte + 7 Bits|1 Bit| bool   |Prvate Bit| Unkown |
|3 Byte + 0 Bits|2 Bit| unsigned char   |Mode| 1 = Joint Stereo |
|3 Byte + 2 Bits|1 Bit| bool   |Mode Extension <br>(Used With Joint Stereo)| 0 = Intensity Stereo Off |
|3 Byte + 3 Bits|1 Bit| bool   |Mode Extension <br>(Used With Joint Stereo)| 0 = MS Stereo Off |
|3 Byte + 4 Bits|1 Bit| bool   |Copy| 0 = Not Copy-righted |
|3 Byte + 5 Bits|1 Bit| bool   |Original| 0 = Copy of original Media |
|3 Byte + 6 Bits|2 Bits| unsigned char   |Emphasis| 0 = None |
***

### MP3-Data-Chunk
