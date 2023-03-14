# PXDictionary

## Purpose
This container is a quick lookup for a smal identifier (key) and a datablock (value).<br>
The goal is to find the key a fast as possible to fetch the matching value.

## Memory Layout
To store both elements together in a packed format, we put them together as a double block.<br>
Size of both elements should be flexible as it depends on OS-Bit version and maximal size what value would be most efficent.

| Element | Description |
|:-:|:-|
| Key | Unique identifier<br>Adress of object can be used, must then be casted to a number. |
| Value / Offset | Adress or raw oject data. If the stored datablock is the same size or<br>even smaler than the field size, there would be no point in saving it seperate. |


### Special usage
To utilize the memory to its fullest, we can store data packed and even store additional data inside the lookup data block.<br>
This result in 3 ways on how we can store key and value pairs.

| Store mode | Description | 
|:-:|:-|
|Paired|Store the value direct after the key, if we search for the key and find it, interpret the value as the given data object|
|Managed|Store key only. The detected key position is the same as the element position, which size is to big to store directly, so it can be stored somewhere else in the same type of structure as the key lookup.<br>This speeds up the process, as there is less data to fetch that will clutter up the cache.<br>Additionally, you can still make a fast and complex search on the data structure. |
|CPublical| Store key and an adress together. The adress points to a from the dictionary allocated space, where data is stored.<br>The PXDictionary is the owner of this adress, so its will release the memory after extraction. |
