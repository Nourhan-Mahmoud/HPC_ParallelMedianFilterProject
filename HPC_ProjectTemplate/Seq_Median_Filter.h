#pragma once
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include<string.h>
#include<msclr\marshal_cppstd.h>
#include <vector>
#include <algorithm>

using namespace std;

ref class Seq_Median_Filter
{
public:

	int width, height;
	int** imgWithBorders;
	int** FinalImage;
	Seq_Median_Filter(int*, int, int, int);
	int* returned_imageData(int , int);
	int**re_imgWithBorders(int*, int, int, int);
	int** applyMask(int**, int, int, int);
	int SortImageMask(int**,int);
	int return_w();
	int return_h();
	~Seq_Median_Filter();
};

