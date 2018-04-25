# ExtractPatches
A simple C++ utility to automatically extract color and grayscale patches. 

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

## Optional
 - A TSV writter for your files - it requires Python 3 with "csv", "os" and "argparse" packages

## To Do
- Add an easy to use CLI for the patch extractor
- Allow user to extract random patches
- Allow user to extract only 1 patch
- Allow user to extract from a given coordinate
- Allow user to extract to a given coordinate
- Allow user to extract multiscale patches (mutliscale)
- Allow user to extract a pyramid of patches (mutliresolution)
