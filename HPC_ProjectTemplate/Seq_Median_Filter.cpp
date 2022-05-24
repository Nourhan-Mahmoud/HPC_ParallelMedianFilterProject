#include "Seq_Median_Filter.h"

Seq_Median_Filter::Seq_Median_Filter(int* Arr, int Width, int Height, int maskSize)
{
	int** re_imgWithBorders_v = re_imgWithBorders(Arr, maskSize, Width, Height);
	FinalImage = applyMask(re_imgWithBorders_v, maskSize,width,height);

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
			else if( i > (h-1+(ms/2))) //For BOTTOM
			{
				imgWithBorders[i][j] = 0;
			}
			else if ( j < ms/2) //FOR LEFT
			{
				imgWithBorders[i][j] = 0;
			}
			else if (j > ((w-1)+(ms/2))) //FOR RIGHT
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

int** Seq_Median_Filter::applyMask(int** img, int ms, int w, int h) {

	int** mask = new int* [ms];
	for (int i = 0; i < ms; ++i)
	{
		mask[i] = new int[ms];
	}

	for (int i = 0; i < h; ++i)//For Rows
	{
		for (int j = 0; j < w; ++j)//For Columns
		{
			for (int x = 0; x < ms; x++) //For mask Rows
			{
				for (int y = 0; y < ms; y++)//For mask Columns
				{
					int ii = x+i;
					int jj = y+j;
					mask[x][y] = img[ii][jj];
				}
			}

			//Sort and apply Filter
			img[i][j] = SortImageMask(mask,ms);
		}
	}
	return img;
}

int Seq_Median_Filter::SortImageMask(int** mask,int ms)
{
	int* m = new int[ms*ms];

	for (int i = 0; i < ms; i++)
	{
		for (int j = 0; j < ms; j++)
		{
			m[i * ms + j] = mask[i][j];
		}
	}

	sort(m, m + (ms*ms));

	int target = m[(ms * ms) / 2];

	return target;
}
int* Seq_Median_Filter::returned_imageData(int w, int h)
{
	//cout << w << " " << h << "Class\n";
	int* final_img = new int[w * h];

	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			final_img[i * w + j] = FinalImage[i][j];

		}
	}

	return final_img;
	
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
	free(FinalImage);
}