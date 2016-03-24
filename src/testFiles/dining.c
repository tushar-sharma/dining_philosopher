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

/*
THINKING is 0
HUNGRY is 1 
EATING is 2 
*/
typedef enum {THINKING, HUNGRY, EATING} phil_state;

phil_state state[NUM_PHILOSOPHERS];

/* 
 * think for random time
 */
void think(void)
{
    sleep(rand() % 11 + 5); 
}

/* 
 * eat for random time
 */
void eat(void)
{
    sleep(rand() % 3 + 1);
}

/* 
 * check if the process is Hungry (need resource)
 * and its neighbours are not EATING (using resources) 
 */
void test(int i)
{
    if (state[i] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING) {
        state[i] = EATING;
	up_semaphore(statemtx, id, SEM_UP);
    }
}

/* 
 * If a process doesn't have its neighbours using forks (or resources)
 * then aquire a semaphore and use resource
 */
void take_forks(int id) 
{ 
    up_semaphore(testmtx, SEM_DOWN);

    state[id] = HUNGRY;
    test(id);

    up_semaphore(testmtx, SEM_UP);

    up_semaphore(statemtx, SEM_DOWN);
}

/* 
 * After a process is done executing, it can release resources and lock
 */
void put_forks(int i) 
{
    state[i] = THINKING;
    up_semaphore(i, SEM_DOWN);
    test(LEFT);
    test(RIGHT);
    up_semaphore(i, SEM_UP);
}

/* 
 * it randomly schedules different philosophers 
 */
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
