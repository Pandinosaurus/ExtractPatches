/* iscolor.hpp
*
* Author: Rémi Ratajczak
* Email : remi.ratajczak@gmail.com
* LICENSE : MIT
*
*/

#pragma once

#include "../headers/headers.hpp"
/* Check if a 3 channels image is in color or in grayscale */
bool isColor(cv::Mat & img)
{
    //Get directory
    std::vector<cv::Mat> channels;
    cv::split(img, channels);
    if (cv::countNonZero(channels[0] - channels[1]) == 0) return false;
    return true;
}