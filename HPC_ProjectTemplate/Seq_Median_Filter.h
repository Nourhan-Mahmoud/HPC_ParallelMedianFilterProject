#pragma once
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include<string.h>
#include<msclr\marshal_cppstd.h>
#include <vector>

using namespace std;

ref class Seq_Median_Filter
{
public:

	int* FinalData;
	int width, height;
	int** imgWithBorders;
	Seq_Median_Filter(int*, int, int, int);
	int* returned_imageData();
	int**re_imgWithBorders(int*, int, int, int);
	int return_w();
	int return_h();
	~Seq_Median_Filter();
};

