#pragma once
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include<string.h>
#include<msclr\marshal_cppstd.h>

using namespace std;

ref class sequential_median_filter
{
public:
	int* img_data;
	sequential_median_filter(int* img_data, int OriginalImageWidth, int OriginalImageHeight);
	int* returned_imageData();
	~sequential_median_filter();
};

