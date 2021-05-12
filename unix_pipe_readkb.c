/**
 * Example program demonstrating UNIX pipes.
 *
 * Figures 3.21 & 3.22
 *
 * @author Silberschatz, Galvin, and Gagne
 * Operating System Concepts  - Tenth Edition
 * Copyright John Wiley & Sons - 2018
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

#define BUFFER_SIZE 25
#define READ_END	0
#define WRITE_END	1

int main(void)
{
	char write_msg[BUFFER_SIZE] = "Greetings";
	char read_msg[BUFFER_SIZE];
	pid_t pid;
	int fd[2];

       
	/* create the pipe */
	if (pipe(fd) == -1) {
		fprintf(stderr,"Pipe failed");
		return 1;
	}

	/* now fork a child process */
	pid = fork();

	if (pid < 0) {
		fprintf(stderr, "Fork failed");
		return 1;
	}

	if (pid > 0) {  /* parent process */
		/* close the unused end of the pipe */
		close(fd[READ_END]);

		while(1){
		  /* write to the pipe */
		  fgets(write_msg, sizeof write_msg, stdin);
		  write(fd[WRITE_END], write_msg, strlen(write_msg)+1); 
                }

       		/* close the write end of the pipe */
		close(fd[WRITE_END]);
	}
	else { /* child process */
		/* close the unused end of the pipe */
		close(fd[WRITE_END]);

                int n,cnt = 0; 
		while(cnt < 4){
                  /* read from the pipe */
		  n = read(fd[READ_END], read_msg, BUFFER_SIZE);
                  //printf("n = %d\n",(n-2));
                  if(n > 0){
                    printf("child read %s\n",read_msg);
                    cnt++;
		  }	
                    
		}

		/* close the write end of the pipe */
		close(fd[READ_END]);
	}

	return 0; //sai sem esperar o pai
}
