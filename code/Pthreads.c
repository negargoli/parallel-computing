
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/times.h>
#include <sys/time.h>
#include <string.h>
#include <limits.h>
#include <time.h>
#define NUM 1024
#define MAX 6

typedef struct {
	int upper_bound,lower_bound;
} t_data;

	float *input;
    float *output;
	////////-----------------------------uncomment this for test --------------------------/////
	//float *output_test;



void *thread_Linear_function(void* args){
	int x,y,t;
	int num;
        float weight[MAX];
        
       weight[0] = -2.92722222;
        weight[1] = 1.66666667;
        weight[2] = -0.23809524;
        weight[3] = 0.03968254;
        weight[4] = -0.00496031;
        weight[5] = 0.00031746;
	t_data *a = (t_data *)args;
	for ( num = 0 ; num < 5 ; num++ ){
		for ( x = a->lower_bound ; x < a->upper_bound ; x++ ){
			for ( t = 5 ; t < NUM-5 ; t++ ){
				for ( y = 0 ; y < NUM ; y++ ){
output[t*(NUM)+x*NUM+y] = weight[0]*input[t*(NUM)+x*NUM+y]+ weight[1]*(input[(t-1)*NUM+x*NUM+y] + input[(t+1)*NUM+x*NUM+y])
                                                 + weight[2]*(input[(t-2)*NUM+x*NUM+y] + input[(t+2)*NUM+x*NUM+y])+ weight[3]*(input[(t-3)*NUM+x*NUM+y] + input[(t+3)*NUM+x*NUM+y])
                                                 + weight[4]*(input[(t-4)*NUM+x*NUM+y] + input[(t+4)*NUM+x*NUM+y])+weight[5]*(input[(t-5)]*NUM+x*NUM+y + input[(t+5)*NUM+x*NUM+y]);




/*					output[t*NUM+x*NUM+y] = weight[0]*(input[t*NUM+x*NUM+y]) + weight[1]*(input[(t-1)*NUM*x*NUM+y] + input[(t+1)*NUM+x*NUM+y]);/*
				    				 + weight[2]*(input.Image[t-2][x][y] + input.Image[t+2][x][y])+ weight[3]*(input.Image[t-3][x][y] + input.Image[t+3][x][y])
				    				 + weight[4]*(input.Image[t-4][x][y] + input.Image[t+4][x][y])+weight[5]*(input.Image[t-5][x][y] + input.Image[t+5][x][y]);*/
				}
			}
		}
	}
}

int main(int argc, char *argv[]) {

time_t start,end;
double duration = 0;
float ratio;
clock_t start1 , end1;
int THREADS;
t_data *arguments;
t_data remain_arg;

int i,j,k,block_size;
input  =( float *)malloc(NUM*NUM*NUM* sizeof(float));
output  =( float *)malloc(NUM*NUM*NUM* sizeof(float));
/////////////////--------------------------un comment this for testing -----------------------/////////////////
		//output  =( float *)malloc(NUM*NUM*NUM* sizeof(float));

struct timeval etstart, etstop;
struct timezone tzdummy;
clock_t etstartt, etstoptt;
unsigned long usecstart, usecstop;

	if ( argc == 2 ){

		THREADS = atoi(argv[1]);
		//int i;
		pthread_t *thread_handle,remain;
		thread_handle=(pthread_t *)malloc(sizeof(pthread_t)*THREADS);
		arguments = (t_data *) malloc (sizeof(t_data)*THREADS);

       
        for ( i = 0 ; i < NUM ; i++ ){
                for ( j = 0 ; j < NUM ; j++ ){
                        for ( k = 0 ; k < NUM ; k++ ){
                                input[i*NUM+j*NUM+k] = ((float)rand()/(float)RAND_MAX)*10;
                        }
                }
        }
        block_size = NUM/THREADS;
        for ( i = 0 ; i < THREADS-1 ; i++ ){
                arguments[i].lower_bound = i*block_size;
                arguments[i].upper_bound = (i+1)*block_size;
        }
        if ( NUM% THREADS != 0){
                remain_arg.lower_bound = THREADS*block_size;
                remain_arg.upper_bound = NUM;
        }

		time(&start);
                start1= clock();
		gettimeofday(&etstart, &tzdummy);
                for (i = 0 ; i < THREADS ; i++ ) {
			int ret = pthread_create(&thread_handle[i],0,thread_Linear_function,&arguments[i]);
		
		void* exit_status;
		for ( i = 0 ; i < THREADS; i++ ){
			pthread_join(thread_handle[i],&exit_status);
		}
		
                gettimeofday(&etstop, &tzdummy);
                
		
                usecstart = (unsigned long)etstart.tv_sec*1000000+etstart.tv_usec;
                usecstop = (unsigned long)etstop.tv_sec*1000000+etstop.tv_usec;

         printf("EX time = %g ms.\n", (float)(usecstop-usecstart)/(float)1000);  
		
		
          
	}
	else{
		printf("argc error\n");
	}
	
		       /////////////////////----------------------------un comment this for testing -----------------------//////////////////////
/*

    static float weight[6];
        weight[0] = -2.92722222;
        weight[1] = 1.66666667;
        weight[2] = -0.23809524;
        weight[3] = 0.03968254;
        weight[4] = -0.00496031;
        weight[5] = 0.00031746;
	for ( num = 0 ; num < 5 ; num++ ){
		for ( t = 5 ; t < NUM-5 ; t++ ){
			for ( x = 0 ; x < NUM ; x++ ){
				for ( y = 0 ; y < NUM ; y++ ){
					output_test[t*(NUM)+x*NUM+y] = weight[0]*input[t*(NUM)+x*NUM+y]+ weight[1]*(input[(t-1)*NUM+x*NUM+y] + input[(t+1)*NUM+x*NUM+y])
				    		 + weight[2]*(input[(t-2)*NUM+x*NUM+y] + input[(t+2)*NUM+x*NUM+y])+ weight[3]*(input[(t-3)*NUM+x*NUM+y] + input[(t+3)*NUM+x*NUM+y])
				    		 + weight[4]*(input[(t-4)*NUM+x*NUM+y] + input[(t+4)*NUM+x*NUM+y])+weight[5]*(input[(t-5)]*NUM+x*NUM+y + input[(t+5)*NUM+x*NUM+y]);
				if ( output_test[t*(NUM)+x*NUM+y] != output[t*(NUM)+x*NUM+y])	
                printf("ERROR")	;				
				}
			}
		}
	}
}

*/		
	return 0;


}
