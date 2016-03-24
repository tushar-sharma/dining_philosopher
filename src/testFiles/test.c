#include <stdio.h>
#include "mysemaphore.h"
#include <stdlib.h>
#include <sys/wait.h>
#define DESC 2 

/* 
 * test program
 * checking semaphore behaviour
 */
int main(int argc, char **argv)
{
    int semid, status;

    printf("%s\n", argv[1]);

    //down sempahore
    wait((int *)up_semaphore(DESC, SEM_DOWN));

    sleep(3);
    //up sempahore
    if ((semid = up_semaphore(DESC, SEM_UP)) == -1) {
        perror("down semaphore");
	exit(EXIT_FAILURE);
    }

    sleep(1);
    //close semaphore
    if ((semid = create_semaphore(DESC, INHERIT, SEM_CLOSE)) == -1) {
        perror("closing semaphore");
	exit(EXIT_FAILURE);
    }

    return 0;
}
