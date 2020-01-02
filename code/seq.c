
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/times.h>
#include <sys/time.h>
#include <string.h>
#include <limits.h>
#include <time.h>
#define  NUM 1024
#define SFNUM 6


float *input;
float *output;

void Initialize(){
	int i,j,k;
	for ( i = 0 ; i < NUM ; i++ ){
		for ( j = 0 ; j < NUM ; j++ ){		
                	for ( k = 0 ; k < NUM ; k++ ){
				input[i*NUM+j*NUM+k] = ((float)rand()/(float)1024)*10;
			}
		}
	}
}

void seq_Linear_function(){
	int x,y,t,num; 
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
					output[t*(NUM)+x*NUM+y] = weight[0]*input[t*(NUM)+x*NUM+y]+ weight[1]*(input[(t-1)*NUM+x*NUM+y] + input[(t+1)*NUM+x*NUM+y])
				    		 + weight[2]*(input[(t-2)*NUM+x*NUM+y] + input[(t+2)*NUM+x*NUM+y])+ weight[3]*(input[(t-3)*NUM+x*NUM+y] + input[(t+3)*NUM+x*NUM+y])
				    		 + weight[4]*(input[(t-4)*NUM+x*NUM+y] + input[(t+4)*NUM+x*NUM+y])+weight[5]*(input[(t-5)]*NUM+x*NUM+y + input[(t+5)*NUM+x*NUM+y]);
				}
			}
		}
	}
}



int main(void) {
        time_t start,end;
        clock_t start1, end1;
        struct timeval etstart, etstop;
        struct timezone tzdummy;
        clock_t etstartt, etstoptt;
        unsigned long usecstart, usecstop;
//        long long int size1 = NUM*NUM;
  //      long long int size=size1*NUM;
        double duration = 0;
        input  =( float *)malloc(NUM*NUM*NUM* sizeof(float));
        output  =( float *)malloc(NUM*NUM*NUM* sizeof(float));
	Initialize();
	
	gettimeofday(&etstart, &tzdummy);
        seq_Linear_function();
        gettimeofday(&etstop, &tzdummy);


	usecstart = (unsigned long)etstart.tv_sec*1000000+etstart.tv_usec;
        usecstop = (unsigned long)etstop.tv_sec*1000000+etstop.tv_usec;

         printf("EX time = %g ms.\n", (float)(usecstop-usecstart)/(float)1000);
     
        return 0;

}
