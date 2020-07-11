# FUM_MP_ParallelProject-2_98-99
Ferdowsi University multicore programming course projects, 98-99 Semester 2.

this project applying [Gaussian blur](https://en.wikipedia.org/wiki/Gaussian_blur) filter on input image and using [CImg](https://cimg.eu/) C++ Library for loading and showing the image. 

## Requirements
* [imagemagick](https://imagemagick.org/script/download.php)

## CUDA version Google Colab
* [FUM_MP_ParallelProject-2_98-99.ipynb](https://colab.research.google.com/drive/1SLtdS1veZZU5Fy9zX8lLAZk5o5ogKmJu?usp=sharing)


## compile on windows 
```sh
g++ .\main.cpp -o .\main -O2 -lgdi32
```
* with openmp
```sh
g++ .\main.cpp -o .\main -O2 -lgdi32 -fopenmp
```
* with cuda
```sh
!nvcc -o /content/main /content/main.cu -O2 -lgdi32 
```
## compile on linux

```sh
g++ main.cpp -o main -O2 -L/usr/X11R6/lib -lm -lpthread -lX11 
```
* with openmp
```sh
g++ main.cpp -o main -O2 -L/usr/X11R6/lib -lm -lpthread -lX11 -fopenmp
```
* with cuda
```sh
!nvcc -o main main.cu -O2 -L/usr/X11R6/lib -lm -lpthread -lX11 
```
