#define _GNU_SOURCE

#include <unistd.h>
#include <stdio.h>
#include <sched.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>

void printPolicy(int sched_policy){

	switch(sched_policy){
	
		case SCHED_OTHER:
			printf("SCHED_OTHER\n");
			break;
		case SCHED_BATCH:
			printf("SCHED_BATCH\n");
			break;
		case SCHED_IDLE:
			printf("SCHED_IDLE\n");
			break;
		case SCHED_RR:
			printf("SCHED_RR\n");
			break;
		case SCHED_FIFO:
			printf("SCHED_FIFO\n");
			break;
		case -1:
			perror("Error on calling function");
			exit(EXIT_FAILURE);
			break;
	}

}

void idlePolicy(){
	struct sched_param param;

	if(sched_getparam(getpid(), &param) == -1){
		perror("ERROR");
		exit(-1);
	}
	
	if(sched_setscheduler(0, SCHED_IDLE, &param) == -1){
		perror("ERROR");
		exit(-1);
	}


	int sched_policy = sched_getscheduler(getpid());

	printPolicy(sched_policy);
	
	printf("Sou o processo %d minha prioridade é %d\n", getpid(), param.sched_priority);
	
	while(1);
}

void fifo_policy(){

	struct sched_param param;

	if(sched_getparam(getpid(), &param) == -1){
		perror("ERROR");
		exit(-1);
	}
	
	param.sched_priority = sched_get_priority_max(SCHED_FIFO);

	/*precisa de permissao de super usuário*/
	if(sched_setscheduler(0, SCHED_FIFO, &param) == -1){
		perror("ERROR");
		exit(-1);
	}


	int sched_policy = sched_getscheduler(getpid());

	printPolicy(sched_policy);
	
	printf("Sou o processo %d minha prioridade é %d\n", getpid(), param.sched_priority);

	while(1);
	/*processo só é interrompido quando chama sched_yield()*/


}

void defaultScheduler(){

	struct sched_param param;
	
	int sched_policy = sched_getscheduler(getpid());

	printPolicy(sched_policy);
	

	if(sched_getparam(getpid(), &param) == -1){
		perror("ERROR");
		exit(-1);
	}


	printf("Sou o processo %d minha prioridade é %d\n", getpid(), getpriority(PRIO_PROCESS,getpid()));


	/*setando a prioridade*/
	/*prioridade varia entre 0(mais prioritario) e 20(menos prioritario)*/
	/*a funcao nice incrementa o valor da prioridade pelo número dado*/
	nice(10);
	printf("Sou o processo %d minha prioridade é %d\n", getpid(), getpriority(PRIO_PROCESS,getpid()));
	
	
	while(1);
	
}

int main(){
	

	struct sched_param param;
	int sched_policy;

	defaultScheduler();



	return 0;
}
