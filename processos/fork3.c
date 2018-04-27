#include <unistd.h>
#include <stdio.h>

/*esse código cria quantos processos?*/
/*qual a saída que será exibida no console?*/

int main(){
	


	printf("Sou o pai com o pid %d, se eu morrer os outros morrem\n", getpid());

	int childPid;


	childPid = fork();

	printf("Sou o pid %d, executando a linha %d\n", getpid(), __LINE__);

	childPid = fork();
	
	printf("Sou o pid %d, executando a linha %d\n", getpid(), __LINE__);

	childPid = fork();
	
	printf("Ficarei bloqueado no while, por favor me mate com kill -9 %d\n",getpid());

	while(1) sleep(1);

	return 0;
}
