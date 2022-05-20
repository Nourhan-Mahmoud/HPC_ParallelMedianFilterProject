#include "ParallelMedianFilter.h"

ParallelMedianFilter::ParallelMedianFilter(int* Arr, int Width, int Height, int maskSize)
{

	MPI_Init(NULL, NULL);

	int rank, size;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	int sizePerMachine = Height / size;
	
	Final_img = new int[Height * Width];

	int* recv = new int [sizePerMachine*Width];

	MPI_Bcast(Arr, Height * Width, MPI_INT, 0, MPI_COMM_WORLD);

    MPI_Scatter(Arr, sizePerMachine * Width, MPI_INT, recv, sizePerMachine * Width, MPI_INT, 0, MPI_COMM_WORLD);
	
	int** re_imgWithBorders_v = new int* [sizePerMachine + maskSize - 1];
	for (int i = 0; i < sizePerMachine + maskSize - 1; ++i)
	{
		re_imgWithBorders_v[i] = new int[Width + maskSize - 1];
	}

	re_imgWithBorders_v = re_imgWithBorders(Arr, maskSize, Width, sizePerMachine);



	int** FinalImage = new int* [sizePerMachine + maskSize - 1];
	for (int i = 0; i < sizePerMachine + maskSize - 1; ++i)
	{
		FinalImage[i] = new int[Width + maskSize - 1];
	}

	FinalImage = applyMask(re_imgWithBorders_v, maskSize, Width, sizePerMachine);


	int* final_img = new int[sizePerMachine * Width];

	for (int i = 0; i < sizePerMachine; i++)
	{
		for (int j = 0; j < Width; j++)
		{
			final_img[i * Width + j] = FinalImage[i][j];
		}
	}

	if (rank == 0) {
		MPI_Gather(final_img, sizePerMachine * Width, MPI_INT, Final_img, sizePerMachine * Width, MPI_INT, 0, MPI_COMM_WORLD);
	}


	MPI_Finalize();
}

int** ParallelMedianFilter::applyMask(int** img, int ms, int w, int h) {

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
					int ii = x + i;
					int jj = y + j;
					mask[x][y] = img[ii][jj];
				}
			}

			//Sort and apply Filter
			img[i][j] = SortImageMask(mask, ms);
		}
	}
	return img;
}

int ParallelMedianFilter::SortImageMask(int** mask, int ms)
{
	int* m = new int[ms * ms];

	for (int i = 0; i < ms; i++)
	{
		for (int j = 0; j < ms; j++)
		{
			m[i * ms + j] = mask[i][j];
		}
	}

	sort(m, m + (ms * ms));

	int target = m[(ms * ms) / 2];

	return target;
}

int** ParallelMedianFilter::re_imgWithBorders(int* imageData, int ms, int w, int h) {
	#pragma region declaration
		int** imgWithBorders = new int* [h + ms - 1];
		for (int i = 0; i < h + ms - 1; ++i)
		{
			imgWithBorders[i] = new int[w + ms - 1];
		}
		int x = 0;//For imageData.
	#pragma endregion

	for (int i = 0; i < h + ms - 1; ++i) {// i->rows
		for (int j = 0; j < w + ms - 1; ++j) {// j->columns


			if (i < ms / 2) //For TOP
			{
				imgWithBorders[i][j] = 0;
			}
			else if (i > (h - 1 + (ms / 2))) //For BOTTOM
			{
				imgWithBorders[i][j] = 0;
			}
			else if (j < ms / 2) //FOR LEFT
			{
				imgWithBorders[i][j] = 0;
			}
			else if (j > ((w - 1) + (ms / 2))) //FOR RIGHT
			{
				imgWithBorders[i][j] = 0;
			}
			else
			{
				imgWithBorders[i][j] = imageData[x];
				x++;
			}
		}

	}

	return imgWithBorders;
}

int* ParallelMedianFilter::returned_imageData_parallel(int width, int height)
{
	return Final_img;
}

ParallelMedianFilter::~ParallelMedianFilter()
{
	free(Final_img);
}