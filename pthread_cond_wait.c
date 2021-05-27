/* CELEBP22 */                                   
#define _OPEN_THREADS                                                           
#include <pthread.h>                                                            
#include <stdio.h>                                                              
#include <time.h>                                                               
#include <unistd.h>                                                             
                                                                                
pthread_cond_t cond[2];                                                            
pthread_mutex_t mutex;                                                          
                                                                                
int footprint = 0;                                                              
                                                                                
void *thread(void *arg) {                                                       
  time_t T;                                                                     
                                                                                
  if (pthread_mutex_lock(&mutex) != 0) {                                        
    perror("pthread_mutex_lock() error");                                       
    exit(6);                                                                    
  }                                                                             
  time(&T);                                                                     
  printf("starting wait at %s", ctime(&T));                                     
  footprint++;                                                                  
                                                                                
  //This function blocks until the condition is signaled. 
  //The function atomically releases the associated mutex lock before blocking, and atomically acquires the mutex again before returning.
  if (pthread_cond_wait(&cond[0], &mutex) != 0) {                                  
    perror("pthread_cond_timedwait() error");                                   
    exit(7);                                                                    
  }                                                                             
  time(&T);                                                                     
  printf("wait over at %s", ctime(&T));                                         
}                                                                               


main() {                                                                        
  pthread_t thid;                                                               
  time_t T;                                                                     
  struct timespec t;                                                            
                                                                                
  if (pthread_mutex_init(&mutex, NULL) != 0) {                                  
    perror("pthread_mutex_init() error");                                       
    exit(1);                                                                    
  }                                                                             
                                                                                
  if (pthread_cond_init(&cond[0], NULL) != 0) {                                    
    perror("pthread_cond_init() error");                                        
    exit(2);                                                                    
  }                                                                             
                                                                                
  if (pthread_create(&thid, NULL, thread, NULL) != 0) {                         
    perror("pthread_create() error");                                           
    exit(3);                                                                    
  }                                                                             
                                                                                
  while (footprint == 0)                                                        
    sleep(1);                                                                   
                                                                                
  puts("IPT is about ready to release the thread");                             
  sleep(2);                                                                     
                                                                                
  if (pthread_cond_signal(&cond[0]) != 0) {                                        
    perror("pthread_cond_signal() error");                                      
    exit(4);                                                                    
  }                                                                             
                                                                                
  if (pthread_join(thid, NULL) != 0) {                                          
    perror("pthread_join() error");                                             
    exit(5);                                                                    
  }                                                                             
}   