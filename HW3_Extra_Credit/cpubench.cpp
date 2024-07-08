#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <sys/time.h>
// #include <stdbool.h>
// #include <pthread.h>

#include <CL/sycl.hpp>
#include <oneapi/dpl/random>
using namespace sycl;

#define MSG "* running cpubench with seed %s using %s with size %s and %s threads with debug %s...\n"

#define USAGE "usage: ./cpubench <seed> <type> <size> <threads> <debug> \n" \
"     - seed: 0 \n" \
"     - type: single / double \n" \
"     - size: 1000 / 4000 / 16000 array dimension \n" \
"     - threads: 1 / 2 / 4 \n" \
"     - debug: true / false \n" \

#define MEGABYTES 1024*1024

double min(double a1, double a2) {
	if (a1 < a2) {
		return a1;
	}
	return a2;
}

int DEBUG = false;

int main(int argc, char **argv)
{
	int checksum = 0;
	time_t t;
	srand((unsigned) time(&t));
    if (argc != 6) 
    {
        printf(USAGE);
		printf("type=-1 size=-1 threads=-1 time=-1 throughput=-1 checksum=-1\n");
        exit(1);
    } 
    else 
    {
    	int seed = atoi(argv[1]);
		srand(seed);
    
		int type = -1;
        if(strcmp(argv[2],"single") == 0)
        	type = 0;
        else if(strcmp(argv[2],"double") == 0)
        	type = 1;
        else
        	type = -1;

		int size = atoi(argv[3]);
        int num_threads = atoi(argv[4]);
		int isAuto = num_threads == -1 ? 1 : 0;

        if(strcmp(argv[5],"true") == 0)
        	DEBUG = true;
        else if(strcmp(argv[5],"false") == 0)
        	DEBUG = false;
        else
        {
        	printf("error in DEBUG argument, must be either true or false; exiting...\n");
			printf("seed=%s mode=%s type=%s size=%d threads=%d time=0.0 throughput=0.0 checksum=-2\n",argv[1],argv[2],argv[3],size,num_threads);
			exit(-1);
		}	
		
		if (DEBUG)
    		printf(MSG, argv[1], argv[2], argv[3], argv[4], argv[5]);

		struct timeval start, end;
		// execuate queue for matrix multiplication task
		queue q;
		// the value of matrix is single `int`, 
		if (type == 0)
		{			
			gettimeofday(&start, NULL);
			// we have to use ** to describe two-dimensional matrix
			int** origin1= new int*[size];
			int** origin2= new int*[size];
			int** origin3= new int*[size];
			// initialize matrix, and put random value to input matrix
			for (int i = 0; i < size; i++) {
				origin1[i] = new int[size];
				origin2[i] = new int[size];
				origin3[i] = new int[size];
				for (int j = 0; j < size; j++) {
					origin1[i][j] = (int)((rand()/rand())*10.0);;
					origin2[i][j] = (int)((rand()/rand())*10.0);;
					origin3[i][j] = 0;
				}
			}
			// depend on hardware
			if (isAuto) {
				q.parallel_for(range(size, size), [=](auto index) {
					int i = index[0];
					int j = index[1];

					long sum = 0;
					for (int k = 0; k < size; k++) {
						sum += origin1[i][k] + origin2[k][j];
					}
					origin3[i][j] = sum;
				}).wait();
			// depend on config the number of thread
			} else {
				int dis = size / num_threads;
				// thread
				q.parallel_for(range<1>(num_threads), [=](id<1> index) { 
					int start = index * dis;
					int end = (index + 1) * dis;
					if (end > size) end = size;
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
											origin3[i1][j1] += origin1[i1][k1] + origin2[k1][j1];
										}
									}
								}

							}
						}
					}
				}).wait();
			}
			
			// test
			// for (int i = 0; i < size; i++) {
			// 	for (int j = 0; j < size; j++) {
			// 		std::cout << origin3[i][j] << " ";
			// 	}
			// }
		    gettimeofday(&end, NULL);
		} else if (type == 1) {
			gettimeofday(&start, NULL);
			double** origin1= new double*[size];
			double** origin2= new double*[size];
			double** origin3= new double*[size];
			// // Intialize c_back
			for (int i = 0; i < size; i++) {
				origin1[i] = new double[size];
				origin2[i] = new double[size];
				origin3[i] = new double[size];
				for (int j = 0; j < size; j++) {
					origin1[i][j] = (double)((rand()/rand())*10.0);;
					origin2[i][j] = (double)((rand()/rand())*10.0);;
					origin3[i][j] = 0;
				}
			}
			if (isAuto) {
				q.parallel_for(range(size, size), [=](auto index) {
					int i = index[0];
					int j = index[1];

					double sum = 0;
					for (int k = 0; k < size; k++) {
						sum += origin1[i][k] + origin2[k][j];
					}
					origin3[i][j] = sum;
				}).wait();
			} else {
				int dis = size / num_threads;
				q.parallel_for(range<1>(num_threads), [=](id<1> index) { 
					int start = index * dis;
					int end = (index + 1) * dis;
					if (end > size) end = size;

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
											origin3[i1][j1] += origin1[i1][k1] + origin2[k1][j1];
										}
									}
								}

							}
						}
					}
				}).wait();
			}
		    gettimeofday(&end, NULL);
		}
		
		long double elapsed_time_sec = (((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec)))/1000000.0;
		long double num_giga_ops = 0;
		
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
		num_giga_ops = (size * 1.0 / 1024.0) * (size * 1.0 / 1024.0) * (size * 1.0 / 1024.0); 
			// num_giga_ops = size*size*size*1.0/(MEGABYTES*1024.0);
		long double throughput = num_giga_ops/elapsed_time_sec;
		// printf("num_giga_ops: %Lf, elapsed_time_sec: %Lf throughput: %Lf\n", num_giga_ops, elapsed_time_sec, throughput);
		printf("seed=%s mode=%s type=%s size=%d threads=%d time=%Lf throughput=%Lf checksum=%d\n",argv[1],argv[2],argv[3],size,num_threads,elapsed_time_sec,throughput,checksum);
    }
    return 0;
}