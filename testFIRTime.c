#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <complex.h>
#include <time.h>

#include "fujitaFFT.h"
#include "fujitaFIR.h"

//Program to measure CPUtime.
int main(){

    int x_n, h_n;
    double real, imag;

    double complex* h;
    double complex* x;
    double complex* y;

    clock_t start, end;

    int fftSize;

    printf("set h_n and x_n\n");
    scanf("%d%d", &h_n, &x_n);

    fftSize = calcFFTSize(h_n+x_n-1);

    h = (double complex*)malloc(fftSize * sizeof(double complex));
    x = (double complex*)malloc(fftSize * sizeof(double complex));
    y = (double complex*)malloc(fftSize * sizeof(double complex));

    memset(h, 0, fftSize * sizeof(double complex));
    memset(x, 0, fftSize * sizeof(double complex));
    memset(y, 0, fftSize * sizeof(double complex));


    printf("imput h[] values\n");
    
    for(int i=0; i<h_n; i++){
        scanf("%lf%lf", &real, &imag);
        h[i] = real + imag*I;
    }

    printf("imput x[] values\n");
    
    for(int i=0; i<x_n; i++){
        scanf("%lf%lf", &real, &imag);
        x[i] = real + imag*I;
    }

    start = clock();
    normalFIR(h, h_n, x, x_n, y);
    end = clock();
    printf("CPU time:%f\n", (double)(end - start) / CLOCKS_PER_SEC);

    start = clock();
    fujitaFIR(h, h_n, x, x_n, y);
    end = clock();
    printf("CPU time:%f\n", (double)(end - start) / CLOCKS_PER_SEC);

    free(h);
    free(x);
    free(y);

    return 0;
}