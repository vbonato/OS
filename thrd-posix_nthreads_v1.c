/**
 * A pthread program illustrating how to
 * create a simple thread and some of the pthread API
 * This program implements the summation function where
 * the summation operation is run as a separate thread.
 *
 * Most Unix/Linux/OS X users
 * gcc thrd.c -lpthread
 *
 * Figure 4.11
 *
 * @author Gagne, Galvin, Silberschatz
 * Operating System Concepts  - Tenth Edition
 * Copyright John Wiley & Sons - 2018
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 4

int sum; /* this data is shared by the thread(s) */


void delay(int seconds){	
	int start = clock();
	// wait n seconds
    	while (((clock()-start)/CLOCKS_PER_SEC)<seconds);         
}


/**
 * The thread will begin control in this function
 */
void *runner(void *param){
	int i, upper = atoi(param);
	sum = 0;
	if (upper > 0) {
		for (i = 1; i <= upper; i++)
			sum += i;
	}
	delay(10);
        printf("sum = %d\n",sum);
	pthread_exit(0);
}




int main(int argc, char *argv[])
{
pthread_t workers[NUM_THREADS]; /* n thread identifiers */
//printf("tid = %lu\n",tid);

pthread_attr_t attr; /* set of attributes for the thread */

delay(1);

if (argc != 5) {
	fprintf(stderr,"usage: a.out <integer value>\n");
	/*exit(1);*/
	return -1;
}

if (atoi(argv[1]) < 0) {
	fprintf(stderr,"Argument %d must be non-negative\n",atoi(argv[1]));
	/*exit(1);*/
	return -1;
}

/* get the default attributes */
pthread_attr_init(&attr);

/* create the thread */
pthread_create(&workers[0],&attr,runner,argv[1]);
pthread_create(&workers[1],&attr,runner,argv[2]);
pthread_create(&workers[2],&attr,runner,argv[3]);
pthread_create(&workers[3],&attr,runner,argv[4]);


/* now wait for the thread to exit */
pthread_join(workers[0],NULL);
pthread_join(workers[1],NULL);
pthread_join(workers[2],NULL);
pthread_join(workers[3],NULL);


//printf("sum = %d\n",sum);
}


