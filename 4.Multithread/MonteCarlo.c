#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define THREAD_NUM 8192

float in_circle = 0;

float PointGenerator(){
		int rand_value = rand();
		float point_value = rand_value / (float) RAND_MAX;

		return point_value;
}

void *MonteCarlo(){
		float x = PointGenerator();
		float y = PointGenerator();

		//printf("(%.2f, %.2f)", x, y);

		if((x * x) + (y * y) < 1){
				in_circle+=1;
		}
}

int main(){
		pthread_t threads[THREAD_NUM];
		int ret, i;
		float pi;

		srand(time(NULL));

		for(i = 0; i < THREAD_NUM; i++){
				pthread_create(&threads[i], NULL, MonteCarlo, NULL);
		}
		for(i = 0; i < THREAD_NUM; i++){
				pthread_join(threads[i], NULL);
		}		

		pi = 4 * in_circle / THREAD_NUM;

		printf("The number of point which is in circle: %.0f\n", in_circle);
		printf("The value of PI is : %.5f\n", pi);
}
