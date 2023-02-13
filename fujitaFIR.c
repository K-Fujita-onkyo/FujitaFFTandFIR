#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <complex.h>
#include "fujitaFFT.h"
#include "fujitaFIR.h"
#include <time.h>

void fujitaFIR(double complex* h, int hSize, double complex* x, int xSize, double complex* y){

    double complex* H;// H[k]
    double complex* X;// X[k]
    double complex* Y;// Y[k]
    int fftSize = calcFFTSize(hSize + xSize - 1);

    H = (double complex*)malloc(fftSize * sizeof(double complex));
    X = (double complex*)malloc(fftSize * sizeof(double complex));
    Y = (double complex*)malloc(fftSize * sizeof(double complex));

    memset(H, 0, fftSize * sizeof(double complex));
    memset(X, 0, fftSize * sizeof(double complex));
    memset(Y, 0, fftSize * sizeof(double complex));

    fujitaFFT(h, H, fftSize);
    fujitaFFT(x, X, fftSize);

    for(int k=0; k<fftSize; k++){
        Y[k] = H[k]*X[k];
    }

    fujitaIFFT(Y, y, fftSize);

    free(H);
    free(X);
    free(Y);
}

int calcFFTSize(int n){
    int fftSize;
    for(fftSize=2; fftSize<n; fftSize*=2);
    return fftSize;
}

void normalFIR(double complex* h, int hSize, double complex* x, int xSize, double complex* y){

    int convSize = hSize + xSize - 1;

    //calculate conv
    for(int i=0; i<convSize; i++){
        y[i] = 0;
        for(int k=0; k<hSize; k++){
            if(i-k<0||i-k>=xSize) continue;
            y[i] += h[k]*x[i-k];
        }
    }
}