#include <stdio.h>
#include <math.h>
#include <complex.h>

#ifndef FUJITAFFT_H
#define FUJITAFFT_H

#define INF 999999999
#define EVEN 0
#define ODD 1

void fujitaFFT(double complex*, double complex*, int); //my original FFT function
void fujitaIFFT(double complex*, double complex*, int); //my original IFFT function
void initializeIndex(int*, int, int); //initialize the index of FFT array
double complex calcFFT(double complex*, int, int, int, int, int); //recursive function to calculate FFT
double complex calcIFFT(double complex*, int, int, int, int, int); //recursive function to calculate IFFT
int calcEvenIndex(int, int, int, int); //calculate the index of even array
int calcOddIndex(int, int, int, int); //calculate the index of odd array
double complex eulerFunction(double); //e^(i*(2PInk/N))

#endif