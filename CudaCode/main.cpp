#include <iostream>
#include "GaussianBlurFilter.h"
#include "cimg/CImg.h"
#include <iostream>
#include <cmath>

using namespace cimg_library;

int main()
{
    GBFilter filter;

    CImg<unsigned char> originalImage("img/RE1LDN2.jpg"), visu(500, 400, 1, 3, 0);
    const unsigned char red[] = {255, 0, 0}, green[] = {0, 255, 0}, blue[] = {0, 0, 255};
    double **kernel;
    const float color[] = {255., 255., 255.};

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

    CImg<unsigned char> image(width, height);
    /**/
    kernel = filter.applyFilter(kernel, filter.getGaussian(5, 5, 15.0), width, height);
    /**/

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            image(x, y) = kernel[y][x];
        }
    }

    image.draw_point(50, 50, color);
    image.normalize(0, 255);
    image.save("output.jpg");

    return 0;
}