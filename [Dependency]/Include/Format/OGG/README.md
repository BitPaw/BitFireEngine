# OGG File (.ogg)

## Structure
### OGG Page (27 Bytes + Segments)
|Offset|Size|Type|Name|Expected content|
|:-:|:-:|:-:|:-:|:-:|
|0|4|char[4]| Signature | 'Oggs'|
|4|1|unsigned char| Version | 0|
|5|1|unsigned char| Header type| Bit 0x01 set => Continuation of stream<br>Bit 0x02 set => Beginning of stream<br>Bit 0x04 set => End of stream |
|6|8|unsigned long long| Granule position| determined by the codec |
|14|4|unsigned int| Bitstream serial number| determined by the codec |
|18|4|unsigned int| Page sequence number| ID starting from 0, incrmented by each page |
|22|4|unsigned int| Checksum | CRC32 Value |
|23|1|unsigned char| Number of page segments| 0-255|

Loop the number of segments times and read a following element.<br>
Each number shall be stored and read after this loop.
|Size|Type|Name|Expected content|
|:-:|:-:|:-:|:-:|
| 1 |unsigned char| Length of segment | 0-255 |

Loop though the array above and use the value you've read, use it as length.<br>
On this resulting adress a different stream begins.
***
