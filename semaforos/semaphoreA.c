
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>


#define KEY (1492)

void main()
{
	int id; /* Number by which the semaphore is known within a program */

	union semun {
		int val;
		struct semid_ds *buf;
		ushort * array;
	} argument;

	argument.val = 0;

	id = semget(KEY, 1, 0666 | IPC_CREAT);

	if(id < 0)
	{
		fprintf(stderr, "Unable to obtain semaphore.\n");
		return;
	}

	if( semctl(id, 0, SETVAL, argument) < 0)
	{
		fprintf( stderr, "Cannot set semaphore value.\n");
	}
	else
	{
		fprintf(stderr, "Semaphore %d initialized.\n", KEY);
	}
	while(1);
}

