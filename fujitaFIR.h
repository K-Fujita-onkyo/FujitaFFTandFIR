#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <complex.h>
#include "fujitaFFT.h"
#include <time.h>


#ifndef FUJITAFIR_H
#define FUJITAFIR_H

void fujitaFIR(double complex*, int, double complex*, int, double complex*); //my original Fast FIR filter
int calcFFTSize(int); //calculate fft size from conv size
void normalFIR(double complex*, int, double complex*, int, double complex*); //a normal FIR filter

#endif
