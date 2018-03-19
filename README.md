# ExtractPatches
A simple C++ utility to automatically extract color and grayscale patches. Initiated for pairwise and unpaired colorization tasks.

## What you should do
- Create a data folder containing the images you would like to use (i.e. 1 folder for color images, 1 folder for grayscale images)
- Update the global variables in headers/globalvar.hpp according to your needs
- Update paths variables in main.cpp according to your data folder
- Modify CMakeList to link the repository to your OpenCV dlls (bottom of CMakeList.txt)
- Generate the project with CMake
- Compile the project with your favorite compiler
- Enjoy your patches

## Requirements
- Windows system (tested on Windows 10)
- OpenCV (>= 3.3)
- CMake (>= 2.8)

## To Do
- Save patches according to the path used to find the data
- Add an easy to use CLI
- Add a choice for extacting only color patches instead of [color + calculated grayscale versions]
- Simplify usage
