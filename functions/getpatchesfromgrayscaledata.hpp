#pragma once

#include "../headers/headers.hpp"
#include "../headers/globalvar.hpp"
#include "extractpatches.hpp"

void getPatchesFromGrayscaleData(std::string grayscaleImagesPath, std::string imagesType)
{
    //Get directory
    auto savePathGrayGray = "../data/outputGrayGray_bis/gray_";
    CreateDirectory(savePathGrayGray, NULL);

    //Get images
    std::vector<cv::String> imgPathsVec;
    cv::glob(grayscaleImagesPath + "*/*." + imagesType, imgPathsVec, false);

    //Extract
    int imgNb = 0;
    for (auto imgPath : imgPathsVec)
    {
        std::cout << imgPath << std::endl;
        cv::Mat imgGray = cv::imread(imgPath, 0);
        extractPatches(imgGray, savePathGrayGray, imagesType, GRANULARITY_DEFAULT, imgNb);
        imgGray.release();
        imgNb++;
    }
}
