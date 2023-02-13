#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <complex.h>
#include "fujitaFFT.h"


//This program verifies that the FFT works properly.
int main(){

    int n;//the index of array x and X
    int wn; //the index of array wx ()
    double real, comp;
    double complex* x;//input x[n];

    double complex* X;//output X[n];

    double complex* ix;


    printf("Please enter the number of elements: ");
    scanf("%d", &n);

    x = (double complex*)malloc(sizeof(double complex) * n);
    X = (double complex*)malloc(sizeof(double complex) * n);
    ix = (double complex*)malloc(sizeof(double complex) * n);
    printf("Please enter the elements of x[n] in the following!! \n");
    printf("For example\n***If you wanna enter 1-3i, prease enter 1 -3***\n***If you wanna enter i, prease enter 0 1***\n\n");

    for(int i=0; i<n; i++){
        scanf("%lf%lf", &real, &comp);
        x[i] = real + comp*I;
        X[i] = -1;
    }
    
   fujitaFFT(x, X, n);

    printf("\n\nFFT result....\n\n");

    for(int i=0; i<n; i++){

        printf("X[%d] = ",i);
        printf("%.2f", creal(X[i]));

        if(cimag(X[i])<0){
            printf("%.2fi\n", cimag(X[i]));
        }else{
            printf("+%.2fi\n", cimag(X[i]));
        }
    }


    fujitaIFFT(X, ix, n);

    printf("\n\nIFFT result....\n\n");

        for(int i=0; i<n; i++){

        printf("ix[%d] = ",i);
        printf("%.2f", creal(ix[i]));

        if(cimag(ix[i])<0){
            printf("%.2fi\n", cimag(ix[i]));
        }else{
            printf("+%.2fi\n", cimag(ix[i]));
        }
    }


    return 0;
}