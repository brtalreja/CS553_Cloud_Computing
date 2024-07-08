#include <stdio.h>
#include <string.h>

typedef double double8 __attribute__((vector_size(64)));
double8 Broadcastdouble8(double val){
	double8 broadcast_vector;
	double* broadcast_tester = (double *)&broadcast_vector;
	for(int x = 0; x < 8; x++){
		broadcast_tester[x] = val;
	}
	return broadcast_vector;
}
#define Loaddouble8(PTR) *((const double8 *)(PTR));

#define A(i, j) matrix1[(j)*8 + (i)]
#define B(i, j) matrix2[(j)*size + (i)]
#define C(i, j) result[(j)*size + (i)]

void multiply_matrices(int size, double* matrix1, double* matrix2, double* result)
{
	double8 csum[size][size / 8];
    //Making sure that the array is initialized with zeros
	for(int x = 0; x < size; x++){
		for(int y = 0; y < size / 8; y ++){
			double8 test = {0.0};
			double8 *refresh = (&csum[x][y]);
			*refresh = test;
		}
	}
	// Perform the DOT product
	for(size_t bi = 0; bi < size; bi++){
		for (size_t ai = 0; ai < size / 8; ai++) {
			double8 aa = Loaddouble8(&A(bi * size, ai));
			for (size_t ci = 0; ci < size; ci++) {
				double8 bb = Broadcastdouble8(B(bi, ci));
				csum[ci][ai] += aa * bb;
			}
		}
	}
	for (size_t bi = 0; bi < size; bi++) {
    	for (size_t ai = 0; ai < size; ai++) {
			double * resultcpy = (double*)&csum[bi];
			result[bi*size + ai] = resultcpy[ai];
    	}
  	}
}

