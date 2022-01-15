#include <iostream>
#include <cuda.h>
#include "GaussianBlurFilter.h"

double **GBFilter::getGaussian(int height, int width, double sigma)
{
    double **filter;
    double sum = 0.0;
    int i, j;

    filter = new double *[height];
    for (int i = 0; i < height; i++)
        filter[i] = new double[width];

    for (i = 0; i < height; i++)
        for (j = 0; j < width; j++)
        {
            filter[i][j] = exp(-(i * i + j * j) / (2 * sigma * sigma)) / (2 * M_PI * sigma * sigma);
            sum += filter[i][j];
        }

    for (i = 0; i < height; i++)
        for (j = 0; j < width; j++)
            filter[i][j] /= sum;

    return filter;
}

double ***GBFilter::applyFilter(double ***image, double **filter, int width, int height, int filterWidth, int filterHeight)
{

    int newImageHeight = height - filterHeight + 1;
    int newImageWidth = width - filterWidth + 1;
    int d, i, j, h, w;

    double ***newImage;
    newImage = new double **[3];
    for (int i = 0; i < 3; i++)
    {
        newImage[i] = new double *[width];
        for (int j = 0; j < width; j++)
            newImage[i][j] = new double[height];
    }

    for (d = 0; d < 3; d++)
        for (i = 0; i < newImageWidth; i++)
            for (j = 0; j < newImageHeight; j++)
                for (h = i; h < i + filterWidth; h++)
                    for (w = j; w < j + filterHeight; w++)
                        newImage[d][i][j] += filter[h - i][w - j] * image[d][h][w];

    return newImage;
}
