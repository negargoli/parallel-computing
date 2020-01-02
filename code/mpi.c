
//#include <iostream>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <mpi.h>
#include <math.h>
#include <sys/types.h>
#include <sys/times.h>
#include <sys/time.h>
#include <string.h>
#include <limits.h>
#include <time.h>



#define NUM 1024



float *input;
float *output;
////////-----------------------------uncomment this for test --------------------------/////
	//float *output_test;



int main (int argc, char **argv)
{
        struct timeval etstart, etstop;
        struct timezone tzdummy;
        clock_t etstartt, etstoptt;
        unsigned long usecstart, usecstop;
	
	
	int num_process,rank;
	int i,j,k,l,x,t,y; //Variables for loops
	int num;
	time_t start,end;
	double duration = 0;

	int start_point,end_point;

	int partition_row;
	int extra_row;
	
	
        input  =( float *)malloc(NUM*NUM*NUM* sizeof(float));
        output  =( float *)malloc(NUM*NUM*NUM* sizeof(float));
		/////////////////--------------------------un comment this for testing -----------------------/////////////////
		//output  =( float *)malloc(NUM*NUM*NUM* sizeof(float));
	float weight[6];

	weight[0] = -2.92722222;
	weight[1] = 1.66666667;
	weight[2] = -0.23809524;
	weight[3] = 0.03968254;
    weight[4] = -0.00496031;
	weight[5] = 0.00031746;


	float *pointer_temp;
	int buffer[10];
	MPI_Status status;
	
	
	MPI_Init(&argc, &argv); //initialize MPI operations
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &num_process);
	
	if ( num_process > 1 )
	{
	partition_row = NUM /(num_process-1);
	extra_row = NUM % (num_process-1);
	}


	if ( num_process > 1 )
	{
		if ( rank == 0 )
		{
                   for ( i = 0 ; i < NUM ; i++ ){
                      for ( j = 0 ; j < NUM ; j++ ){
                        for ( k = 0 ; k < NUM ; k++ ){
                                input[i*NUM+j*NUM+k] = ((float)rand()/(float)100)*10;
                                                     }
                                                  }
                        }
                        

                        for ( i = 1 ; i < num_process ; i++ )
                        {
                                start_point = partition_row*(i-1);
                                pointer_temp =  input+start_point*NUM*NUM;
                                MPI_Send(pointer_temp,partition_row*NUM*NUM,MPI_FLOAT,i,0,MPI_COMM_WORLD);
                        }
                        start_point = partition_row*(num_process-1);
                        end_point = start_point + extra_row;

			time(&start);
			//printf("Here we are in Master process and we have %d Slaves\n", num_process-1 );
	                gettimeofday(&etstart, &tzdummy);		
			for ( num = 0 ; num < 5 ; num++ )
			 for ( x = start_point ; x < end_point ; x ++ )
				for ( t = 5 ; t < NUM-5 ; t++ )
					for ( y = 0 ; y < NUM ; y++ )
						output[t*(NUM)+x*NUM+y] = weight[0]*input[t*(NUM)+x*NUM+y]+ weight[1]*(input[(t-1)*NUM+x*NUM+y] + input[(t+1)*NUM+x*NUM+y])
                                                 + weight[2]*(input[(t-2)*NUM+x*NUM+y] + input[(t+2)*NUM+x*NUM+y])+ weight[3]*(input[(t-3)*NUM+x*NUM+y] + input[(t+3)*NUM+x*NUM+y])
                                                 + weight[4]*(input[(t-4)*NUM+x*NUM+y] + input[(t+4)*NUM+x*NUM+y])+weight[5]*(input[(t-5)]*NUM+x*NUM+y + input[(t+5)*NUM+x*NUM+y]);


			//i = 2;
			for ( i = 1 ; i < num_process ; i++ )
			{
				start_point = partition_row*(i-1);
				pointer_temp = 	output+start_point*NUM*NUM;
				MPI_Recv(pointer_temp,partition_row*NUM*NUM,MPI_FLOAT,i,i,MPI_COMM_WORLD,&status);
			}
                        gettimeofday(&etstop, &tzdummy);
			time(&end);
			
                        usecstart = (unsigned long)etstart.tv_sec*1000000+etstart.tv_usec;
                        usecstop = (unsigned long)etstop.tv_sec*1000000+etstop.tv_usec;
                     
                        printf("EX time = %g ms.\n", (float)(usecstop-usecstart)/(float)1000);
               
		}
		else
		{
			start_point = partition_row*(rank-1);
			end_point = start_point + partition_row;
                        MPI_Recv(input+start_point*NUM*NUM,partition_row*NUM*NUM,MPI_FLOAT,0,0,MPI_COMM_WORLD,&status);  
//                     printf(" start : %d , end: %d , rank : %d\n" , start_point , end_point , rank);
			for ( num = 0 ; num < 5 ; num++ )
			 for ( x = start_point ; x < end_point ; x ++ )
				for ( t = 5 ; t < NUM-5 ; t++ )
					for ( y = 0 ; y < NUM ; y++ )
						output[t*(NUM)+x*NUM+y] = weight[0]*input[t*(NUM)+x*NUM+y]+ weight[1]*(input[(t-1)*NUM+x*NUM+y] + input[(t+1)*NUM+x*NUM+y])
                                                 + weight[2]*(input[(t-2)*NUM+x*NUM+y] + input[(t+2)*NUM+x*NUM+y])+ weight[3]*(input[(t-3)*NUM+x*NUM+y] + input[(t+3)*NUM+x*NUM+y])
                                                 + weight[4]*(input[(t-4)*NUM+x*NUM+y] + input[(t+4)*NUM+x*NUM+y])+weight[5]*(input[(t-5)]*NUM+x*NUM+y + input[(t+5)*NUM+x*NUM+y]);

			
			pointer_temp = 	output+start_point*NUM*NUM;
			MPI_Send(pointer_temp,partition_row*NUM*NUM,MPI_FLOAT,0,rank,MPI_COMM_WORLD);
			

		}
	}
	else
	{
		printf("Run this program mode multi process mode\n");
	}
	
	MPI_Finalize();
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
