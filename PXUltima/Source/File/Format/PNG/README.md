# Portable Network Graphics (.PNG) [RFC 2083]
## Info
|||
|:-:|:-:|
| Compression | Lossless |
| Tranparency| ✔️ |
| Complexity | High |

## Structure
File starts with a signature, then **chunks** will follow for the rest of the file.<br>
Each chunk has a fixed syntax.

### PNG Signature (8 Bytes)
|||||||||
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
| 0x89| 'P'| 'N'| 'G'| '\r'| '\n'| 0x1A| '\n'|

### PNG Chunk (minimum 12 Bytes)
|Name|Length|Type| Description |
|:-:|:-:|:-:|:-:|
|Length|4  Bytes| unsigned int | The length of the "chunkData"<br>A length of 0 to 2^32 is valid. |
|Signature|4 Bytes | char[4] | 4 Letter ID, if a letter is big or smal is important!|
|Data|? Bytes|-| Content depends on info above |
|CRC| 4 Bytes | unsigned int | CRC check value |

## Important Chunks
### Image Header (IHDR) [13 Bytes]
Is always the first chunk to be expected. contains important information.
|Name|Length|Type| Description / Expected |
|:-:|:-:|:-:|:-:|
|Width|4 Byte|unsigned int| Width of Image in Pixels|
|Height|4 Byte|unsigned int| Height of Image in Pixels|
|Bit depth |1 Byte|unsigned char| 1,2,4,8,16|
|Color type|1 Byte|unsigned char<br>(enum)|0,2,3,4,6|
|Compression method|1 Byte|unsigned char<br>(enum)|0|
|Filter method|1 Byte|unsigned char<br>(enum)|0|
|Interlace method|1 Byte|unsigned char<br>(enum)|0=no interlace<br>1=Adam7 interlace|

### Palette (PLTE) 
### Image Data (IDAT)
>This chunk is chained in a big steam.<br>
>This contains the compressed data.

### Image End (IEND)
Should be at the end of every file, can still be missing as it's not regarded as a necessary.
> This chunk contains no data, the length is expected to be zero.

## Optional Chunks
### Background color (bKGD) 
### Chromaticity coordinates  (cHRM)  
### Digital signatures (dSIG)
### Exif metadata (eXIf)
### Gamma (gAMA)
### Histogram (hIST)
### ICC color (iCCP)
### encodings profile hint (iTXt)
### Pixel aspect ratio (pHYs)
### significant bits (sBIT)
### Suggested Palette (sPLT)
### Standard sRGB color space indicator (sRGB)
### Stereoscopic image indicator (sTER)
### Plain Text (tEXt)
### "last changed" time (tIME)
### Transparency information (tRNS)
### Compressed text (zTXt)

