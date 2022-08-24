# BitMap (.BMP) [RFC 797]

## Info
Bitmaps is an image format.<br>
The format is easy to parse and serialize but as a drawback, it comsumes a considerable amount of space even for relative smal images.<br>
Even in the early days, other formats gained alot more popularity.<br>
Though, this format got some updates over time, most rely on mecanics that are copyed from other formates.<br>
Because of this history, bitmaps are used here and there but in the context of the internet, this format is absent.


## Structure
### Bitmap Header (14 Bytes)
|Name|Length|Type| Description |
|:-:|:-:|:-:|:-:|
|ID|2  Bytes| unsigned int | BM - Windows 3.1x, 95, NT, ... etc.<br>BA - OS/2 struct bitmap array<br>CI - OS/2 struct color icon<br>CP - OS/2 const color pointer<br>IC - OS/2 struct icon<br>PT - OS/2 pointer |
|Size of file|4 Bytes | unsigned int | Notice: as this is a 32-Bit number, the file can only around 4 GB |
|Reserved| 2 Bytes | unsigned short | usually 0 |
|Reserved| 2 Bytes | unsigned short | usually 0 |
|DataOffset| 4 Bytes | unsigned int | On this offset the pixeldata is stored |

### Bitmap DIP Header (minimum 12 Bytes to maximal 124 Bytes)
You read this header instandly after the main header.<br>
The first value directly decides what data follows.

|Name|Length|Type| Description |
|:-:|:-:|:-:|:-:|
|SizeOfHeader| 4 Bytes | unsigned int | - |

Then lets see what we get

#### OS/2 1.x BITMAPCOREHEADER (12 Byte)

#### OS22XBITMAPHEADER (16 Bytes) 

#### Windows BITMAPINFOHEADER (40 Bytes) [Most common version]

|Name|Length|Type| Description |
|:-:|:-:|:-:|:-:|
|Width|4 Bytes | int | - |
|Height|4 Bytes | int | - |
|Number of color planes |2 Bytes | unsigned short | must be 1  |
|Bits per Pixel |2 Bytes | unsigned short | Typical values are 1, 4, 8, 16, 24 and 32 |
|Compression method|4 Bytes | enum | - |
|Image size|4 Bytes | unsigned int | 0 can be given for BI_RGB bitmaps |
|horizontal resolution|4 Bytes | unsigned int | - |
| vertical resolution|4 Bytes | unsigned int | - |
|number of colors in the color palette|4 Bytes | unsigned int |  0 to default to 2^n |
|number of important colors used|4 Bytes | unsigned int | 0 when every color is important; generally ignored |


#### BITMAPV2INFOHEADER (52 Bytes)
ToDo

#### BITMAPV3INFOHEADER (56 Bytes)
ToDo

#### BITMAPV4HEADER (108 Bytes)
ToDo

#### BITMAPV5HEADER (124 Bytes)
ToDo



### Pixel data
The data is stored depending on the layout described in the header. <br>


