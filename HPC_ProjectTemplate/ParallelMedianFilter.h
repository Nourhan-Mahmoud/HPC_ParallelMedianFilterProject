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
	ParallelMedianFilter(int*, int, int, int);
	int* returned_imageData_parallel(int, int);
	~ParallelMedianFilter();
};

