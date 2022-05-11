# Dependencies (.LIB / .DLL / .so)

## Install (for Linux)
### OpenGL and OpenGL Extension Library
sudo apt-get install -y libglu1-mesa-dev freeglut3-dev mesa-common-dev  libglew-dev

## Cross Platform
| Library | Purpose | State | Reason "to use or not to use.." |
|:--:|:--:|:--:|:--:|
| OpenGL<br> (Open Graphics Library) | Graphics API to be able to render models & stuff | :heavy_check_mark:<br>In-use | Mainly used in graphics cards since forever. Is nearly in every OS. |
| GLFW <br> (OpenGL for Window)| Window creation and OpenGL context creation for multible operating systems, then binding to created window.<br>Has only one header file. | ❗<br>rewritten | Code is nearly a redirect, so it does not really add functionallity. It doesn't really reduce code and you loose alot of control of what each OS can really do.  |
| GLUT<br>OpenGL Utility Toolkit | Manage Window creation, input handling and a hand full of events like a window main loop. |:x:<br>never used | Considered undesirable, because it is too restricting if you want to have controll. |
|stb<br>| Load & Save Images | :x:<br>never used |  Many formats can be loaded but not saved.<br>It will not be feature-updated anymore because of "security" reasons, in the sence of it makes the library more vulnerable, more to test and harder to keep secure. |
| SOIL<br>(Simple OpenGL Image Library) | Load & Save images and combine OpenGL image registration into one | :x:<br>never used | It uses underlying library "stb_image". It doesn't really add any functionality. |
| GLM <br> (OpenGL Math) | Math calculations needed for object transformation & positioning <br> Library is header only (Just .hpp files)| ❗<br>rewritten | The whole library is very heavy, the compile time is very long. You most likely just need a Matrix4x4, a Vector3. Thus nearly the whole library will be unused. |
| SDL <br> (Simple DirectMedia Layer)| Access to Audio, Keyboard & Controller and Rendering with OpenGL | :x:<br>never used |
| OpenAL<br> (Open Audio Library) | Async audio Interface <br> Syntax useable like OpenGL| :x: removed | Library written in C++ but classes aren't even used.<br>It's C code with C++ std:: elements<br>Code is nested heavily in itself. |
| libpng | Load & Save a PNG file | ❗<br>rewritten | Code is scattered heavily.<br>Function call depth reaches very high amounts without doing anything.  |

### Windows Only
| Library | Purpose | 
|:-:|:-:|
| WINMM.DLL<br>(Windows Multi Media) | Sound (WAVE only) <br>Controller I/O<br>MIDI devices| 

### Linux Only
| Library | Purpose | 
|:-:|:-:|
|||
