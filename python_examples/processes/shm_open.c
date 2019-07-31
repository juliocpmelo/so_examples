#include <stdio.h> 
#include <stdlib.h>
#include <errno.h> 
#include <unistd.h> 
#include <string.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <signal.h>

int shm_fd;
void *mapped_memory_ptr = NULL;

void SIGINT_hanler(int sig_val){
	if(mapped_memory_ptr != NULL){
		printf("desalocando as estruturas\n");
		shm_unlink("test");
		munmap(mapped_memory_ptr, 50);
	}
	exit(0);
}

int main(){
	
	signal(SIGINT, SIGINT_hanler);

	/*traz a memoria compartilhada para dentro do espaco de enderecamento do programa*/
	shm_fd = shm_open("test", O_RDWR | O_CREAT, 0777);

	if (shm_fd == -1) {
		perror("shm_open");
		return 1;
	}
	int rc = ftruncate(shm_fd, 50);
	if (rc){
		perror("erro truncando o arquivo");
		return 1;
	}

  mapped_memory_ptr = mmap((void *)0, (size_t)50, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
	if (mapped_memory_ptr == MAP_FAILED){
		perror("erro mapeando a memória");
		return 1;
	}

	close(shm_fd);

	char s[50];
	int cont = 0;
	while (1){
		sprintf(s, "teste de escrita %d", cont);
		cont ++;
		strcpy((char *)mapped_memory_ptr, s);
		sleep(1);
	}


		
	return 0;

}
