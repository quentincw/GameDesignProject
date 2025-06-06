**PREREQUISITES**

- GCC
- CMAKE (www.cmake.org)
- SDL 2.0 (www.libsdl.org)
- SDL2_image
- SDL2_gfx
- SDL2_ttf
- SDL2_mixer

**Linux**

Just install the packages above with your distributions package manager and
everything should work out of the box.  Only resort to compiling from source
if no suitable package exists.  Also, do not forget to install the 'devel'
package for SDL2.

Git clone the package from your fork. Enter the cloned directory, Make a subdir 
'Debug', and in 'Debug' type: 'cmake ..'.  This should generate the makefiles.  
Once succesfully generated, you can now compile the code with 'make'.

**Windows**

To make install easy, we will use MSYS2 and mingw64.

1) Install MSYS2: https://www.msys2.org/
2) Open the MSYS2 MINGW64 terminal (not the MSYS2 UCRT64 terminal)
2) Install mingw64:    pacman -S mingw-w64-x86_64-toolchain
3) Install cmake:      pacman -S mingw-w64-x86_64-cmake
4) Install git:        pacman -S git
5) Install SDL2:       pacman -S mingw-w64-x86_64-SDL2
6) Install SDL2 gfx:   pacman -S mingw-w64-x86_64-SDL2_gfx
7) Install SDL2 image: pacman -S mingw-w64-x86_64-SDL2_image
8) Install SDL2 ttf:   pacman -S mingw-w64-x86_64-SDL2_ttf
9) Install SDL2 ttf:   pacman -S mingw-w64-x86_64-SDL2_mixer
10) Optional: add <msys2 install path>/mingw64/bin to your path if you also want to be able to run your code by double clicking.  To add to your path, open "Edit environment variables" -> select Path -> Edit -> New -> Browse

We will use the MSYS2 MINGW64 terminal for **all** steps. To access your c:\ drive use:

cd /c/

Next, git clone the skeleton code to your location of choice (git clone https://code.wm.edu/<username>/CSCI437-Pong.git), and use cd /c/<path> to
enter the location in msys2.  If you get an error that git does not support 'https', then you probably copy-pasted an invisible character before
https; just delete all spaces between 'clone' and 'https', and re-add a new space; this will delete the invisible character.

1) Make the directory in which we will compile the pong skeleton code.  Inside
your pong source directory make a directory 'Debug'

mkdir Debug

2) Next, generate make files:

cd Debug
cmake.exe -G "MinGW Makefiles" ..

3) The above step should find a C++ compiler and the SDL2 libraries.  Next we
can compile the code:

mingw32-make.exe

4) We can now test the code:

./helloworld.exe

NOTE: it is possible that the helloworld window is hidden behind your console window.

***helloworld***

If the above worked without error, it should  produce a 'helloworld' executable that will open a blue
window.  You can change the color of pressing 'r', 'g', or 'b'.  You can quit
by pressing 'q'.

***bitmap***

The bitmap program, loads a bitmap (resource/bitmap.png).  You can module its
color with 'r', 'g', and 'b', and rotate it with 'z' and 'x'.

***text***

Loads a font (resource/Arial.ttf).  Same keys are 'bitmap'.

***geom***

Draws a box, a circle, and draws lines.  You can enable/disable each with 'b',
'c', and 'l' respectively.


**ADDING FILES**

- If you want to add an executable, just add the corresponding .cpp file in the 'bin' subdirectory, and _rerun_ 'cmake .' to update the Makefiles.
- If you want to add a source file, just add the corresponding .cpp file in the 'src' subdirectory, and _rerun_ 'cmake .' to update the Makefile.
- If you want to add a header file, just add the corresponding .h file to the 'include' subdirectory. You do not need to update the Makefile.


**ADVANCED COMPILING**

The above instructions will compile your executable with all debug information embedded and compiler optimizations minimized.  To compile a 'release' version, just create a subdirectory 'Release' instead of 'Debug' and follow the same instructions as above. Note: in release mode certain safety checks are disabled and 'assert' statement are ignored. Hence, it is recommended to test your code in 'Debug' mode, and only when everything works, compile it in the 'Release' mode.

If you want to use additional external libraries, you will need to add them to 'CMakeLists.txt' (line 48). Please refer to the CMake documentation for more information on how to include libraries to your project with CMake.

**HOW TO PLAY GAME**

Follow the compilation instructions above and then run ./killAlien in Release.