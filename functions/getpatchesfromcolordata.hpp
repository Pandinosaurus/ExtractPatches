/* getpatchesfromcolordata.hpp
*
* Author: Rémi Ratajczak
* Email : remi.ratajczak@gmail.com
* LICENSE : MIT
*
*/

#pragma once

#include "../headers/headers.hpp"
#include "../headers/globalvar.hpp"
#include "extractpatches.hpp"

void getPatchesFromColorData(std::string colorImagesPath, std::string imagesType)
{
    //Create folders to save the patches
    auto savePathColorColor = "../data/outputColorRGB_bis/colorrgb_";
    CreateDirectory(savePathColorColor, NULL);
    auto savePathColorGray = "../data/outputColorGray_bis/colorgray_";
    CreateDirectory(savePathColorGray, NULL);

    //Get all image paths in a folder
    std::vector<cv::String> imgPathsVec;
    cv::glob(colorImagesPath + "*." + imagesType, imgPathsVec, false);

    //For each path gathered, read the image in both in 
    //color and grayscale and extract pair patches from them
    int imgNb = 0;
    for (auto imgPath : imgPathsVec)
    {
        cv::Mat imgBgr = cv::imread(imgPath, CV_LOAD_IMAGE_COLOR);
        extractPatches(imgBgr, savePathColorColor, imagesType, GRANULARITY_DEFAULT, imgNb, STEP_);
        imgBgr.release();

        if (!COLOR_DATA_ONLY) {
            cv::Mat imgGray = cv::imread(imgPath, CV_LOAD_IMAGE_GRAYSCALE);
            extractPatches(imgGray, savePathColorGray, imagesType, GRANULARITY_DEFAULT, imgNb, STEP_);
            imgGray.release();
            imgNb++;
        }
    }
}