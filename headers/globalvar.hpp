#pragma once

#include "headers.hpp"

int UNSET_INT = -1;
int GRANULARITY_DEFAULT = 512;
int STEP_DIV = 1;
int STEP_ = GRANULARITY_DEFAULT / STEP_DIV;
bool GRAY_DATA = true;
bool COLOR_DATA = false;

enum ExtractWithGTModes 
{
    CentralPixel = 0, //only the central pixel of the ground truth patch encode the class
    AllPixel = 1 //all the pixels of the ground truth patch encode the class (i.e. they should all have the same value to be considered)
};