/*

Image processing project-part 2

******houge transform*********

Names:Bar kozlovski and noa filiakov

Lecture:Moshe butman
*/
#pragma once
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <math.h> 

using namespace cv;

double DegreeToRadian(double degrees);

Mat TurnImageToMatrix(unsigned int *buffer, int w, int h);

std::vector< std::pair< std::pair<int, int>, std::pair<int, int> > > GetLines(int threshold, unsigned int* _accu, int _accu_h, int _accu_w, int _img_w, int _img_h);