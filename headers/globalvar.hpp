/* globalvar.hpp
*
* Author: Rémi Ratajczak
* Email : remi.ratajczak@gmail.com
* LICENSE : MIT
*
*/

#pragma once

#include "headers.hpp"

int UNSET_INT = -1;
int GRANULARITY_DEFAULT = 512;
int STEP_DIV = 4;
int STEP_ = GRANULARITY_DEFAULT / STEP_DIV;
double OVERLAP_ = 100-(STEP_ / GRANULARITY_DEFAULT) * 100;
bool GRAY_DATA = false;
bool COLOR_DATA = true;
bool GRAY_WITHCOLORGT_DATA = false;
bool DETERMINE_TYPE_ALONE_SUBFOLDERS = false;
std::string SAVE_TYPE = "png";

enum ExtractWithGTModes 
{
    CentralPixel = 0, //only the central pixel of the ground truth patch encodes the class
    AllPixel = 1 //all the pixels of the ground truth patch encode the class (i.e. they should all have the same value to consider the patch)
};

void updateOverlap(int step, int granularity)
{
    OVERLAP_ = 100 - (step / granularity) * 100;
}