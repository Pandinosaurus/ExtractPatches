#pragma once

#include "../headers/headers.hpp"
#include "../headers/globalvar.hpp"

void extractPatches(cv::Mat img, std::string savePath, std::string imgType = "jpg", int granularity = GRANULARITY_DEFAULT, int imgNb = UNSET_INT, int step = UNSET_INT)
{
    CreateDirectory(savePath.c_str, NULL);

    if (step == UNSET_INT) step = granularity;
    for (int row = 0; row < img.rows - granularity; row += step)
    {
        for (int col = 0; col < img.cols - granularity; col += step)
        {
            std::string imNbstr = std::to_string(imgNb);
            std::string colstr = std::to_string(col);
            std::string rowstr = std::to_string(row);
            cv::Rect roi(col, row, granularity, granularity);
            cv::imwrite(savePath + 
                        imNbstr + "_" + rowstr + "x" + colstr + "." + imgType,
                        img(roi));
        }
    }
}

void extractPatchesWithGT(cv::Mat img, std::string savePathImg, std::string imgType,
                          cv::Mat gt, std::string savePathGt, std::string gtType,
                          int mode = ExtractWithGTModes::AllPixel,
                          int imgNb = UNSET_INT,
                          int granularity = GRANULARITY_DEFAULT, 
                          int step = UNSET_INT)
{
    std::vector<cv::Scalar> vectorOfColors;
    if (step == UNSET_INT) step = granularity;
    for (int row = 0; row < img.rows - granularity; row += step)
    {
        for (int col = 0; col < img.cols - granularity; col += step)
        {
            std::string imNbstr = std::to_string(imgNb);
            std::string colstr = std::to_string(col);
            std::string rowstr = std::to_string(row);
            cv::Rect roi(col, row, granularity, granularity);
            cv::Scalar color;
            if (checkOnExtractWithGTMode(gt, color, mode)) 
            {
                //Simplify notation
                std::string currSavePathImg = savePathImg.c_str + "/" + scalarToString(color) + "/";
                std::string currSavePathGt = savePathGt.c_str + "/" + scalarToString(color) + "/";

                //Create directory if necessary
                if (!scalarDirAlreadyCreated(vectorOfColors, color)) 
                {
                    vectorOfColors.push_back(color);
                    CreateDirectory(currSavePathImg.c_str, NULL);
                    CreateDirectory(currSavePathGt.c_str, NULL);
                }

                cv::imwrite(currSavePathImg + 
                            imNbstr + "_" + rowstr + "x" + colstr + "." + imgType, 
                            img(roi));
                cv::imwrite(currSavePathImg +
                            imNbstr + "_" + rowstr + "x" + colstr + "." + gtType,
                            gt(roi));
            }
        }
    }
}
bool checkOnExtractWithGTMode(cv::Mat gt, cv::Scalar& color, int mode = ExtractWithGTModes::AllPixel)
{
    gt.convertTo(gt, CV_8U); //unsigned char - 0...255

    switch (mode)
    {
        case ExtractWithGTModes::AllPixel:
            cv::Scalar curr;
            for (int row; row < gt.rows; row++)
            {
                for (int col; col < gt.cols; col++)
                {
                    if (row + col == 0) color = gt.at<uchar>(row, col);
                    curr = gt.at<uchar>(row, col);
                    if (curr != color) return false;
                }
            }
            break;

        case ExtractWithGTModes::CentralPixel:
            color = gt.at<uchar>(int(gt.rows/2), int(gt.cols/2));
            break;
        
        default: 
            break;
    }
    return true;
}

std::string scalarToString(cv::Scalar scalar)
{
    std::string str = "";
    switch (scalar.channels)
    {
        case 3:
            int a = scalar[0]; 
            int b = scalar[1]; 
            int c = scalar[2];
            str = std::to_string(a) + std::to_string(b) + std::to_string(c);
            break;
        case 1:
            int a = scalar[0];
            str = std::to_string(a);
            break;
        default:
            break;
    }
    return str;
}

bool scalarDirAlreadyCreated(std::vector<cv::Scalar> scalarVec, cv::Scalar scalar)
{

}