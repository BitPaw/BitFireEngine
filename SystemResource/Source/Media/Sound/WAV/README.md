# WAVE File (.wav)

## Structure
### RIFF Header (12 Bytes)
|Offset|Size|Type|Name|Expected content|
|:-:|:-:|:-:|:-:|:-:|
|0|4|char[4]| Header Signature | 'RIFF'|
|4|4|unsigned int| Following data size |FileSize - 8|
|8|4|char[4]|WAVE Signature|'WAVE'|
***
### FMT Header (24 Bytes)
|Offset|Size|Type|Name|Expected content|
|:-:|:-:|:-:|:-:|:-:|
|12|4|char[4]       | Header signature|'fmt '|
|16|4|unsigned int  | Size of header| 16 (Bytes)|
|20|2|unsigned short<br>enum| Format| ... |
|22|2|unsigned short| Channels      |1=Mono<br>2=Stereo<br>...|
|24|4|unsigned int | Samplerate    |-|
|28|4|unsigned int  | Bytes/second|-|
|32|2|unsigned short| Block allign|-|
|34|2|unsigned short| bits/sample|-|
***

### WAVE Data
|Offset|Size|Type|Name|Expected content|
|:-:|:-:|:-:|:-:|:-:|
| 36 | 4                        | char[4]      | Header signature| 'data'                 |
| 40 | 4                        | unsigned int | Size            | Maximal = FileSize - 44|
| 44 | From FMT<br>Block allign | Byte[]       | DataBlock 1     | Musicdata Bytes      |
| ?? | From FMT<br>Block allign | Byte[]       | DataBlock 2     | Musicdata Bytes       |
| ?? |...|...|...|...|

> Repeat until finished.
***
