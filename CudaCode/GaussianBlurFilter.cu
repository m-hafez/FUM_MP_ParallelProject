#include <iostream>
#include <cuda.h>
#include "GaussianBlurFilter.h"

__global__ void cudaKernel(int *n, int limit)
{

}


double **GBFilter::getGaussian(int height, int width, double sigma)
{
    double **filter;
    double sum = 0.0;
    int i, j;

    filter = new double *[height];
    for (i = 0; i < height; i++)
    {
        filter[i] = new double[width];
    }

    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            filter[i][j] = exp(-(i * i + j * j) / (2 * sigma * sigma)) / (2 * M_PI * sigma * sigma);
            sum += filter[i][j];
        }
    }

    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            filter[i][j] /= sum;
        }
    }

    return filter;
}

double **GBFilter::applyFilter(double **image, double **filter, int width, int height)
{
    int filterHeight = 5;
    int filterWidth = 5;
    int newImageHeight = height - filterHeight + 1;
    int newImageWidth = width - filterWidth + 1;
    int i, j, h, w;

    double **newImage;
    newImage = new double *[height];
    {
        for (i = 0; i < height; i++)
        {
            newImage[i] = new double[width];
        }

        for (i = 0; i < newImageHeight; i++)
        {
            for (j = 0; j < newImageWidth; j++)
            {
                for (h = i; h < i + filterHeight; h++)
                {
                    for (w = j; w < j + filterWidth; w++)
                    {
                        newImage[i][j] += filter[h - i][w - j] * image[h][w];
                    }
                }
            }
        }
    }

    return newImage;
}

