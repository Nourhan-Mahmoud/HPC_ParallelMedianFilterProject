#include "ParallelMedianFilter.h"

ParallelMedianFilter::ParallelMedianFilter(int* Arr, int Width, int Height, int maskSize) 
{

	MPI_Init(NULL, NULL);
	//parallel code here
	MPI_Finalize();

}

int* ParallelMedianFilter::returned_imageData_parallel(int width,int height) 
{

}

ParallelMedianFilter::~ParallelMedianFilter() 
{

}
