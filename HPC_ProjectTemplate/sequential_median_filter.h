#pragma once
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include<string.h>
#include<msclr\marshal_cppstd.h>
#include <vector>

using namespace std;

ref class sequential_median_filter
{
public:

	int* FinalData;
    int* imgWithBorders;
	int* image;
	sequential_median_filter(int*, int , int ,int );
	int* returned_imageData();
	int* returned_imgWithBorders(int* , int , int, int);
	~sequential_median_filter();
};

