#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <sys/wait.h>
#include "mysemaphore.h"
#define DESC 2 

/* Checking dining philsopher */ 
int main(void)
{
    int semid, status, foo, bar; 
    pid_t pid1, pid2;

    char *argv[] = {"test","Hello! I have executed exev()", NULL };
    char *envp[] = {NULL};

    //allocate resources and initialize semaphore
    if((semid = create_semaphore(DESC, NOT_INHERIT, SEM_UNCLOSE)) == -1) {
        perror("unable to create semaphore");
	exit(-1);
    }

    pid1 = fork(); //create a new child process

    if (pid1 < 0) {
        perror("unable to fork");
	exit(EXIT_FAILURE);
    }

    else if (pid1 == 0) { //child process
        
        //inheriting semaphore
        if((semid = create_semaphore(DESC, INHERIT, SEM_UNCLOSE)) == -1) {
            exit(-1);
        }

        status = execve("./test", argv, envp); 
        exit(status);
     }

    else { //parent process
         sleep(1);
	 pid2 = fork(); //create another child process

         switch (pid2) {

         case -1: 
	 	perror("unable to fork");
		exit(EXIT_FAILURE);
		break;

         case 0:
	     //inherit semaphore
             if((semid = create_semaphore(DESC, INHERIT, SEM_UNCLOSE)) == -1) {  
                 exit(-1);
             }
             
             //down semaphore
	     wait((int *)up_semaphore(DESC, SEM_DOWN));

	     //up semaphore
             if ((semid = up_semaphore(DESC, SEM_UP)) == -1) {
                 perror("up semaphore ");
		 exit(EXIT_FAILURE);
	     }

            if((semid = create_semaphore(DESC, INHERIT, SEM_CLOSE)) == -1) {
                 perror("unable to close semaphore");
                 exit(-1); 
             }

             exit(EXIT_SUCCESS);

  	 default:
             if((semid = create_semaphore(DESC, NOT_INHERIT, SEM_CLOSE)) == -1) {
                 perror("unable to close semaphore");
                 exit(-1); 
             }

	     exit(EXIT_SUCCESS);
	 }
    }
    return 0;
}
