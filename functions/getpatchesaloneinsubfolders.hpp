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
        if (img.rows > 3000 && img.cols > 3000)
        {
            cv::Mat roi = img(cv::Rect(1000, 1000, img.cols - 1000, img.rows - 1000)); //allocate & clone roi
            if (isColor(roi))
            {
                std::cout << "Image in color" << std::endl;
                extractPatches(roi, savePathColorColor, saveType, GRANULARITY_DEFAULT, imgNb, STEP_);
                cv::cvtColor(roi, roi, CV_BGR2GRAY);
                extractPatches(roi, savePathColorGray, saveType, GRANULARITY_DEFAULT, imgNb, STEP_);
            }
            else
            {
                std::cout << "Image not in color" << std::endl;
                extractPatches(roi, savePathGrayGray, saveType, GRANULARITY_DEFAULT, imgNb);
            }
            roi.release();
        }
        img.release();
        imgNb++;
    }
}