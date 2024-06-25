# FUM_MP_ParallelProject
Ferdowsi University of Mashhad parallel programming course projects.

this project applying [Gaussian blur](https://en.wikipedia.org/wiki/Gaussian_blur) filter on input image and using [CImg](https://cimg.eu/) C++ Library for loading and showing the image.

## OpenMP manual (FA)
* [GaussianBlurFilter_OpenMP Manual (FA).pdf](https://drive.google.com/file/d/1HQMde9PUsr3o8a41i-FR32kIKHcdM4qy/view?usp=share_link)
## Requirements
* [imagemagick](https://imagemagick.org/script/download.php)

## CUDA version Google Colab
* [FUM_MP_ParallelProject.ipynb](https://colab.research.google.com/drive/1SLtdS1veZZU5Fy9zX8lLAZk5o5ogKmJu?usp=sharing)

## OpenMP version Google Colab
* [FUM_MP_ParallelProject_OMP.ipynb](https://colab.research.google.com/drive/1PRm7uHeRAj7twGjJM3vUPogBlruiHw9B?usp=sharing)

## compile on windows 
```sh
g++ .\main.cpp -o .\main -O2 -lgdi32
```
* with openmp
```sh
g++ .\main.cpp -o .\main -O2 -lgdi32 -fopenmp
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

 cd to CudaCode directory
```sh
make
```
