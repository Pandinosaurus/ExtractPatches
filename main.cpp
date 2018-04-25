/* main.cpp
 * 
 * Author: Rémi Ratajczak
 * Email : remi.ratajczak@gmail.com
 * LICENSE : MIT
 *
*/

#include "headers/headers.hpp"
#include "functions/getpatchesfromgrayscaledata.hpp"
#include "functions/getpatchesfromcolordata.hpp"
#include "functions/getpatchesfromgrayscaleAndgtdata.hpp"
#include "functions/getpatchesaloneinsubfolders.hpp"

int main(int argc, char *argv[])
{
    if(GRAY_DATA) getPatchesFromGrayscaleData(grayscaleImagesPath, READ_TYPE);
    if(COLOR_DATA) getPatchesFromColorData(colorImagesPath, READ_TYPE);
    if(GRAY_WITHCOLORGT_DATA) getPatchesFromGrayscaleAndGTData(grayscaleImagesPath, READ_TYPE, colorGtPath, READ_TYPE);
    if(DETERMINE_TYPE_ALONE_SUBFOLDERS) getPatchesAloneInSubfolders(ImagesRootPath, READ_TYPE);

    return 0;
}
