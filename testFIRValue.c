#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <complex.h>

#include "fujitaFFT.h"
#include "fujitaFIR.h"

//The program checks if the value is accurate.
int main(){

    int x_n, h_n;
    double real, imag;

    double complex* h;
    double complex* x;
    double complex* y1;
    double complex* y2;

    int fftSize;

    scanf("%d%d", &h_n, &x_n);

    fftSize = calcFFTSize(h_n+x_n-1);

    h = (double complex*)malloc(fftSize * sizeof(double complex));
    x = (double complex*)malloc(fftSize * sizeof(double complex));
    y1 = (double complex*)malloc(fftSize * sizeof(double complex));
    y2 = (double complex*)malloc(fftSize * sizeof(double complex));

    memset(h, 0, fftSize * sizeof(double complex));
    memset(x, 0, fftSize * sizeof(double complex));
    memset(y1, 0, fftSize * sizeof(double complex));
    memset(y2, 0, fftSize * sizeof(double complex));
    
    for(int i=0; i<h_n; i++){
        scanf("%lf%lf", &real, &imag);
        h[i] = real + imag*I;
    }
    
    for(int i=0; i<x_n; i++){
        scanf("%lf%lf", &real, &imag);
        x[i] = real + imag*I;
    }

    printf("%d\n", h_n+x_n-1);
    normalFIR(h, h_n, x, x_n, y1);
    for(int i=0; i<h_n+x_n-1; i++){
        printf("%.3f %.3f\n", creal(y1[i]), cimag(y1[i]));
    }
    fujitaFIR(h, h_n, x, x_n, y2);
    for(int i=0; i<h_n+x_n-1; i++){
        printf("%.3f %.3f\n", creal(y2[i]), cimag(y2[i]));
    }

    free(h);
    free(x);
    free(y1);
    free(y2);

    return 0;
}