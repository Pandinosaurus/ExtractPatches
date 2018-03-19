#pragma once

#include "../headers/headers.hpp"
#include "../headers/globalvar.hpp"

bool checkOnExtractWithGTMode(const cv::Mat& gtroi, cv::Scalar& color, const int& mode = ExtractWithGTModes::AllPixel)
{
    gt.convertTo(gt, CV_8UC3); //unsigned char - 0...255

    uint8_t* pixelPtr = (uint8_t*)gt.data;
    int cn = gt.channels();
    cv::Scalar curr;

    switch (mode)
    {
    case ExtractWithGTModes::AllPixel:
        for (int row = 0; row < gt.rows; row++)
        {
            for (int col = 0; col < gt.cols; col++)
            {
                if (row + col == 0) 
                {
                    color.val[0] = pixelPtr[row*gt.cols*cn + col*cn + 0]; // B
                    color.val[1] = pixelPtr[row*gt.cols*cn + col*cn + 1]; // G
                    color.val[2] = pixelPtr[row*gt.cols*cn + col*cn + 2]; // R
                }
                curr.val[0] = pixelPtr[row*gt.cols*cn + col*cn + 0]; // B
                curr.val[1] = pixelPtr[row*gt.cols*cn + col*cn + 1]; // G
                curr.val[2] = pixelPtr[row*gt.cols*cn + col*cn + 2]; // R
                if (curr != color) return false;
            }
        }
        break;
    case ExtractWithGTModes::CentralPixel:
        color = gt.at<uchar>(int(gt.rows / 2), int(gt.cols / 2));
        break;
    }
    return true;
}

std::string scalarToString(const cv::Scalar& scalar)
{
    std::string str = "";
    int a, b, c;
    switch (scalar.channels)
    {
    case 3:
        a = scalar[0];
        b = scalar[1];
        c = scalar[2];
        str = std::to_string(a) + "_" + std::to_string(b) + "_" + std::to_string(c);
        break;
    case 1:
        a = scalar[0];
        str = std::to_string(a);
        break;
    }
    return str;
}

bool scalarDirAlreadyCreated(const std::vector<cv::Scalar>& scalarVec, const cv::Scalar& scalar)
{
    for (auto s : scalarVec)
        if (s == scalar) return true;
    return false;
}

void extractPatchesWithGT(const cv::Mat& img, const std::string& savePathImg, const std::string& imgType,
                          const cv::Mat& gt, const std::string& savePathGt, const std::string& gtType,
                          const int& mode = ExtractWithGTModes::AllPixel,
                          const int& imgNb = UNSET_INT,
                          const int& granularity = GRANULARITY_DEFAULT, 
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
            if (checkOnExtractWithGTMode(gt(roi), color, mode)) 
            {
                //Simplify notation
                std::string currSavePathImg = savePathImg + "/" + scalarToString(color) + "/";
                std::string currSavePathGt = savePathGt + "/" + scalarToString(color) + "/";

                //Create directory if necessary
                if (!scalarDirAlreadyCreated(vectorOfColors, color)) 
                {
                    vectorOfColors.push_back(color);
                    CreateDirectory(currSavePathImg.c_str(), NULL);
                    CreateDirectory(currSavePathGt.c_str(), NULL);
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

void extractPatches(const cv::Mat& img, const std::string& savePath, const std::string& imgType = "jpg",
    const int& granularity = GRANULARITY_DEFAULT,
    const int& imgNb = UNSET_INT,
    int step = UNSET_INT)
{
    CreateDirectory(savePath.c_str(), NULL);

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