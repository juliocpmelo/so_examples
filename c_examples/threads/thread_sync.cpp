
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

#include <iostream>
#include <vector>

using std::cout;
using std::endl;


std::vector<int> buffer;

pthread_mutex_t buffer_mutex;

void* producer(void * thread_arg){

	struct thread_param * param_val = (struct thread_param *) thread_arg;


	while(1){

		cout << "Sou o produtor, produzo numeros aleatorios" <<endl;
		pthread_mutex_lock(&buffer_mutex);
		if(buffer.size() > 10)
			buffer.clear();
		buffer.push_back(rand());
		pthread_mutex_unlock(&buffer_mutex);
		sleep(1);

	}

	return NULL;
}

void* consumer(void * thread_arg){
	while(1){
	
		cout << "Sou o consumidor, exibo os números produzidos pelo produtor" <<endl;
		
		pthread_mutex_lock(&buffer_mutex);
		for(int i=0; i<buffer.size(); i++)
			cout << buffer[i] << " ";
		buffer.clear();
		pthread_mutex_unlock(&buffer_mutex);
		
		cout << endl;
		sleep(1);

	}

	return NULL;
}

int main(int argc, char** argv){


	pthread_t thread_id, thread_id2;

	pthread_mutex_init(&buffer_mutex, NULL);

	pthread_create(&thread_id, NULL, consumer, NULL);
	pthread_create(&thread_id2, NULL, producer, NULL);

	pthread_join(thread_id, NULL); //espera pela thread 

	return 0;
}
