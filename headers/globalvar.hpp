#pragma once

#include "headers.hpp"

int UNSET_INT = -1;
int GRANULARITY_DEFAULT = 30;
int STEP_DIV = 1;
int STEP_ = GRANULARITY_DEFAULT / STEP_DIV;
double OVERLAP_ = 100-(STEP_ / GRANULARITY_DEFAULT) * 100;
bool GRAY_DATA = false;
bool COLOR_DATA = false;
bool GRAY_WITHCOLORGT_DATA = true;

enum ExtractWithGTModes 
{
    CentralPixel = 0, //only the central pixel of the ground truth patch encodes the class
    AllPixel = 1 //all the pixels of the ground truth patch encode the class (i.e. they should all have the same value to consider the patch)
};

void updateOverlap(int step, int granularity)
{
    OVERLAP_ = 100 - (step / granularity) * 100;
}