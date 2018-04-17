#include "headers/headers.hpp"
#include "functions/getpatchesfromgrayscaledata.hpp"
#include "functions/getpatchesfromcolordata.hpp"
#include "functions/getpatchesfromgrayscaleAndgtdata.hpp"
#include "functions/getpatchesaloneinsubfolders.hpp"

int main(int argc, char *argv[])
{
    std::string imagesType = "jpg";
    std::string colorImagesPath = "../data/inputColor/";
    std::string grayscaleImagesPath = "../data/inputGray/";
    std::string colorGtPath = "../data/inputColorGt/";
    std::string ImagesRootPath = "../../../datasets/";

	if(GRAY_DATA) getPatchesFromGrayscaleData(grayscaleImagesPath, imagesType);
	if(COLOR_DATA) getPatchesFromColorData(colorImagesPath, imagesType);
    if(GRAY_WITHCOLORGT_DATA) getPatchesFromGrayscaleAndGTData(grayscaleImagesPath, imagesType, colorGtPath, imagesType);
    if(DETERMINE_TYPE_ALONE) getPatchesAloneInSubfolders(ImagesRootPath, imagesType);

    return 0;
}