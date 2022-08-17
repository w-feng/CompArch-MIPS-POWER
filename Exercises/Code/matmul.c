#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define num 64 //matrix size
//#include <valgrind/callgrind.h>
//clock_t start, end;
//double cpu_time_used; //cannot use time.h in syscall emulation mode of GEM5. Must check the time in stats.txt 

void matmul_unopt(int**  mat_A , int** mat_B, int** product_unopt, int N)
{
    for (int i = 0; i < N; i++) {
        for (int  k= 0; k < N; k++) {
            //#pragma GCC unroll 8
            for (int j = 0; j < N;j++)
			{
                product_unopt[i][j] += mat_A[i][k] * mat_B[k][j];
			} 
		}
    }
    return;
}
 
void matmul_opt(int** mat_A , int** mat_B, int** product_opt, int N)
{
     for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++)
                product_opt[i][j] += mat_A[i][k] * mat_B[k][j];
        }
    }
    return;
}


void correctness_test(int** product_unopt, int** product_opt, int N){
     
      int threshold = 0; 
      //(10^-6), ideally both should be equal but giving this room because of the single precison inting points)
      for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
	    //if( fabsf( fabs(product_unopt[i][j]) - fabsf(product_opt[i][j])) > threshold){
		//printf("Optimized implementation is incorrect\n");
		return;
               }
	     }
       printf("The implementation is correct\n");
       return;

}


int main (int argc, char *argv[])

{
  
  //srand((unsigned int)time(NULL));
  //srand won't work in the SE mode of GEM5. Going to just initialize matrices using iterative variables
  //read the size of the square matrix from command line 
  //if (argc > 1)
  //{
  //	char *a = argv[1];
  // 	num = atoi(a);
  //}
  //else 
  //setting  matrix size to 64 for now. 
   	  
  
  
  printf("Generating matrices of size %d * %d \n",num,num);

  int **mat_A = (int **)malloc(num * sizeof(int *)); 
  int **mat_B = (int **)malloc(num * sizeof(int *));
  int **product_unopt = (int **)malloc(num * sizeof(int *));
  //int **product_opt = (int **)malloc(num * sizeof(int *));
  
  for (int i=0; i<num; i++){ 
    mat_A[i] = (int *)malloc(num * sizeof(int)); 
	mat_B[i] = (int *)malloc(num * sizeof(int));
	product_unopt[i] = (int *)malloc(num * sizeof(int));
	//product_opt[i] = (int *)malloc(num * sizeof(int));
  }

  //
  for( int i=0; i<num; i++){
	for(int j=0; j<num; j++){
		mat_A[i][j]= i-j;
		mat_B[i][j]= 1;
        product_unopt[i][j]=0;  
    //    product_opt[i][j]=0;    
	}
  }
  
  printf("computing the results\n");

  //compute the product
  //TODO: add timers here to measure execution time
  // start = clock();
  //CALLGRIND_START_INSTRUMENTATION;
    matmul_unopt(mat_A, mat_B, product_unopt, num);
  //CALLGRIND_STOP_INSTRUMENTATION;
  // end = clock();
  // cpu_time_used = ((end - start)) / CLOCKS_PER_SEC;
  //printf("order i j k took %f seconds to execute \n", cpu_time_used);
   
   //start = clock();
   // matmul_opt(mat_A, mat_B, product_unopt, num);
   //end = clock();
   //cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
   // printf("order j k i took %f seconds to execute \n", cpu_time_used);
   

  //return 0;
  //TODO: add timers here to measure execution time
  //matmul_opt(mat_A, mat_B, product_opt, num);
  //correctness_test(product_unopt, product_opt, num);

 
 // printf("printng result \n");
 // for (int i = 0; i < num; i++) {
 //       for (int j = 0; j < num; j++) {	
 // 		printf("%f ", product_opt[i][j]);
 // 		}
 // 	 printf("\n");
 //  	}
  
  for (int i=0; i<num; i++)
  {
  
   free(mat_A[i]);
   free(mat_B[i]);
   free(product_unopt[i]);
   //free(product_opt[i]);
  }

   free(mat_A);
   free(mat_B);
   free(product_unopt);
   //free(product_opt);
  return (0);

}
