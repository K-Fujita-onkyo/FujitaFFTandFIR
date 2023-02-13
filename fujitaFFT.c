#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <complex.h>
#include "fujitaFFT.h"

//my original FFT function
void fujitaFFT(double complex* x, double complex* X, int N){
    double complex* wx;//Save the already calculated X_eo[k].
    int wn = N * (int)log2((double)N*2);//Index of wx.
    wx = (double complex*)malloc(sizeof(double complex) * wn); //Array to save calculated values
    int index[N]; // Array containing the sorted indices

    for(int i=0; i<N; i++) index[i] = i;
    initializeIndex(index, 0, N); //Initialize in the order after splitting

    //init wx
    for(int i=0; i < wn; i++){
        if(i<N){
            wx[i] = x[index[i]];
        }else{
            wx[i] = INF;
        }
    }

    for(int k=0; k < N; k++){
        X[k] = calcFFT(wx, N, k, wn - N + k, N, EVEN);
    }

    free(wx);
}

//my original IFFT function
void fujitaIFFT(double complex* X, double complex* x, int N){

    double complex* mX;//Save the already calculated X_eo[k].
    int mk = N * (int)log2((double)N*2);//Index of mX.
    mX = (double complex*)malloc(sizeof(double complex) * mk); //Array to save calculated values
    int index[N]; // Array containing the sorted indices

    for(int i=0; i<N; i++) index[i] = i;
    initializeIndex(index, 0, N);
    
    //init mX
    for(int i=0; i < mk; i++){
        if(i<N){
            mX[i] = X[index[i]];
        }else{
            mX[i] = INF;
        }
    }

    //calculate IFFT
    for(int n=0; n < N; n++){
        x[n] = (1.0/(double)N) * calcIFFT(mX, N, n, mk - N + n, N, EVEN);
    }
    free(mX);
}

//initialize the index of FFT/IFFT array
void initializeIndex(int* indexArray, int beginning, int end){

    if(end-beginning < 2) return;

    int even = 0;
    int odd = (end-beginning) / 2;
    int temp[end-beginning];

    for(int i=beginning; i<end; i++){
        if(i%2 == 0){
            temp[even++] = indexArray[i];
        }else{
            temp[odd++] = indexArray[i];
        }
    }

    for(int i=beginning; i<end; i++){
        indexArray[i] = temp[i-beginning];
    }

    initializeIndex(indexArray, beginning, (end+beginning) / 2);
    initializeIndex(indexArray, (end+beginning) / 2, end);
}

//recursive function to calculate FFT
double complex calcFFT(double complex* wx, int N, int k, int index, int logStratum, int evenOrOdd){

    if(logStratum!=N && wx[index]!=INF){
        if(evenOrOdd==EVEN || evenOrOdd == ODD && (k<logStratum)){
            return wx[index];
        }else {
            return -wx[index];
        }
    }

    int evenNum = calcEvenIndex(N, k, logStratum, index%N);
    int oddNum = calcOddIndex(N, k, logStratum, index%N);

    if(evenOrOdd == EVEN){
        //Save X_e[k]
        wx[index] = calcFFT(wx, N, k, evenNum, logStratum/2, EVEN) + calcFFT(wx, N, k, oddNum, logStratum/2, ODD);
        return wx[index];

    }else{

        //Save W_N^nk*X_o[k]
        wx[index] = eulerFunction((-2*M_PI*k)/(2*logStratum))*(calcFFT(wx, N, k, evenNum, logStratum/2, EVEN) + calcFFT(wx, N, k, oddNum, logStratum/2, ODD));
        return wx[index];
    }
}


//recursive function to calculate IFFT
double complex calcIFFT(double complex* mX, int N, int n, int index, int logStratum, int evenOrOdd){
    if(logStratum!=N && mX[index]!=INF){
        if(evenOrOdd==EVEN || evenOrOdd == ODD && (n<logStratum)){
            return mX[index];
        }else {
            return -mX[index];
        }
    }

    int evenNum = calcEvenIndex(N, n, logStratum, index%N);
    int oddNum = calcOddIndex(N, n, logStratum, index%N);

    if(evenOrOdd == EVEN){
        //Save X_e[k]
        mX[index] = calcIFFT(mX, N, n, evenNum, logStratum/2, EVEN) + calcIFFT(mX, N, n, oddNum, logStratum/2, ODD);
        return mX[index];

    //Calculate odds array
    }else{

        //Save W_N^nk*X_o[k]
        mX[index] = eulerFunction((2*M_PI*n)/(2*logStratum))*(calcIFFT(mX, N, n, evenNum, logStratum/2, EVEN) + calcIFFT(mX, N, n, oddNum, logStratum/2, ODD));
        return mX[index];
    }
}


//calculate the index of even array
int calcEvenIndex(int N,  int k, int logStratum, int columnIndex){
    int h = columnIndex;
    if(k >= logStratum/2) h -= logStratum/2;
    return N * (int)log2((double)logStratum/2) + h;
}

//calculate the index of odd array
int calcOddIndex(int N, int k, int logStratum, int columnIndex){
    int h = columnIndex;
    if(k >= logStratum/2) h -= logStratum/2;
    return N * (int)log2((double)logStratum/2) + h + logStratum/2;
}

//e^(i*(2PInk/N))
double complex eulerFunction(double angle){
    //e^(i*angle) = cos(angle) + sin(angle)*i
    return cos(angle) + sin(angle)*I;
}