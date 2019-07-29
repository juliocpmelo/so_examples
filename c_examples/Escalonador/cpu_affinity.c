#define _GNU_SOURCE

#include <unistd.h>
#include <stdio.h>
#include <sched.h>
#include <stdlib.h>

/*esse código cria quantos processos?*/
/*qual a saída que será exibida no console?*/

#define errExit(msg)    do { perror(msg); exit(EXIT_FAILURE); } while (0)

int main(){
	

	cpu_set_t set;
	CPU_ZERO(&set);

	/*voce pode usar 'lscpu' para verficar o numero de cpus online*/	
	int num_cpus = sysconf(_SC_NPROCESSORS_ONLN);
	int cpuno = sched_getcpu();

	
	int parentCpu, childCpu;
	
	printf("O número de cpus online é %d\n", num_cpus);
	
	int parent = fork();
	
	if(parent){
		parentCpu = 0;
		CPU_SET(parentCpu, &set);
		if (sched_setaffinity(getpid(), sizeof(set), &set) == -1)
			errExit("sched_setaffinity");				
	}
	else{
		childCpu = 1;
		CPU_SET(childCpu, &set);
		if (sched_setaffinity(getpid(), sizeof(set), &set) == -1)
			errExit("sched_setaffinity");				
	}

	printf("Sou o processo %d executando na cpu %d\n", getpid(), sched_getcpu());

	int count  = 0;
	while(count < 10){
		if(cpuno != sched_getcpu()){
			printf("Processo %d Estava na cpu %d e agora estou na cpu %d\n", getpid(),cpuno, sched_getcpu());
			cpuno = sched_getcpu();
		}
		sleep(1);
		count ++;
	}

	return 0;
}
