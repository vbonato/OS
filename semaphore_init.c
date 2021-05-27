#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>

int sem_init(sem_t *sem, int pshared, unsigned int value);

sem_t sem;
int pshared;
int ret;
int value;
int main(){
    
    /* initialize a private semaphore */
    pshared = 0;
    value = 1;
    if (sem_init(&sem, pshared, value) != 0){
      printf("Unable to initialize semaphores\n");
    } 
    
    sem_wait(&sem);
    
    //sem_post(&sem);

    printf("step 1\n");

    sem_wait(&sem);
    printf("step 2\n");

    
    return 0;
}