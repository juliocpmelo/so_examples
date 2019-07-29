
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

#include <iostream>
#include <vector>

using std::cout;
using std::endl;


std::vector<int> buffer;


void* producer(void * thread_arg){



	while(1){

		cout << "Sou o produtor, produzo numeros aleatorios" <<endl;
		if(buffer.size() > 10)
			buffer.clear();

		buffer.push_back(rand());
		sleep(1);

	}

	return NULL;
}

void* consumer(void * thread_arg){
	while(1){
	
		cout << "Sou o consumidor, exibo os números produzidos pelo produtor" <<endl;
		
		std::vector<int> copy = buffer;
		for(int i=0; i<copy.size(); i++)
			cout << copy[i] << " ";

		cout << endl;
		sleep(1);

	}

	return NULL;
}

int main(int argc, char** argv){


	pthread_t thread_id, thread_id2;

	pthread_create(&thread_id, NULL, consumer, NULL);
	pthread_create(&thread_id2, NULL, producer, NULL);

	pthread_join(thread_id, NULL); //espera pela thread 

	return 0;
}
