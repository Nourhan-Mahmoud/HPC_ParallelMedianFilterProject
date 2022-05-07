#include "sequential_median_filter.h"

sequential_median_filter::sequential_median_filter(int* imageArray, int OriginalImageWidth,int OriginalImageHeight) {
	img_data = imageArray;
	int mask[3][3] = { {0,0,0},{0,0,0},{0,0,0} };
	
	for (int i = 0; i < OriginalImageHeight; i++) {
		for (int j = 0; j < OriginalImageWidth; j++) {

		}
	}


	
}
int* sequential_median_filter::returned_imageData() {
	return img_data;
}
sequential_median_filter::~sequential_median_filter() {
	free(img_data);
}