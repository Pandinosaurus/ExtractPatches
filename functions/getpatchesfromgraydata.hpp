#pragma once

#include "../headers/headers.hpp"
#include "../headers/globalvar.hpp"
#include "extractpatches.hpp"

void getPatchesFromGrayscaleData(std::string grayscaleImagesPath, std::string imagesType)
{
    //Get directory
    auto savePathTestGray = "../data/outputGrayGray/";
    CreateDirectory(savePathTestGray, NULL);

    //Get images
    std::vector<cv::String> imgPathsVec;
    cv::glob(grayscaleImagesPath + "*." + imagesType, imgPathsVec, false);

    //Extract
    int imgNb = 0;
    for (auto imgPath : imgPathsVec)
    {
        std::cout << imgPath << std::endl;
        cv::Mat imgTestGray = cv::imread(imgPath, 0);
        extractPatches(imgTestGray, savePathTestGray, imagesType, GRANULARITY_DEFAULT, imgNb);
        imgTestGray.release();
    }
}