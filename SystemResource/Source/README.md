# System Resource
## Stuff 
***

# Programming tricks & mecanics
|What|Why|Alternative|
|:-:|:-:|:-:|
|Do not use std:: |Those librarys are okey, you can use them if you want to but they are not written to be efficient or good to use.|Just implement your own version if possible or just write differently.<br>Often there is not need for special stuff like std::string.|
|Remember ownership of variables|Each object (class) should be required to clean up by itself|Prevent memory leaks and make them easy to find.| 
|Avoid allocations at all cost<br>(malloc / new)| These operations are very slow<br> and only needed, if the data will exist for a longer while.|Instand of allocation on the HEAP, stay on the STACK.<br>:x: int* array = new int[1000]<br>✔️int array[1000]|
|Use your virtual memory|Every programm has it's own virtual memory.<br>Pageing gets handled by the operating system.|Instead of reading a file compleatly into a buffer or just a smal line, instead map the file directly into virtual memory and use it directly.|
