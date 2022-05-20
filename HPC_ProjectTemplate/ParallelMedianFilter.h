#pragma once
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include<string.h>
#include<msclr\marshal_cppstd.h>
#include <vector>
#include <algorithm>
#include <mpi.h>

using namespace std;

ref class ParallelMedianFilter
{
public:
	int width;
	int height;
	int* Final_img;
	ParallelMedianFilter(int*, int, int, int);
	int** applyMask(int**, int, int, int);
	int SortImageMask(int**, int);
	int** re_imgWithBorders(int* , int , int , int );
	int* returned_imageData_parallel(int, int);
	~ParallelMedianFilter();
};

