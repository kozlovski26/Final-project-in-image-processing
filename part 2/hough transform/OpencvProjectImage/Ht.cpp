/*

Image processing project-part 2

******houge transform*********

Names:Bar kozlovski and noa filiakov

Lecture:Moshe butman
*/


#include "Ht.h"
#include <iostream>


using namespace std;

#define P 3.14159265


//degree to radian
double DegreeToRadian(double degrees) {
	return degrees * 4.0 * atan(1.0) / 180.0;
}
//turn the image to a matrix
Mat TurnImageToMatrix(unsigned int *buffer, int w, int h) {
	Mat tmp(w, h, CV_8UC1);
	for (int x = 0; x < h; x++) {
		for (int y = 0; y < w; y++) {
			int value = (int)buffer[x * w + y];
			if (value < 255)
				tmp.at<uchar>(y, x) = value;
			else
				tmp.at<uchar>(y, x) = 255;
		}
	}
	return tmp;
}


std::vector< std::pair< std::pair<int, int>, std::pair<int, int> > > GetLines(int threshold, unsigned int* _accu, int _accu_h, int _accu_w, int _img_w, int _img_h)
{
	std::vector< std::pair< std::pair<int, int>, std::pair<int, int> > > lines;

	if (_accu == 0)
		return lines;

	for (int r = 0; r < _accu_h; r++)
	{
		for (int t = 0; t < _accu_w; t++)
		{
 			if ((int)_accu[(r*_accu_w) + t] >= threshold)
			{
				
				int max = _accu[(r*_accu_w) + t];
				for (int ly = -4; ly <= 4; ly++)
				{
					for (int lx = -4; lx <= 4; lx++)
					{
						if ((ly + r >= 0 && ly + r < _accu_h) && (lx + t >= 0 && lx + t < _accu_w))
						{
							if ((int)_accu[((r + ly)*_accu_w) + (t + lx)] > max)
							{
								max = _accu[((r + ly)*_accu_w) + (t + lx)];
								ly = lx = 5;
							}
						}
					}
				}
				if (max >(int)_accu[(r*_accu_w) + t])
					continue;


				int x1, y1, x2, y2;
				x1 = y1 = x2 = y2 = 0;

				if (t >= 45 && t <= 135)
				{
					//y = (r - x cos(t)) / sin(t)  
					x1 = 0;
					y1 = ((double)(r - (_accu_h / 2)) - ((x1 - (_img_w / 2)) * cos(DegreeToRadian(t)))) / sin(DegreeToRadian(t)) + (_img_h / 2);
					x2 = _img_w - 0;
					y2 = ((double)(r - (_accu_h / 2)) - ((x2 - (_img_w / 2)) * cos(DegreeToRadian(t)))) / sin(DegreeToRadian(t)) + (_img_h / 2);
				}
				else
				{
					//x = (r - y sin(t)) / cos(t);  
					y1 = 0;
					x1 = ((double)(r - (_accu_h / 2)) - ((y1 - (_img_h / 2)) * sin(DegreeToRadian(t)))) / cos(DegreeToRadian(t)) + (_img_w / 2);
					y2 = _img_h - 0;
					x2 = ((double)(r - (_accu_h / 2)) - ((y2 - (_img_h / 2)) * sin(DegreeToRadian(t)))) / cos(DegreeToRadian(t)) + (_img_w / 2);
				}

				lines.push_back(std::pair< std::pair<int, int>, std::pair<int, int> >(std::pair<int, int>(x1, y1), std::pair<int, int>(x2, y2)));

			}
		}
	}

	//std::cout << "number of lines: " << lines.size() << " " << threshold << std::endl;
	return lines;
}