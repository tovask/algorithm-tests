// gcc frog_jumps.c -o frog_jumps.elf -Wall && ./frog_jumps.elf > frog_jumps.out.csv

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void print_array(double *data, long size) {
	long i;
	for(i=0;i<size;i++){
		printf("%6.3f ",data[i]);
	}
	printf("\n");
}

void compare_summarization() {
	double *data;
	long i,count,step;
	double sum;
	
	for (count = 2; count < (long)1000*1000*1000*10; count*=2) {
		
		printf("%ld\t", count);
		
		data =  malloc( sizeof(*data) * count );
		fprintf( stderr, "count: %ld, memory: %lu byte\n", count, sizeof(*data) * count);
		
		for(i=0;i<count;i++){
			data[i] = (double) rand() / RAND_MAX;
		}
		
		sum = 0;
		for(i=0;i<count;i++){
			sum += data[i];
		}
		printf("%.15f\t", sum);
		
		for (step = 1; step < count; step*=2) {
			//print_array(data, count);
			for ( i = 0; i+step < count; i+=2*step) {
				//printf("%2ld %2ld: %f + %f\n", i, i+step, data[i] , data[i+step]);
				data[i] += data[i+step];
				//data[i+step] = 0;
			}
		}
		//print_array(data, count);
		printf("%.15f\t", data[0]);
		
		printf("%.15f\n", data[0] - sum);
		
		free(data);
	}
}

void precision_test() {
	long i, count = (long)1000*1000*1000*10;
	double sum = 0;
	for(i=0;i<count;i++){
		sum += (double) rand() / RAND_MAX;
		if ( i%(count/100) == 0) {
			printf("%f\n", sum);
			fprintf( stderr, " %ld ", 100*i/count);
		}
	}
	printf("sum: %f\n", sum);
}

int main(void) {
	srand(time(NULL));
	
	compare_summarization();
	
	//precision_test();
	
	return 0;
}

