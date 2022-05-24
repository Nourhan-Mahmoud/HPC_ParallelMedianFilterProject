#include <iostream>
#include <math.h>
#include <stdlib.h>
#include<string.h>
#include<msclr\marshal_cppstd.h>
#include <ctime>// include this header 
#include "Seq_Median_Filter.h"
#include "ParallelMedianFilter.h"
#pragma once
#using <mscorlib.dll>
#using <System.dll>
#using <System.Drawing.dll>
#using <System.Windows.Forms.dll>
using namespace std;
using namespace msclr::interop;

int OriginalImageWidth, OriginalImageHeight;
int* inputImage(int* w, int* h, System::String^ imagePath) //put the size of image in w & h
{
	int* input;

	//*********************************************************Read Image and save it to local arrayss*************************	
	//Read Image and save it to local arrayss

	System::Drawing::Bitmap BM(imagePath);

	OriginalImageWidth = BM.Width;
	OriginalImageHeight = BM.Height;
	
	*w = BM.Width;
	*h = BM.Height;
	int *Red = new int[BM.Height * BM.Width];
	int *Green = new int[BM.Height * BM.Width];
	int *Blue = new int[BM.Height * BM.Width];
	input = new int[BM.Height*BM.Width];

	for (int i = 0; i < BM.Height; i++)
	{
		for (int j = 0; j < BM.Width; j++)
		{
			System::Drawing::Color c = BM.GetPixel(j, i);

			Red[i * BM.Width + j] = c.R;
			Blue[i * BM.Width + j] = c.B;
			Green[i * BM.Width + j] = c.G;

			input[i*BM.Width + j] = ((c.R + c.B + c.G) / 3); //gray scale value equals the average of RGB values

		}

	}
	return input;
}
void createImage(int* image, int width, int height, int index)
{
	//cout << width << height<<"Done!\n";
	System::Drawing::Bitmap MyNewImage(width, height);

	for (int i = 0; i < MyNewImage.Height; i++)
	{
		for (int j = 0; j < MyNewImage.Width; j++)
		{
			//i * OriginalImageWidth + j
			if (image[i*width + j] < 0)
			{
				image[i*width + j] = 0;
			}
			if (image[i*width + j] > 255)
			{
				image[i*width + j] = 255;
			}
			System::Drawing::Color c = System::Drawing::Color::FromArgb(image[i*MyNewImage.Width + j], image[i*MyNewImage.Width + j], image[i*MyNewImage.Width + j]);
			MyNewImage.SetPixel(j, i, c);
		}
	}
	MyNewImage.Save("..//Data//Output//outputRes" + index + ".png");
	cout << "result Image Saved " << index << endl;
}

int main()
{
	int ImageWidth = 4, ImageHeight = 4;

    #pragma region  Set Mask Size
	int maskSize = 3;
	cout << "Mask Size is "<<maskSize<<"\n";
    #pragma endregion

	System::String^ imagePath;
	std::string img;
	img = "..//Data//Input//N_N_Salt_Pepper.png";

	imagePath = marshal_as<System::String^>(img);
	int* imageData = inputImage(&ImageWidth, &ImageHeight, imagePath);


    #pragma region Sequential Median Filter

	int start_time_For_SeqentialCode, stop_time_For_SeqentialCode, Totaltime_For_SeqentialCode = 0;

	start_time_For_SeqentialCode = clock();

	Seq_Median_Filter seq_f(imageData, OriginalImageWidth, OriginalImageHeight, maskSize);
	int* re_imageData = seq_f.returned_imageData(OriginalImageWidth, OriginalImageHeight);

	createImage(re_imageData, OriginalImageWidth, OriginalImageHeight, 0);
	
	stop_time_For_SeqentialCode = clock();
	Totaltime_For_SeqentialCode += (stop_time_For_SeqentialCode - start_time_For_SeqentialCode) / double(CLOCKS_PER_SEC) * 1000;
	cout << "Time For Sequential Code : " << Totaltime_For_SeqentialCode << endl;

    #pragma endregion

	#pragma region Parallel Median Filter

	int start_time_For_Parallel, stop_time_For_Parallel, Totaltime_For_Parallel = 0;

	start_time_For_Parallel = clock();

	ParallelMedianFilter Parallel_f(imageData, OriginalImageWidth, OriginalImageHeight, maskSize);
	int* re_imageData_Parallel = Parallel_f.returned_imageData_parallel(OriginalImageWidth, OriginalImageHeight);
	createImage(re_imageData_Parallel, OriginalImageWidth, OriginalImageHeight, 1);


	stop_time_For_Parallel = clock();
	Totaltime_For_Parallel += (stop_time_For_Parallel - start_time_For_Parallel) / double(CLOCKS_PER_SEC) * 1000;
	cout << "Time For Parallel Code : " << Totaltime_For_Parallel << endl;

	#pragma endregion


	free(imageData);
	free(re_imageData);
	free(re_imageData_Parallel);

	system("pause");
	return 0;

}



