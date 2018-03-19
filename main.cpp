#include "headers/headers.hpp"
#include "functions/getpatchesfromgrayscaledata.hpp"
#include "functions/getpatchesfromcolordata.hpp"

int main(int argc, char *argv[])
{
    std::string imagesType = "jpg";
    std::string colorImagesPath = "../data/inputColor/";
    std::string grayscaleImagesPath = "../data/inputGray/";

	if(GRAY_DATA) getPatchesFromGrayscaleData(grayscaleImagesPath, imagesType);
	if(COLOR_DATA) getPatchesFromColorData(colorImagesPath, imagesType);

    return 0;
}