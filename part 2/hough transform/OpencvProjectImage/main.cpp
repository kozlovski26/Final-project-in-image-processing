/*

Image processing project-part 2

******houge transform*********

Names:Bar kozlovski and noa filiakov

Lecture:Moshe butman
*/

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include "Ht.h"

#define FLAG 1

using namespace std;

void exit(string msg, bool exitCode)
{
	cout << msg << endl;
	cout << endl << endl << "Press Enter to exit the program" << endl;
	cin.ignore();
	exit(exitCode);
	
}


int main(int argc, char** argv)
{
	
	// Variables:

	cv::Mat original_image;		// Original Image 
	cv::Mat blur_image;			// Image after bluring
	cv::Mat edge_image;			// Image after edge detection
	string img_path;			// The path to the image 
	
	int counter = 0;
	bool flag = 1;
	int value = 0;
	
	//start of the program
	cout << endl;
	cout << "#############  Welcome To Hough Transformation Program! #############"<< endl;
	cout << "#############  By Bar Kozlovski and Noa Filiakov #############"<< endl;
	cout << endl;

	
	img_path = "C:\\Users\\Bar\\Desktop\\3d-chess.jpg";
	original_image = cv::imread(img_path, CV_LOAD_IMAGE_COLOR);// Reading given path into a pixle matrix


	//Chacking the image path
	if (original_image.empty())
		flag = 1;
	else
		flag = 0;
	while (flag)
	{
		counter++;
		if (original_image.empty())	{
			cout << "Invalid path to image,please enter a valid path:" << endl;
			std::getline(std::cin, img_path);
			original_image = cv::imread(img_path, CV_LOAD_IMAGE_COLOR);
			if (original_image.empty())
				flag = 1;
			else
				flag = 0;}
	
		if (counter > 3){
			cout << endl;
			exit("Too much times invalid path to image,the program will stop!", 1);
		}
	}
	

	//show the the original image
		
	cv::imshow("1.Orginal image", original_image);					

	//show the bluring image 
	cout << "1.Bluring the image,Please press any key:" << endl;
	cv::waitKey();													
	
	cv::blur(original_image, blur_image, cv::Size(5, 5));				
	cv::imshow("2.Blur image", blur_image);						

	//show the edge image was creating with canny algorithm
	cout << "2.Finding the edge of the image with canny algorithm,Please press any key" << endl;
	cv::waitKey();													
	cv::Canny(blur_image, edge_image,100, 150, 3);	//100,150,3		
	cv::imshow("3.Edges iamge", edge_image);
	


	cout << "3.Moving the houge space,Please press any key:" << endl;
	cv::waitKey();												

	int w = edge_image.cols;
	int h = edge_image.rows;

	unsigned char *img_data = (unsigned char *)calloc(w * h, sizeof(unsigned char));

	for (int j = 0; j < h; j++) {
		for (int i = 0; i < w; i++) {
			uchar& uxy = edge_image.at<uchar>(j, i);
			int color = (int)uxy;
			img_data[j * w + i] = color;
		}
	}

	//Create the accumulator  
	double hough_h = ((sqrt(2.0) * (double)(h > w ? h : w)) / 2.0);
	int _accu_h = hough_h * 2.0; // -r -> +r  
	int _accu_w = 180;

	unsigned int* _accu = (unsigned int*)calloc(_accu_h * _accu_w, sizeof(unsigned int));

	double center_x = w / 2;
	double center_y = h / 2;

	for (int y = 0; y < h; y++)
	{
		for (int x = 0; x < w; x++)
		{
			if (img_data[(y*w) + x] > 250)
			{
				for (int t = 0; t < 180; t++)
				{
					double r = (((double)x - center_x) * cos((double)DegreeToRadian(t))) + (((double)y - center_y) * sin((double)DegreeToRadian(t)));
					_accu[(int)((round(r + hough_h) * 180.0)) + t]++;
				}
			}
		}
	}

 	cv::Mat hough_space = TurnImageToMatrix(_accu, _accu_w, _accu_h);
	cv::transpose(hough_space, hough_space);
	cv::imshow("4.accumulator", hough_space);
	cv::waitKey();

	//Search on the accumulator  
	std::vector< std::pair< std::pair<int, int>, std::pair<int, int> > > lines = GetLines(115, _accu, _accu_h, _accu_w, w, h);

	//Draw the results  
	std::vector< std::pair< std::pair<int, int>, std::pair<int, int> > >::iterator it;
	for (it = lines.begin(); it != lines.end(); it++)
	{
		cv::line(original_image, cv::Point(it->first.first, it->first.second), cv::Point(it->second.first, it->second.second), cv::Scalar(0, 0, 255), 2, 8);
	}

	cv::imshow("5.Hough Transform", original_image);
	cv::waitKey();

	cout << endl << endl << "Press any key to exit" << endl;
	cv::waitKey();
	
}



