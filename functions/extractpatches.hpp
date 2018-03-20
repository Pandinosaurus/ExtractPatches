#pragma once

#include "../headers/headers.hpp"
#include "../headers/globalvar.hpp"


bool areAllColorPixelsEquals(const cv::Mat& img, cv::Scalar& color)
{
    uint8_t* pixelPtr = (uint8_t*)img.data;
    int cn = img.channels();
    cv::Scalar curr;

    for (int row = 0; row < img.rows; row++)
    {
        for (int col = 0; col < img.cols; col++)
        {
            if (row + col == 0){
                color.val[0] = pixelPtr[row*img.cols*cn + col*cn + 0]; // B
                color.val[1] = pixelPtr[row*img.cols*cn + col*cn + 1]; // G
                color.val[2] = pixelPtr[row*img.cols*cn + col*cn + 2]; // R
            }
            curr.val[0] = pixelPtr[row*img.cols*cn + col*cn + 0]; // B
            curr.val[1] = pixelPtr[row*img.cols*cn + col*cn + 1]; // G
            curr.val[2] = pixelPtr[row*img.cols*cn + col*cn + 2]; // R
            if (curr != color) return false;
        }
    }
    return true;
}

bool areAllGrayPixelsEquals(const cv::Mat& img, cv::Scalar& color)
{
    uint8_t* pixelPtr = (uint8_t*)img.data;
    cv::Scalar curr;

    for (int row = 0; row < img.rows; row++)
    {
        for (int col = 0; col < img.cols; col++)
        {
            if (row + col == 0){
                color.val[0] = pixelPtr[row*img.cols + col]; // Gray
            }
            curr.val[0] = pixelPtr[row*img.cols + col + 0]; // Gray
            if (curr != color) return false;
        }
    }
    return true;
}

bool areAllPixelsEquals(const cv::Mat& img, cv::Scalar& color)
{
    switch (img.channels())
    {
    case 3: return areAllColorPixelsEquals(img, color);
    case 1: return areAllGrayPixelsEquals(img, color);
    }
    return false;
}


bool checkOnExtractWithGTMode(const cv::Mat& gtroi, cv::Scalar& color, const int& mode = ExtractWithGTModes::AllPixel)
{
    gtroi.convertTo(gtroi, CV_8UC3); //unsigned char - 0...255

    switch (mode)
    {
    case ExtractWithGTModes::AllPixel:
        return areAllPixelsEquals(gtroi, color);
        break;
    case ExtractWithGTModes::CentralPixel:
        color = gtroi.at<uchar>(int(gtroi.rows / 2), int(gtroi.cols / 2));
        break;
    }
    return false;
}

std::string scalarToString(const cv::Scalar& scalar)
{
    std::string str = "";
    int a, b, c, d;
    switch (scalar.channels)
    {
    case 4:
        a = scalar[0];
        b = scalar[1];
        c = scalar[2];
        str = std::to_string(a) + "_" + std::to_string(b) + "_" + std::to_string(c);
        break;
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

bool DirectoryExists(LPCTSTR szPath)
{
    DWORD dwAttrib = GetFileAttributes(szPath);

    return (dwAttrib != INVALID_FILE_ATTRIBUTES &&
        (dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
}

void createDirectoryRecursively(std::string path)
{
    std::size_t pos = 0;
    do
    {
        pos = path.find_first_of("\\/", pos+1);
        CreateDirectory(path.substr(0, pos).c_str(), NULL);
    } while (pos != std::string::npos);
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
            cv::Mat gtroi = gt(roi); //for debug
            cv::Scalar color;
            if (checkOnExtractWithGTMode(gt(roi), color, mode)) 
            {
                //Simplify notation
                std::string currSavePathImg = savePathImg + "\\" + scalarToString(color) + "\\";
                std::string currSavePathGt = savePathGt + "\\" + scalarToString(color) + "\\";

                std::cout << currSavePathImg << std::endl;

                //Create directory if necessary
                if (!scalarDirAlreadyCreated(vectorOfColors, color)) 
                {
                    //Add color to vector
                    vectorOfColors.push_back(color);

                    //Create corresponding directories if they don't exist
                    //ToDo : add flag for user to avoid directory existence check
                    if (!DirectoryExists(currSavePathImg.c_str())) {
                        createDirectoryRecursively(currSavePathImg);
                    }
                    if (!DirectoryExists(currSavePathGt.c_str())) {
                        createDirectoryRecursively(currSavePathGt);
                    }
                }

                cv::imwrite(currSavePathImg + 
                            imNbstr + "_" + rowstr + "x" + colstr + "." + imgType, 
                            img(roi));
                //for debug purpose
                cv::imwrite(currSavePathGt +
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
    //Create corresponding directories if they don't exist
    //ToDo : add flag for user to avoid directory existence check
    if (!DirectoryExists(savePath.c_str())) {
        createDirectoryRecursively(savePath);
    }

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