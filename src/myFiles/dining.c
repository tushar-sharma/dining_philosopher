/* Dining Philosopher Problem
 * By Tushar Sharma
 */

#include "mysemaphore.h"
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_PHILOSOPHERS 3  //number of philosopher
#define MAX_TIME 10
/*#define THINKING 0
#define HUNGRY 1 
#define EATING 2 
*/

typedef enum {THINKING, HUNGRY, EATING} phil_state;

phil_state state[NUM_PHILOSOPHERS];

void think(void)
{
    sleep(rand() % 11 + 5); 
}

void eat(void)
{
    sleep(rand() % 3 + 1);
}

void test(int i)
{
    if (state[i] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING) {
        state[i] = EATING;
	up_semaphore(statemtx, id, SEM_UP);
    }
}

void take_forks(int id) 
{ 
    up_semaphore(testmtx, SEM_DOWN);

    state[id] = HUNGRY;
    test(id);

    up_semaphore(testmtx, SEM_UP);

    up_semaphore(statemtx, SEM_DOWN);
}

void put_forks(int i) 
{
    state[i] = THINKING;
    up_semaphore(i, SEM_DOWN);
    test(LEFT);
    test(RIGHT);
    up_semaphore(i, SEM_UP);
}

void philosopher()
{
    int id;

    for (id = 0; id < NUM_PHILOSOPHERS - 1 && fork(); i++) {
        srand(time(NULL) + id);

	while (time(NULL) < MAX_TIME) {
	    think();
	    take_forks(id);
	    eat();
	    put_forks(id);
	}
    }
}

int main(int argc, char **argv)
{
    int i;
    pid_t pid;

    pid = fork();
 
    switch(pid) {
    
    case -1:
    	perror("unable to fork");
	exit(EXIT_FAILURE);
	break;

    case 0:
    	//child process
        philosopher();
        break;

    default:
    	//parent process
    }
    return 0;
}
