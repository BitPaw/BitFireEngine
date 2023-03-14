# Memory

## Functions

### Memory Clear
Set a given range to a zero byte.

### Memory Set
Set a given range to a specified byte.

### Memory Compare
Compares a given range of bytes.

### Memory Copy
Copys a given range of bytes into another.<br>
Note, this function will corrupt the data if the buffers overlap.<br>
If you use uverlapping buffers or copying in the same buffer, use the MemoryMove() function.

### Memory Move
Copys a given range of bytes into another while working like you'd coped them into a temporal buffer first.

## Virtual Memory
Many operating systems noticed problems using direct physical memory adressing.<bs>
A solution was, to create a virtal memory space for each process, so that other processes interfeere less with our own memory space.<br>
Additionally, we got the bonus that shared memory mostly of librarys can reduce physical memory usage by alot.