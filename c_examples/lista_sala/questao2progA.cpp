
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>


#include <iostream>
using namespace std;

int main(){


	char c;
	int count=0;
	
	int shmid1, shmid2;
	key_t key1, key2;
	void *shm;
	char *char_vec;
	int *int_vec;

	/*keys tem que ser diferentes*/
	key1 = 5680;
	/*segmento de memoria compartilhada 1, buffer de 10 char*/
	if ((shmid1 = shmget(key1, sizeof(char)*10, IPC_CREAT | 0777)) < 0) {
		perror("shmget");
		return 1;
	}

	
	/*keys tem que ser diferentes*/
	key2 = 5681;
	/*segmento de memoria compartilhada 2, buffer de 10 int*/
	if ((shmid2 = shmget(key2, sizeof(int)*10, IPC_CREAT | 0777)) < 0) {
		perror("shmget");
		return 1;
	}

	
	
	
	/*attach do segmento 1*/
	shm = shmat(shmid1, NULL, 0);
	if (shm == (void*) -1) {
		perror("shmat");
		return 1;
	}
	char_vec = (char*)shm;


	/*attach do segmento 2*/
	shm = shmat(shmid2, NULL, 0);
	if (shm == (void*) -1) {
		perror("shmat");
		return 1;
	}
	int_vec = (int*) shm;



	while(1){
		
		char_vec[count] = 'a'; 
		int_vec[count] = count; 

		/*imprime os vetores*/
		cout << "[ ";
		for(int i=0; i< 10; i++){
		
			cout << int_vec[i] << " ";
		}
		cout << "]";
		cout << endl;
		cout << "[ ";
		for(int i=0; i< 10; i++){
		
			cout << char_vec[i] << " ";
		}
		cout << "]";
		cout << endl;
		
		count = (count + 1)%10;
		sleep(1);
	}


	return 0;

}
