# Joint Photographic Experts Group (JPEG)<br>[ISO/IEC 10918]
## Info
|||
|:-:|:-:
|Common file extension| jpg<br>jpeg<br>jpe<br>jif<br>jfif<br>jfi|
|Compression| Lossy |
|Transparency| :x:|
|Complexity| High|

## Structure
<p>
The file is structured into chunks.<br>
Each chunk has in identifier the size of 2 Bytes.<br>
The first Byte will always be 0xFF, the secound decides what chunk will follow.<br>
Each chunk, besides the beginning and end chunk, have a length (2 Bytes) directly after the identifier.
</p>


## Chunks
