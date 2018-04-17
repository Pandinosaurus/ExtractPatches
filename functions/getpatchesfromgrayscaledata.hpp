#pragma once

#include "../headers/headers.hpp"
#include "../headers/globalvar.hpp"
#include "extractpatches.hpp"

void getPatchesFromGrayscaleData(std::string grayscaleImagesPath, std::string imagesType)
{
    //Get directory
    auto savePathGray = "../data/outputGrayGray/";
    CreateDirectory(savePathGray, NULL);

    //Get images
    std::vector<cv::String> imgPathsVec;
    cv::glob(grayscaleImagesPath + "*/*." + imagesType, imgPathsVec, false);

    //Extract
    int imgNb = 0;
    for (auto imgPath : imgPathsVec)
    {
        std::cout << imgPath << std::endl;
        cv::Mat imgGray = cv::imread(imgPath, 0);
        extractPatches(imgGray, savePathGray, imagesType, GRANULARITY_DEFAULT, imgNb);
        imgGray.release();
        imgNb++;
    }
}