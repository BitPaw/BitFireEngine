# Kaydara Film Box (FBX)

## Info
|||
|:-:|:-:|
|Type| 🧊 3D model format |
|Documentation| :x: No (proprietary) |
|Format| Text and Binary|

Developed by Kaydara for MotionBuilder, bought up by Autodesk Inc in 2006.<br>
The format is hidden behind a SDK. 

### Dependency
- ZLIB

## Structure - Binary file
### Header [27 bytes]

|Size|Type|Name|Expected|
|:-:|:-:|:-:|:-:|
|21 Bytes|char[]|Signature|"Kaydara FBX Binary"<br>ending with 2 spaces + NULL terminator|
|2 Bytes|unsiged short| Magic number? | [0x1A, 0x00] |
|4 Bytes|unsigned int |Version Number|7300 for version 7.3 for example |

### Node Record

 |Size (Bytes)| Data Type| Name|
 |:-:|:-:|:-:|
 |4|unsigned int|EndOffset|
 |4|unsigned int|NumProperties|
 |4|unsigned int|PropertyListLength|
 |1|unsigned char|NameLength|
 |NameLength|char[]|Name|
 |?| 	?| 	Property[n], for n in 0:PropertyListLen|
 |Optional| 		
 |?| 	?| 	NestedList|
 |13| char[] | 	NULL-record|
 
 ### Property Record Format
 |Size (Bytes)| Data Type| Name|
 |:-:|:-:|:-:|
 |1| unsigned char<br>(enum)|TypeID|
 |?|?|Data|
 
 |ID|Datablock size|Type|
|:-:|:-:|:-:|
|Y|2 byte|int|
|C|1 bit|bool|
|I|4 byte|int|
|F|4 byte|float|
|D|8 byte|double|
|L|8 byte|int|
|f|Array of 4 byte|float|
|d|Array of 8 byte|double|
|l|Array of 8 byte|int|
|i|Array of 4 byte|int|
|b|Array of 1 byte|bool|
|S|???|string| 
|R|???|raw binary data| 

<p>

#### if "TypeID" is a type
> Interpred data as the type. 

#### If "TypeID" is an array
|Size (Bytes) |	Data Type |	Name|
|:-:|:-:|:-:|
|4|unsigned int|ArrayLength|
|4|unsigned int|Encoding|
|4|unsigned int|CompressedLength|
|?|?|Contents|

#### if "TypeID" is "string" or "raw binary data"
|Size (Bytes)|Data Type|Name|
|:-:|:-:|:-:|
|4|Uint32|Length|
|Length|byte/char|Data|
  
  </p>

## Structure - Text-Based File
...ToDo...

## Links
- https://docs.fileformat.com/3d/fbx/
- https://code.blender.org/2013/08/fbx-binary-file-format-specification
