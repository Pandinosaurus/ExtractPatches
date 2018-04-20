/* getpatchesaloneinsubfolders.hpp
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
#include "iscolor.hpp"

void getPatchesAloneInSubfolders(std::string imagesRootPath, std::string imagesType, std::string saveType = SAVE_TYPE)
{
    //Create folders to save the patches
    auto savePathGrayGray = "../data/outputGrayGray/gray_";
    CreateDirectory(savePathGrayGray, NULL);
    auto savePathColorColor = "../data/outputColorRGB/colorrgb_";
    CreateDirectory(savePathColorColor, NULL);
    auto savePathColorGray = "../data/outputColorGray/colorgray_";
    CreateDirectory(savePathColorGray, NULL);

    //Get images recursivly
    bool recursivly = true;
    std::vector<cv::String> imgPathsVec;
    cv::glob(imagesRootPath + "/*." + imagesType, imgPathsVec, recursivly);

    //Extract
    int imgNb = 0;
    for (auto imgPath : imgPathsVec)
    {
        std::cout << imgPath << std::endl;
        cv::Mat img = cv::imread(imgPath, CV_LOAD_IMAGE_COLOR);
        if (isColor(img))
        {
            std::cout << "Image in color" << std::endl;
            extractPatches(img, savePathColorColor, saveType, GRANULARITY_DEFAULT, imgNb, STEP_);
            if (!COLOR_DATA_ONLY) {
                cv::cvtColor(img, img, CV_BGR2GRAY);
                extractPatches(img, savePathColorGray, saveType, GRANULARITY_DEFAULT, imgNb, STEP_);
            }
        }
        else //image is in grayscale
        {
            std::cout << "Image not in color" << std::endl;
            extractPatches(img, savePathGrayGray, saveType, GRANULARITY_DEFAULT, imgNb);
        }
        img.release();
        imgNb++;
    }
}