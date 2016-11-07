#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include <omp.h>
#define PARALLEL_NUM 8192

/* Compile: gcc -fopenmp -O MonteCarlo_OpenMP.c -o MonteCarlo */

/* Last modified at 2016/11/8 00:10 by Tommy */

float PointGenerator(){
		int rand_value = rand();
		float point_value = rand_value / (float) RAND_MAX;

		return point_value;
}

void MonteCarlo(float *in_circle){
		float x = PointGenerator();
		float y = PointGenerator();

		//printf("(%.1f, %.1f) ", x, y);

		if((x * x) + (y * y) < 1){
				#pragma omp atomic
				*in_circle+=1;
		}
}

int main(){
		int ret, i;
		float in_circle = 0;

		srand(time(NULL));

		#pragma omp for
		for(i = 0; i < PARALLEL_NUM; i++){
				MonteCarlo(&in_circle);
		}
		
		printf("The value of PI is : %.5f\n", 4 * in_circle / PARALLEL_NUM);

		return 0;
}
