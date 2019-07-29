#include <unistd.h>
#include <stdio.h>
#include <signal.h>

void callback2(int sigNum){
	printf("WUUUT? SIGUSR1!\n");

}
void callback3(int sigNum){
	printf("WUUUT? SIGUSR2!\n");
}

void callback(int sigNum){

	if(sigNum == SIGINT)
		printf("You CANT kill me with ctrl-c\n");
	else if(sigNum == SIGSTOP)
		printf("Will this work?1?\n");
}

int main(){
	


	signal (SIGINT, callback);
	signal (SIGUSR1, callback2);
	signal (SIGUSR2, callback3);

	signal (SIGSTOP, callback); //nao tem efeito pois nan podemos capturar sigstop

	while(1);
	return 0;
}
