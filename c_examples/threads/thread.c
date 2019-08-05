#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

void* thread_func(void * thread_arg){
	while(1){
		printf("Sou o processo %d na thread %d e estou executando em paralelo\n", getpid(), (int)pthread_self());
		sleep(1);
	}
	return NULL;
}

int main(int argc, char** argv){


	pthread_t thread_id;

	pthread_create(&thread_id, NULL, thread_func, NULL);

	for(;;){
			printf("Sou o processo principal, %d, e estou executando em paralelo à thread %d \n", getpid(), (int)thread_id);
			sleep(1);
	
	}


	pthread_join(thread_id, NULL); //espera pela thread 
	return 0;
}
