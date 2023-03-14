# Material (.mtl)<br>

## Info
|||
|:-:|:-:|
|Format|Text|

Contains data about visual aspects and textures. Used in OBJ-Model files.

## Structure
> Lines beginning with an '#' are regarded as a comment and should be ignored.

|ID|Parameter 1|Parameter 2|Parameter 3|Parameter 4| Description|
|:-:|:-:|:-:|:-:|:-:|:-:|
|newmtl| NameOfMaterial | | ||Declare Material|
|Ns| Value (float)| | | |Weight|
|Ka| Red (float)| Green (float)| Blue (float)||Ambient|
|Kd| Red (float)| Green (float)| Blue (float)||Diffuse|
|Ks| Red (float)| Green (float)| Blue (float)||Specular|
|Ke| Red (float)| Green (float)| Blue (float)||Emission|
|Tf  |Red (float)| Green (float)| Blue (float)||???|
|Ni| Value (float)| | ||Dissolved|
|d| Value (float)| | ||Density|
|sharpness  | Value (unsigned char) | | ||???|
|illum| Value (enum) | | ||Illumination|
|map_Ka | | | ||???|
|map_Kd | | | ||???|
|map_Ks | | | ||???|
|map_Ns | | | ||???|
|map_d | | | ||???|
|decal  | | | ||???|
|bump  | | | ||???|
|refl  | | | ||???|



|Illumination Model | Color | Ambient | Highlight | Reflextion | Ray trace | Description |
|-:|:-:|:-:|:-:|:-:|:-:| :-|
|0| ✔️ | :x:|:x:|:x:|:x:|Color on and Ambient off|
|1|✔️ | ✔️ |:x:|:x:|:x:|Color on and Ambient on|
|2|:x: | :x:| ✔️|:x:|:x:|Highlight on|
|3|:x:| :x:|:x:|✔️|✔️|Reflection on and Ray trace on|
|4|:x:| :x:|:x:|:x:|✔️|Transparency: Glass on and<br>Reflection: Ray trace on|
|5|:x:| :x:|:x:|✔️|:x:|Reflection: Fresnel on and<br>Ray trace on|
|6|:x:| :x:|:x:|:x:|✔️|Transparency: Refraction on and<br>Reflection: Fresnel off and Ray trace on|
|7|:x:| :x:|:x:|✔️|✔️|Transparency: Refraction on and<br>Reflection: Fresnel on and Ray trace on|
|8|:x:| :x:|:x:|✔️|:x:|Reflection on and Ray trace off|
|9|:x: |:x:| :x:|:x:|:x:|Transparency: Glass on and<br>Reflection: Ray trace off|
|10|:x: |:x:| :x:|:x:|:x:|Casts shadows onto invisible surfaces|


