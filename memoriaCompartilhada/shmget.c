
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#define SHMSZ     200


int main(){


	char c;
	int count;
	int shmid;
	key_t key;
	char *shm, *s;

	key = 5680;

	/*cria uma posi¢ao de memoria compartilhada com tamanho 27 bytes*/
	if ((shmid = shmget(key, SHMSZ, IPC_CREAT | 0777)) < 0) {
		perror("shmget");
		return 1;
	}

	/*traz a memoria compartilhada para dentro do espaco de enderecamento do programa*/
	shm = shmat(shmid, NULL, 0);

	if (shm == (void*) -1) {
		perror("shmat");
		return 1;
	}
	
	/*foi alocada uma regiao com 27 bytes*/
	s = shm;

	for (c = 'a', count = 0; c <= 'z'; c++, count++){
		s[count] = c;
  }
	s[count+1] = NULL; //poe um null para indicar o fim da mensagem

	
	//while (*shm != '*')
	//	sleep(1);

	/*desanexa a posicao de memoria*/
	if(shmdt(shm) != 0){
		perror("shmdet");
		return 1;
	}

	if(shmctl(key, IPC_RMID, NULL) != 0){
		perror("shmctl");
		return 1;
	}


	printf("%s terminado\n",__FILE__);

	return 0;

}
