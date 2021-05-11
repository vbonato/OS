#include <omp.h>
#include <stdio.h>
#include <time.h>

void delay(int seconds)
{
    int start = clock();
    // wait n seconds
    while (((clock()-start)/CLOCKS_PER_SEC)<seconds);
          
}
 


int main(int argc, char *argv[])
{
        //printf("Hello from process: %d\n", omp_get_thread_num());
	printf("Max of thread = %d\n", omp_get_max_threads());
	#pragma omp parallel
	{
	  printf("I am a parallel region\n");
	}
        
        for (int i=0; i<10; i++) {  
          delay(1);
          printf("%d\n",i);
        } 
  
        printf("\n\n");
        #pragma omp parallel for 
        for (int i=0; i<10; i++) {  
          delay(1);
          printf("%d\n",i);
        } 


	return 0;
}
