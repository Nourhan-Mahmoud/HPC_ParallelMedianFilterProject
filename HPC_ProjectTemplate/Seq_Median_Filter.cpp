#include "Seq_Median_Filter.h"

Seq_Median_Filter::Seq_Median_Filter(int* Arr, int Width, int Height, int maskSize)
{
	int** re_imgWithBorders_v = new int* [Height + maskSize - 1];
	for (int i = 0; i < height + maskSize - 1; ++i)
	{
		re_imgWithBorders_v[i] = new int[width + maskSize - 1];
	}

	re_imgWithBorders_v = re_imgWithBorders(Arr, maskSize, Width, Height);

}

int** Seq_Median_Filter::re_imgWithBorders(int* imageData, int ms, int w, int h)
{
    #pragma region declaration
	width = w;
	height = h;
	imgWithBorders = new int* [h + ms - 1];
	for (int i = 0; i < h + ms - 1; ++i)
	{
		imgWithBorders[i] = new int[w + ms - 1];
	}

	int x = 0;//For imageData.
    #pragma endregion

	for (int i = 0; i < h + ms - 1; ++i) {// i->rows
		for (int j = 0; j < w + ms - 1; ++j) {// j->columns

			
			if (i < ms/2) //For TOP
			{
				imgWithBorders[i][j] = 0;
			}
			else if( i > h) //For BOTTOM
			{
				imgWithBorders[i][j] = 0;
			}
			else if ( j < ms/2) //FOR LEFT
			{
				imgWithBorders[i][j] = 0;
			}
			else if (j > w) //FOR RIGHT
			{
				imgWithBorders[i][j] = 0;
			}
			else 
			{
				imgWithBorders[i][j] = imageData[x];
				x++;
			}
			//cout << imgWithBorders[i][j]<< " ";
		}

		//cout << endl;
	}
	
	return imgWithBorders;
}

int* Seq_Median_Filter::returned_imageData()
{
	int* re_imgWithBorders = new int[width * height];

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			re_imgWithBorders[i * width + j] = imgWithBorders[i][j];

		}
	}
	return re_imgWithBorders;
}

int Seq_Median_Filter::return_w()
{
	return width;
}

int Seq_Median_Filter::return_h()
{
	return height;
}

Seq_Median_Filter::~Seq_Median_Filter()
{
	free(imgWithBorders);
	free(FinalData);
}