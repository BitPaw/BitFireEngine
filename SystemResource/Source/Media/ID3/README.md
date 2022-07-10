# ID3
## Structure
***
### Version 1.0 (ID3v1) (128 Bytes) [obsolete]
|Offset|Size|Type|Name|Expected content|
|:-:|:-:|:-:|:-:|:-:|
|0| 3 Byte__ | char[3] | Signature | 'ID3' |
|3| 30 Byte__ |  char[30] | Title | Text |
|33| 30 Byte__ |  char[30] | Artist | Text |
|63| 30 Byte__ |  char[30] | Album | Text |
|93| 4 Byte__ |  char[4] | Release year | Text |
|97| 30 Byte__ |  char[30] | Comment | Text |
|127| 1 Byte__ | unsigned char<br>(enum) | Genre | ... |

***
### Version 1.1 (ID3v1.1) (128 Bytes) [obsolete]
>Changes from 1.0
>> Comment is 2 Bytes less long.<br>
>> Force first Byte__ to be 0x00 to terminate the string<br>
>> Use the secound Byte__ for a title number<br>

|Offset|Size|Type|Name|Expected content|
|:-:|:-:|:-:|:-:|:-:|
|0| 3 Byte__ | char[3] | Signature | 'ID3' |
|3| 30 Byte__ |  char[30] | Title | Text |
|33| 30 Byte__ |  char[30] | Artist | Text |
|63| 30 Byte__ |  char[30] | Album | Text |
|93| 4 Byte__ |  char[4] | Release year | Text |
|97| 30 Byte__ |  char[28] | Comment | Text |
|125| 1 Byte__ | unsigned char | Null Byte__ | 0x00 |
|126| 1 Byte__ | unsigned char | Title Number | 0-255 |
|127| 1 Byte__ | unsigned char<br>(enum) | Genre | ... |

***
### Version 2.0 (ID3v2) [obsolete]
>Changes from 1.1
>> Added additonal version, flag and size after header signature<br>
>> Added frames to hold more information and even custom data.<br>

#### Header
|Offset|Size|Type|Name|Expected content|
|:-:|:-:|:-:|:-:|:-:|
|0| 3 Byte__ | char[3] | Signature | 'ID3' |
|3| 2 Byte__ |  char[2] | Version | Text |
|5| 1 Byte__ |  unsigned char | Flags | ... |
|6| 4 Byte__ |  char[2] | Size | 0-256MB |
...

##### Flags
Bit 7 "unsynchronisation"<br>
Bit 6 "uses compression"<br>

##### Size
In the size field, every first bit (Bit 7) is set to be zero.<br>
The creator wanted to make the maximal 'guaranteed' possible file size to be 256MB.<br> 
As this shall be considered to be the maximum size for this ID3 tag.

#### Frame
|Offset|Size|Type|Name|Expected content|
|:-:|:-:|:-:|:-:|:-:|
|0| 3 Byte__ |  char[3] | Identifier  | ... |
|3| 3 Byte__ |  unsigned int | Size | Number |





***
### Version 2.2 (ID3v2.2) [obsolete]

***
### Version 2.3 (ID3v2.3) [most supported version]
> Changes from 2.2
>> Flag 'uses compression' is now  'has Extended header'<br>
>> Added flag 'Experimental'<br>
>> FrameID size increased from 3 Bytes to 4 Bytes<br>

#### Extended Header
|Offset|Size|Type|Name|Expected content|
|:-:|:-:|:-:|:-:|:-:|
|0| 4 Byte__ |  unsigned int | Size  | Number |
|4| 2 Byte__ |  unsigned short | Flags  | ... |
|6| 4 Byte__ |  unsigned int | Padding  | Number |

#### Frame
|Offset|Size|Type|Name|Expected content|
|:-:|:-:|:-:|:-:|:-:|
|0| 4 Byte__ |  char[4] | ID  | A-Z and 0-9 |
|4| 4 Byte__ |  unsigned int | Size  | Number |
|6| 2 Byte__ |  unsigned short | Flags  | ... |

##### Frame Types

***
### Version 2.4 (ID3v2.4) [device may not fully support]
> Chnanged from 2.3
>> Added footer chunk<br>
>> Added flag 'footer'<br>
>> Changed Extended header

#### Footer chunk
A copy of the header chunks but on the end of the file.<br>
To speedup lookuptime, if you read the file bottom up.<br>
Only difference is the identifier, its in reverse.
> Here its now "3DI" not "ID3" as in the header
***
