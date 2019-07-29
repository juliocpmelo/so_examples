
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#include <iostream>
#include <vector>

using std::cout;
using std::endl;

struct thread_param{

	int value;
	std::string test_string;
	std::vector<std::string> test_vector;
};

struct thread_return{
	int value;
	std::string test_string;
	std::vector<std::string> test_vector;
};

void* thread_func(void * thread_arg){

	struct thread_param * param_val = (struct thread_param *) thread_arg;


	printf("Sou o processo %d na thread %d e estou executando em paralelo\n", getpid(), (int)pthread_self());

	cout<<"Meus arugmentos foram "<<param_val->value<<endl;
	cout<<"Meus arugmentos fora "<<param_val->test_string<<endl;
	cout<<"Meus arugmentos fora "<<param_val->test_vector[0]<<endl;

	sleep(1);


	/*precisa usar memória dinâmica, porque?*/
	struct thread_return *ret = new struct thread_return;
	ret->value = param_val->value;
	ret->test_string = param_val->test_string;
	ret->test_vector.push_back(param_val->test_vector[0]);



	return ret;
}

int main(int argc, char** argv){


	pthread_t thread_id;

	struct thread_param par;

	par.value = 10;
	par.test_string = "hello Thread";
	par.test_vector.push_back("Thread rox, processes sux");

	pthread_create(&thread_id, NULL, thread_func, &par);

	/*for(;;){
			printf("Sou o processo principal, %d, e estou executando em paralelo à thread %d\n", getpid(), (int)thread_id);
			sleep(1);
	
	}*/


	struct thread_return* ret;
	pthread_join(thread_id, (void**)&ret); //espera pela thread 

	cout<<"Recebi de retorno"<<ret->value<<endl;
	cout<<"Recebi de retorno"<<ret->test_string<<endl;
	cout<<"Recebi de retorno "<<ret->test_vector[0]<<endl;

	delete ret;

	return 0;
}
