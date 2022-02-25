# BitFireEngine
## Systems

| OS | x86 | x64 | 
|:--:|:--:|:--:|
| Windows | :heavy_check_mark:  | :heavy_check_mark: |
| Linux | :heavy_check_mark: | :heavy_check_mark: |
| OSX |:x: | :x: |

## Dependencies (.LIB / .DLL / .so)
### Cross Platform
| Library | Used | Purpose |
|:--:|:--:|:--:|
| OpenGL<br> (Open Graphics Library) | API to be able to render | :heavy_check_mark: In-use |
| GLFW <br> (OpenGL for Window)| Window creation and OpenGL Context creation, then binding to created window.<br>Has only one header file. |:warning: soon removed <br><br> Alot of code for something thatmost operating systems already provides. It saves only a smal chunk of code. |
| GLUE | ??? |:x: never used |
| SOIL | ??? | :x: never used |
| GLM <br> (OpenGL Math) | Math calculations needed for object transformation & positioning <br> Library is header only (Just .hpp files)| ↪️ rewritten <br><br> The whole library is very heavy, the compile time is very long. You most likely just need a Matrix4x4, a Vector3 and a Vector4. |
| SDL <br> (Simple DirectMedia Layer)| Access to Audio, Keyboard & Controller and Rendering with OpenGL | :x: never used |
| OpenAL<br> (Open Audio Library) | Async audio Interface <br> Syntax useable like OpenGL| :x: removed <br><br> Library written in C++, classes aren't even used <br>Code is nested in itself. |
| libpng | Load&Save a PNG file | ↪️ rewritten <br><br> Code is scattered heavily.<br>Function call depth reaches very high amounts without doing anything.  |

### Windows Only
insert libs

### Linux Only
insert libs

### Current Minimal Systemrequirements 

|Hardware| Minimal requirement| Tested requirement |
|:-:|:-:|:-:|
|CPU| SSE2 support | Intel i3 3250-M | 
|RAM| 57 MB | 102 MB | 
|GPU| OpenGL v.1.2 | Intel HD 3000 | 
|Harddrive| atleast 500 KB | ... |


## Supported Formats
<table>
<tr>
  <th>Image</th>
  <th>Objekt</th>
  <th>Sound</th>
  <th>Video</th>
</tr> 
  
 </td><td valign="top">
  
| Format | Supported |
|:--:|:--:|
| BMP | :heavy_check_mark: | 
| GIF | :x: |
| PNG | :heavy_check_mark:|
| JPEG | :warning: |
| TGA | :heavy_check_mark: |
| TIFF | :x: |
    
 </td><td valign="top">

| Format | Supported |
|:--:|:--:|
| 3DS | :x: |
| FBX | :x: |
| OBJ | :heavy_check_mark: | 
| PLY | :x: |
| STL | :x: |
| WRL | :x: |

 </td><td valign="top">
 
| Format | Supported |
|:--:|:--:|
| AAC | :x: |
| FLAC | :x: |
| MID | :warning: |
| MP3 | :x: |
| OGG | :x: |
| WAV | :heavy_check_mark: |
| WMA | :x: |
  
</td><td valign="top">
  
| Format | Supported |
|:--:|:--:|
| AVI | :x: |
| MP4 | :x: |
  </td>
 </table>
 
## Images
### Test-Project: Cleaved
![Image](_Images/Cleaved.png)

### Test-Project: Dust
![Image](_Images/Dust.png)


## Bugs
- Yes

## ToDo
- Physics Engine - Collision
 
## Ideas
- Non-Euclidian Space


# Trivia
## Q&A

|Question|My Answer|
|:-|:-|
| A new Engine?<br> Why do you even bother?<br> There are enough of them already. |  Yes.. I know.. <br>There are so many of them and all of their ups and downs. |
| Why don't you use GameMaker, Unity or Unreal?   | I've used Unity a lot and will use it again sometime.<br>Sadly, Unity is very frustrating to use. Even tho it exists for so long, it's lacking in so many regions.<br> It has a lot of features, jet it still feels like everything is a BETA Version and requires hours of work just to figure out how it works. Then I learn quickly, that this feature is too limited, then I have to spend more time re-doing it another way.<br> Why shouldn't I just do it correctly the first time?<br><br> My Point here is: Big Engines have poorly developed base features. You are required to make your own stuff. Small Engines on the other hand don't even have them or they are also poorly developed, for other reasons of course. |
| What is it then, that makes your Engine better than others? | I'll write this Engine as powerful as I can and it shall be very lightweight. It shouldn't be another clone of Unity or something alike. I want to create something very straight forward, something everyone can use and most importantly, to not hinder someone to take 100% advantage of every ounce of Hardware-Juice there is. |
| How do you think you will accomplish 'doing better' then professionals?<br> Sure they'll know what they do! | They know what they do, of course.<br><br> BUT.. if you take a look and go through Code-Histoy, you'll find that there are a lot of highly skilled people who are gods in their field but write horrible code. HR-People who will push you to solve solutions as fast as possible no matter the quality. Even good coders, they may write code with slight structural mistakes that scale horrible.<br><br>I'll go through hell and back to create everything myself. I need to plan a lot and had to rewrite the whole system several times already. I am learning here too!<br>If I manage to combine everything under one library, that is well-performing and error prove, this Engine will be legendary.. maybe. |
| WHAT?!<br> Did you mean, you write everything yourself?<br> Even libraries  that are used time and time again? | YES! Exactly! <br> It is in a way stupid, a waste of time. BUT as I said, I have my reasons.<br><br>Did you ever see some of those 'well established' libraries? Hahaha... <br>They are the worst spaghetti-coding-clusterfucks I've seen i some time. They work.. yes. Are they understandable? Maybe. But does that mean good? Or even fast or slow? Hard to tell. |
| If you do 'everything' what do you have in mind? | Well.. 'everything' sure is a very vague.<br>I mean by that, that i will add support for all sorts of formats. From music and video to images and models, maybe even more? So that you could juggle with all types, no matter common or uncommon, why not every type? We have time enough, don't we? |
| Sounds like a lot of work | It's a lot of work.. Yes... : ^)<br>It's hard to stay motivated. |
| Do you have someone to help you? | Not really, a one man army. <br>I do have a lot of 'sometime i'll do something' helpers tho.. heh.. |

### Details

The code is written in a way that you could remove some systems and use your own. Even Engine itself. 
(Ofcorse.. there are limitations)

