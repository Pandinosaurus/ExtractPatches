#pragma once

#include "../headers/headers.hpp"
#include "../headers/globalvar.hpp"
#include "extractpatches.hpp"

void getPatchesFromGrayscaleAndGTData(std::string grayscaleImagesPath, std::string grayscaleImagesType,
                                 std::string groundTruthImagesPath, std::string groundTruthImagesType)
{
    //Get directories
    auto savePathGray = "../data/outputGrayGTGray/";
    auto savePathGT = "../data/outputGrayGTGT/";

    //Get images
    std::vector<cv::String> imgGrayPathsVec;
    cv::glob(grayscaleImagesPath + "*." + grayscaleImagesType, imgGrayPathsVec, false);
    std::vector<cv::String> imgGTPathsVec;
    cv::glob(groundTruthImagesPath + "*." + groundTruthImagesType, imgGTPathsVec, false);

    //Check
    if (imgGrayPathsVec.size() != imgGTPathsVec.size()) 
    {
        std::cerr << "Not same number of grayscale images an GT images in getPatchesFromGrayscaleAndGTdata()" 
                  << std::endl;
        return;
    }

    //Extract
    int maxImgNb = imgGrayPathsVec.size();
    for(auto imgNb = 0; imgNb < maxImgNb; imgNb++)
    {
        cv::Mat imgGray = cv::imread(imgGrayPathsVec[imgNb], 0);
        cv::Mat imgGT = cv::imread(imgGTPathsVec[imgNb], 1); //in color
        extractPatchesWithGT(imgGray, savePathGray, grayscaleImagesType,
                             imgGT, savePathGT, groundTruthImagesType,
                             ExtractWithGTModes::AllPixel,
                             imgNb);
        imgGray.release();
        imgGT.release();
    }
}