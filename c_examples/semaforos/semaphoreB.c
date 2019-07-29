#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#define KEY (1492)

void main()
{
	int id;  /* Internal identifier of the semaphore. */
	struct sembuf operations[1];

	int retval; /* Return value from semop() */

	id = semget(KEY, 1, 0666);
	if(id < 0)
	{
		fprintf(stderr, "Program sema cannot find semaphore, exiting.\n");
		return;
	}

	printf("Program sema about to do a V-operation. \n");

	operations[0].sem_num = 0;
	//operations[0].sem_op = 1; //UP operation
	operations[0].sem_op = -1; //Down operation
	operations[0].sem_flg = 0;

	retval = semop(id, operations, 1);

	if(retval == 0)
	{
		printf("Successful V-operation by program semb.\n");
	}
	else
	{
		printf("sema: V-operation did not succeed.\n");
		perror("REASON");
	}
}
