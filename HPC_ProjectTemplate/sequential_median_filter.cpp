#include "sequential_median_filter.h"

sequential_median_filter::sequential_median_filter(int* imageArray, int OriginalImageWidth,int OriginalImageHeight,int maskSize)
{
	
	int mask[99][99] = {0};
	
	imgWithBorders = returned_imgWithBorders(imageArray, maskSize, OriginalImageWidth, OriginalImageHeight);
	//cout << *imgWithBorders;

	//for (int i = 0; i < OriginalImageHeight + mask_size; i++) {

		for (int j = 0; j < OriginalImageWidth + maskSize; j++) {
			cout << *imgWithBorders << " ";
			if (*(imgWithBorders) == NULL) {
				cout << "NULLLLLL\n";
			}
			imgWithBorders++;
		}
		cout << endl;
	//}

	

	
}

int* sequential_median_filter::returned_imgWithBorders(int* imageData, int maskSize, int width, int height)
{
	int zero = 0;
	int ms = maskSize / 2;

	for (int i = 0; i < height*width; i++) {

		//add zeroes to upper
		if (i==0)
		{
			for (int m = 0; m < ms; m++) {
				for (int z = 0; z < width+(ms*2); z++) {
					 image = &zero;
					 image++;
				}
			}

			for (int z = 0; z < ms; z++) {
				image = &zero;
				 image++;
			}

			image = imageData;
			imageData++;
			image++;
		}
		//add zeroes to the left
		else if(i%width == 0 && i!=0)
		{
			for (int z = 0; z < ms; z++) {
				image = &zero;
				image++;
			}

			image = imageData;
			imageData++;
			image++;
		}
		//add zeroes to the right
		else if(i+1 % width == 0)
		{
			image = imageData;
			imageData++;
			image++;

			for (int z = 0; z < ms; z++) {
				image = &zero;
				image++;
			}

			//add zeroes to the bottom
			if (i == (width * height) - 1) {

				for (int m = 0; m < ms; m++) {
					for (int z = 0; z < width + (ms*2); z++) {
						image = &zero;
						image++;
					}
				}
			}
		}
		else
		{
			image = imageData;
			imageData++;
			image++;
		}

		
	}

	return image;
}
int* sequential_median_filter::returned_imageData()
{
	return FinalData;
}
sequential_median_filter::~sequential_median_filter()
{
	free(FinalData);
	free(imgWithBorders);
}