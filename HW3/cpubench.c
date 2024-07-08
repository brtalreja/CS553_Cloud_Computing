#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <sys/time.h>
#include <stdbool.h>
#include <pthread.h>
#include <immintrin.h>

#define MSG "* running cpubench with seed %s mode %s using %s with size %s and %s threads with debug %s...\n"

#define USAGE "usage: ./cpubench <seed> <mode> <type> <size> <threads> <debug> \n" \
"     - seed: 0 \n" \
"     - mode: flops / matrix \n" \
"     - type: single / double \n" \
"     - size: 256 / 1024 / 4096 / 16386 -- MegaFlops / array dimension \n" \
"     - threads: 1 / 2 / 4 \n" \
"     - debug: true / false \n" \


#define MEGAFLOPS 1000000
#define MEGABYTES 1024*1024

int DEBUG = false;

struct int_params {
	int start;
	int end;
	int size;
	int*** mat1;
	int*** mat2;
	int*** res;
};

struct double_params {
	int end;
	int start;
	int size;
	double*** mat1;
	double*** mat2;
	double*** res;
};

// matrix multiplication


double min(double a1, double a2) {
	if (a1 < a2) {
		return a1;
	}
	return a2;
}

//MUST MODIFY TO SATISFY ASSIGNMENT BELOW THIS LINE//
//=================================================//

// This function multiplies mat1[][] and mat2[][],
// and stores the result in res[][]
//may want to print periodic status to the screen to verify the rate of progress
void multiply_double(int start, int end, int size, double mat1[size][size], double mat2[size][size], double res[size][size])
{
	int i, j, k;
	int bsize = 16;
	for (i = start; i < end; i += bsize) {
		for (j = 0; j < size; j += bsize) {
			for (k = 0; k < size; k += bsize) {
				int i1s = min(i+bsize, end);
				// block
				for (int i1 = i; i1 < i1s; i1++) {
					int j1s = min(j+bsize, size);
					for (int j1 = j; j1 < j1s; j1++) {
						int k1s = min(k+bsize, size);
						for (int k1 = k; k1 < k1s; k1+=4) {
							// mat2: transpose
							__m256d a = _mm256_loadu_pd(&mat1[i1][k1]);
							// // transpose matrix
							__m256d b = _mm256_loadu_pd(&mat2[j1][k1]);
							__m256d v = _mm256_mul_pd(a, b);
							double * val = (double *) &v;
							res[i1][j1] += (val[0] + val[1] + val[2] + val[3]);
							// res[i1][j1] += mat1[i1][k1] * mat2[j1][k1];
						}
					}
				}

			}
		}
	}
}

void multiply_int(int start, int end, int size, int mat1[size][size], int mat2[size][size], int res[size][size]) {
	int i, j, k;
	int bsize = 16;
	for (i = start; i < end; i += bsize) {
		for (j = 0; j < size; j += bsize) {
			for (k = 0; k < size; k += bsize) {
				int i1s = min(i+bsize, end);
				// block
				for (int i1 = i; i1 < i1s; i1++) {
					int j1s = min(j+bsize, size);
					for (int j1 = j; j1 < j1s; j1++) {
						int k1s = min(k+bsize, size);
						for (int k1 = k; k1 < k1s; k1++) {
							// mat2: transpose
							res[i1][j1] += mat1[i1][k1] * mat2[j1][k1];
							// mat2: transpose
							// _mm_loadu_epi32
							// __m128i a = _mm_loadu_si128((const __m128i_u*)&mat1[i1][k1]);
							// // transpose matrix
							// __m128i b = _mm_loadu_si128((const __m128i_u*)&mat2[j1][k1]);
							// __m128i v = _mm_mul_epi32(a, b);
							// int * val = (int *) &v;
							// res[i1][j1] += (val[0] + val[1] + val[2] + val[3]);
						}
					}
				}

			}
		}
	}
}

void multiply_int_wrapper(void * params) {
	struct int_params *recv_params;
	recv_params = (struct int_params *) params;
	int start = (*recv_params).start;
	int end = (*recv_params).end;
	int size = (*recv_params).size;
	int** mat1 = *((*recv_params).mat1);
	int** mat2 = *((*recv_params).mat2);
	int** res = *((*recv_params).res);
    multiply_int(start, end, size, (int (*)[(int)(size)])mat1, (int (*)[(int)(size)])mat2, (int (*)[(int)(size)])res);
}

void multiply_double_wrapper(void * params) {
	
	struct double_params *recv_params;
	recv_params = (struct double_params *) params;
	int start = (*recv_params).start;
	int size = (*recv_params).size;
	int end = (*recv_params).end;
	double** mat1 = *((*recv_params).mat1);
	double** mat2 = *((*recv_params).mat2);
	double** res = *((*recv_params).res);
	// printf("start: %d, end: %d, size: %d\n", start, end, size);
    multiply_double(start, end, size, (double(*)[(int)(size)])mat1, (double (*)[(int)(size)])mat2, (double (*)[(int)(size)])res);
}


void DEBUG_LOOP(int index, int index2) {
	if (index2 % 1000) {
		printf("current outer loop: %d, inner loop: %d\n", index, index2);
	}
}

void compute_flops_int(void *size)
{
	int index, index2;
	int result;
	int loops = *((int*)size);
	for (index=0;index<loops;index++)
	{
		for (index2=0;index2<MEGAFLOPS;index2++) {
			result = (index2*loops)+1;
		}
	}
	// if (DEBUG)
		// printf("result: %d, size: %d\n",result, loops);
}

void compute_flops_double(void *size)
{
	int index, index2;
	double result;
	int loops = *((int*)size);
	for (index=0;index<loops;index++)
	{
		for (index2=0;index2<MEGAFLOPS;index2++) {
			result = (index2*loops)+1.0;
		}
	}
	// if (DEBUG)
		// printf("result: %lf, size: %d\n",result, loops);
	
}

//=================================================//
//MUST MODIFY TO SATISFY ASSIGNMENT ABOVE THIS LINE//


double compute_checksum_dynamic_double(int size, double res[size][size]){
	if (DEBUG)
	printf("compute_checksum...\n");
	int checksum = 0;
    int i, j;
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
                checksum += (int)res[i][j];
                //if (DEBUG)
                //printf("%d %lf\n", checksum, res[i][j]);
        }
    }
    return checksum;
}

int compute_checksum_dynamic_int(int size, int res[size][size]){
	if (DEBUG)
		printf("compute_checksum_dynamic_int...\n");
	int checksum = 0;
    int i, j;
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
                checksum += res[i][j];
        }
    }
    return checksum;
}

void compute_flops_int_thread(int num_threads, int size) {
	pthread_t ids_t[num_threads];

	for (int i = 0; i < num_threads; i++) {
		pthread_create(&(ids_t[i]), NULL, (void *)&compute_flops_int, (void*)&size);
	}

	for (int i = 0; i < num_threads; i++) {
		pthread_join(ids_t[i], NULL);
	}
}

void compute_flops_double_thread(int num_threads, int size) {
	pthread_t ids_t[num_threads];

	for (int i = 0; i < num_threads; i++) {
		pthread_create(&(ids_t[i]), NULL, (void *)&compute_flops_double, (void*)&size);
	}

	for (int i = 0; i < num_threads; i++) {
		pthread_join(ids_t[i], NULL);
	}
}

void multiply_double_thread(int num_threads, int size, double mat1[size][size], double mat2[size][size], double res[size][size]) {
	pthread_t ids_t[num_threads];
	
	int n = size / num_threads;
	struct double_params *params;
	params = (struct double_params*) malloc(sizeof(struct double_params) * num_threads);

	// printf("num_threads: %d\n", num_threads);
	for (int i = 0; i < num_threads; i++) {
		params[i].mat1 = (double***)&mat1;
		params[i].mat2 = (double***)&mat2;
		params[i].res = (double***)&res;
		params[i].start = i * n;
		if (i == num_threads - 1) {
			params[i].end = size;
		} else {
			params[i].end = i * n + n;
		}
		params[i].size = size;
		pthread_create(&(ids_t[i]), NULL, (void *)&multiply_double_wrapper, (void*)&(params[i]));
	}

	for (int i = 0; i < num_threads; i++) {
		pthread_join(ids_t[i], NULL);
	}
}

void multiply_int_thread(int num_threads, int size, int mat1[size][size], int mat2[size][size], int res[size][size]) {
	pthread_t ids_t[num_threads];
	
	int n = size / num_threads;
	struct int_params *params;
	params = (struct int_params*) malloc(sizeof(struct int_params) * num_threads);

	// printf("num_threads: %d\n", num_threads);
	for (int i = 0; i < num_threads; i++) {
		params[i].mat1 = (int***)&mat1;
		params[i].mat2 = (int***)&mat2;
		params[i].res = (int***)&res;
		params[i].start = i * n;
		if (i == num_threads - 1) {
			params[i].end = size;
		} else {
			params[i].end = i * n + n;
		}
		params[i].size = size;
		// printf("start: %d, size: %d\n", params[i].start, params[i].size);
		pthread_create(&(ids_t[i]), NULL, (void *)&multiply_int_wrapper, (void*)&(params[i]));
	}

	for (int i = 0; i < num_threads; i++) {
		pthread_join(ids_t[i], NULL);
	}
}

void debug_matrix_int (int size, int arr1[size][size], int arr2[size][size]) {
	int i, j;
	if (DEBUG) {
		for (i = 0; i < size; i++) 
		{
			for (j = 0; j < size; j++) 
				printf("%d ", arr1[i][j]); 
			printf("\n");
		}
		printf("\n");

		for (i = 0; i < size; i++) 
		{
			for (j = 0; j < size; j++) 
				printf("%d ", arr2[i][j]); 
			printf("\n");
		}
		printf("\n");
	}
}

void debug_matrix_double (int size, double arr1[size][size], double arr2[size][size]) {
	int i, j;
	if (DEBUG) {
		for (i = 0; i < size; i++) 
		{
			for (j = 0; j < size; j++) 
				printf("%lf ", arr1[i][j]); 
			printf("\n");
		}
		printf("\n");

		for (i = 0; i < size; i++) 
		{
			for (j = 0; j < size; j++) 
				printf("%lf ", arr2[i][j]); 
			printf("\n");
		}
		printf("\n");
	}
}

void debug_matrix_double_result(int size, double arr3[size][size]) {
	if (DEBUG) {	    
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) 
				printf("%lf ", arr3[i][j]); 
			printf("\n");
		}
		printf("\n");
	}
}

int main(int argc, char **argv)
{
	int checksum = 0;
	time_t t;
	srand((unsigned) time(&t));
    if (argc != 7) 
    {
        printf(USAGE);
		printf("mode=-1 type=-1 size=-1 threads=-1 time=-1 throughput=-1 checksum=-1\n");
        exit(1);
    } 
    else 
    {
    	int seed = atoi(argv[1]);
		srand(seed);
    	
		int mode = -1;
        if(strcmp(argv[2],"flops") == 0) {
			mode = 0;
		} else if(strcmp(argv[2],"matrix") == 0) {
        	mode = 1;
		} else {
			mode = -1;
		}
        	

		int type = -1;
        if(strcmp(argv[3],"single") == 0)
        	type = 0;
        else if(strcmp(argv[3],"double") == 0)
        	type = 1;
        else
        	type = -1;


        int size = atoi(argv[4]);
        int num_threads = atoi(argv[5]);

        if(strcmp(argv[6],"true") == 0)
        	DEBUG = true;
        else if(strcmp(argv[6],"false") == 0)
        	DEBUG = false;
        else
        {
        	printf("error in DEBUG argument, must be either true or false; exiting...\n");
			printf("seed=%s mode=%s type=%s size=%d threads=%d time=0.0 throughput=0.0 checksum=-2\n",argv[1],argv[2],argv[3],size,num_threads);
			exit(-1);
		}	
		
		if (DEBUG)
    		printf(MSG, argv[1], argv[2], argv[3], argv[4], argv[5], argv[6]);

		struct timeval start, end;
		
		if (mode == 0 && type == 0)
		{	
			gettimeofday(&start, NULL);
			compute_flops_int_thread(num_threads, size/num_threads);
		    gettimeofday(&end, NULL);
		}
		else if (mode == 0 && type == 1)
		{	
			gettimeofday(&start, NULL);
			compute_flops_double_thread(num_threads, size/num_threads);
		    gettimeofday(&end, NULL);
		}		
		else if (mode == 1 && type == 0)
		{			
			int i, j;//, k;
			int (*arr1)[size] = malloc(sizeof(int[size][size]));
			int (*arr2)[size] = malloc(sizeof(int[size][size]));
			int (*arr3)[size] = malloc(sizeof(int[size][size]));
			// bool STATIC = false;
			if (DEBUG) {
				size_t len = size * size * 3 * sizeof(int);
				printf("allocating %lf GB memory...\n",len*3.0/(1024*1024*1024));
			}

			for (i = 0; i < size; i++)  {
				for (j = 0; j < size; j++) {
					arr1[i][j] = (int)((rand()/rand())*10.0);
					// transpose matrix
					arr2[j][i] = (int)rand()/rand();
					arr3[i][j] = 0;
				}
			}

			// debug_matrix_int(size, arr1, arr2);
			gettimeofday(&start, NULL);
			// multiply_int(0, size, arr1, arr2, arr3);
			multiply_int_thread(num_threads, size, arr1, arr2,arr3);
		    gettimeofday(&end, NULL);
			checksum = compute_checksum_dynamic_int(size, arr3);   
		}
		else if (mode == 1 && type == 1)
		{
			int i, j;//, k;
			double (*arr1)[size] = malloc(sizeof(double[size][size]));
			double (*arr2)[size] = malloc(sizeof(double[size][size]));
			double (*arr3)[size] = malloc(sizeof(double[size][size]));
			// bool STATIC = false;
			
			if (DEBUG) {
				size_t len = size * size * 3 * sizeof(double);
				printf("allocating %lf GB memory...\n",len*3.0/(1024*1024*1024));
			}

			for (i = 0; i < size; i++) {
				for (j = 0; j < size; j++) {
					arr1[i][j] = (double)rand()/rand();
					// arr2[i][j] = (double)rand()/rand();
					// transpose matrix
					arr2[j][i] = (double)rand()/rand();
					arr3[i][j] = 0.0; 
				}
			}
			// debug_matrix_double(size, arr1, arr2);
			gettimeofday(&start, NULL);
			multiply_double_thread(num_threads, size, arr1, arr2, arr3);
		    gettimeofday(&end, NULL);
			checksum = compute_checksum_dynamic_double(size, arr3);
			// debug_matrix_double_result(size, arr3);
		}
		else
		{
			if (DEBUG)
        	{
        		printf(USAGE);
				printf("unrecognized option, exiting...\n");
			}
			else
				printf("seed=%s mode=%s type=%s size=%d threads=%d time=0.0 throughput=0.0 checksum=-6\n",argv[1],argv[2],argv[3],size,num_threads);
				
        	exit(1);
		}

		long double elapsed_time_sec = (((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec)))/1000000.0;
		long double num_giga_ops = 0;
		
		if (size*MEGAFLOPS < 0)
		{
			if (DEBUG)
				printf("error in size, check for overflow; exiting...\n");
			else
				printf("seed=%s mode=%s type=%s size=%d threads=%d time=0.0 throughput=0.0 checksum=-7\n",argv[1],argv[2],argv[3],size,num_threads);
			exit(1);
		}
		if (elapsed_time_sec < 0)
		{
			if (DEBUG)
				printf("error in elapsed time, check for proper timing; exiting...\n");
			else
				printf("seed=%s mode=%s type=%s size=%d threads=%d time=0.0 throughput=0.0 checksum=-8\n",argv[1],argv[2],argv[3],size,num_threads);
			exit(1);
		}
		if (elapsed_time_sec == 0)
		{
			if (DEBUG)
				printf("elapsed time is 0, check for proper timing or make sure to increase amount of work performed; exiting...\n");
			else
				printf("seed=%s mode=%s type=%s size=%d threads=%d time=0.0 throughput=0.0 checksum=-9\n",argv[1],argv[2],argv[3],size,num_threads);
			exit(1);
		}
		if (mode == 0)
			num_giga_ops = size*1000.0/MEGAFLOPS;
		else if (mode == 1)
			num_giga_ops = (size * 1.0 / 1024.0) * (size * 1.0 / 1024.0) * (size * 1.0 / 1024.0); 
			// num_giga_ops = size*size*size*1.0/(MEGABYTES*1024.0);
		long double throughput = num_giga_ops/elapsed_time_sec;
		// printf("num_giga_ops: %Lf, elapsed_time_sec: %Lf throughput: %Lf\n", num_giga_ops, elapsed_time_sec, throughput);
		printf("seed=%s mode=%s type=%s size=%d threads=%d time=%Lf throughput=%Lf checksum=%d\n",argv[1],argv[2],argv[3],size,num_threads,elapsed_time_sec,throughput,checksum);
    }
    return 0;
}