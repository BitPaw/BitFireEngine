# WAVE File (.wav)

## Structure
### RIFF Header (12 Bytes)
|Offset|Name|Type|Size in Bytes |Expected content|
|:-:|:-:|:-:|:-:|:-:|
|0|Hedaer Signature|char[4]| 4 | "RIFF"|
|4|Size|unsigned int |4 |Size-8|
|8|WAVE Signature|char[4]|4|"WAVE"|

### FMT Header (24 Bytes)
|Offset|Name|Type|Size in Bytes |Expected content|
|:-:|:-:|:-:|:-:|:-:|
|12|Header signature|char[4]|4|"fmt "|
|16|Size of header|unsigned int|4| 16 (Bytes)|
|20|Format|unsigned short<br>enum|2|* |
|22|Channels|unsigned short|2|1=Mono<br>2=Stereo<br>...|
|24|Samplerate|unsigned int|4|
|28|Bytes/second|unsigned int|4|
|32|Block allign|unsigned short|2|||
|34|bits/sample|unsigned short|2|||

### WAVE Data
|Offset|Name|Type|Size in Bytes |Expected content|
|:-:|:-:|:-:|:-:|:-:|
|36|Header signature|char[4]|4|"data"|
|40|Size|unsigned int|4|Maximal = FileSize - <br>(RIFF Header + FMT Header)<br>(12+24)<br>(44)|
|44|DataBlock 1|Byte[]|Known from before| Musicdata Bytes |
|??|DataBlock 2|Byte[]|Known from before|Musicdata Bytes|
|??|...|...|...|...|

Repeat until finished.
