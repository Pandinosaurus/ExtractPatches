#pragma once

#include "../headers/headers.hpp"
#include "../headers/globalvar.hpp"

void extractPatches(cv::Mat img, std::string savePath, std::string imageType = "jpg", int granularity = GRANULARITY_DEFAULT, int imgNb = UNSET_INT, int step = UNSET_INT)
{
    if (step == UNSET_INT) step = granularity;
    for (int row = 0; row < img.rows - granularity; row += step)
    {
        for (int col = 0; col < img.cols - granularity; col += step)
        {
            std::string imNbstr = std::to_string(imgNb);
            std::string colstr = std::to_string(col);
            std::string rowstr = std::to_string(row);
            cv::Rect roi(col, row, granularity, granularity);
            cv::imwrite(savePath + imNbstr + "_" + rowstr + "x" + colstr + "." + imageType, img(roi));
        }
    }
}