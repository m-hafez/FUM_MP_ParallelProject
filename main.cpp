#include "cimg\CImg.h"
#include <iostream>
#include <cmath>

using namespace cimg_library;

double **getGaussian(int height, int width, double sigma)
{
    double **filter;
    double sum = 0.0;
    int i, j;

    filter = new double *[height];
    for (int i = 0; i < height; i++)
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

double **applyFilter(double **image, double **filter, int width, int height)
{
    int filterHeight = 5;
    int filterWidth = 5;
    int newImageHeight = height - filterHeight + 1;
    int newImageWidth = width - filterWidth + 1;
    int d, i, j, h, w;

    double **newImage;
    newImage = new double *[height];
    for (int i = 0; i < height; i++)
    {
        newImage[i] = new double[width];
    }

    // for (int i = 0; i < height; i++)
    // {
    //     for (int j = 0; j < width; j++)
    //     {
    //         newImage[i][j] = 0.0;
    //     }
    // }

    // for (i = 0; i < newImageHeight; i++)
    // {
    //     for (j = 0; j < newImageWidth; j++)
    //     {
    //         for (h = i; h < i + filterHeight; h++)
    //         {
    //             for (w = j; w < j + filterWidth; w++)
    //             {
    //                 newImage[i][j] += filter[h - i][w - j] * image[h][w];
    //             }
    //         }
    //     }
    // }

    int sum;
    for (int y = 1; y < height - 1; y++)
    {
        for (int x = 1; x < width - 1; x++)
        {
            sum = 0.0;
            for (int k = -1; k <= 1; k++)
            {
                for (int j = -1; j <= 1; j++)
                {
                    sum = sum + filter[j + 1][k + 1] * image[y - j][x - k];
                }
            }
            newImage[y][x] = sum;
        }
    }

    return newImage;
}

int main(int argc, char const *argv[])
{
    CImg<unsigned char> originalImage("img/RE1LDN2.jpg"), visu(500, 400, 1, 3, 0);
    const unsigned char red[] = {255, 0, 0}, green[] = {0, 255, 0}, blue[] = {0, 0, 255};
    double **kernel;

    int width = originalImage.width();
    int height = originalImage.height();

    kernel = new double *[height];
    for (int i = 0; i < height; i++)
    {
        kernel[i] = new double[width];
    }

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            kernel[y][x] = (double)originalImage(x, y);
        }
    }

    CImgDisplay Original_image(originalImage, "Original image");

    // originalImage.blur(2.5);
    // CImgDisplay Original_s_image(originalImage, "Original dd image");

    CImg<unsigned char> image(width, height);
    /**/
    kernel = applyFilter(kernel, getGaussian(5, 5, 15.0), width, height);
    /**/

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            image(x, y) = kernel[y][x];
        }
    }

    CImgDisplay main_disp(image, "Modified image, Click a point"), draw_disp(visu, "Intensity profile");
    while (!main_disp.is_closed() && !draw_disp.is_closed())
    {
        main_disp.wait();
        if (main_disp.button() && main_disp.mouse_y() >= 0)
        {
            const int y = main_disp.mouse_y();
            visu.fill(0).draw_graph(image.get_crop(0, y, 0, 0, image.width() - 1, y, 0, 0), red, 1, 1, 0, 255, 0);
            visu.draw_graph(image.get_crop(0, y, 0, 1, image.width() - 1, y, 0, 1), green, 1, 1, 0, 255, 0);
            visu.draw_graph(image.get_crop(0, y, 0, 2, image.width() - 1, y, 0, 2), blue, 1, 1, 0, 255, 0).display(draw_disp);
        }
    }
    return 0;
}
