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
	printf("You CANT kill me with ctrl-c\n");
}


/*usos da funcao raise*/
int main(){
	


	printf("Meu PID é %d, just saying\n", getpid());

	signal (SIGINT, callback);
	signal (SIGUSR1, callback2);
	signal (SIGUSR2, callback3);



	raise(SIGINT); //o mesmo que digitar kill -INT PID no console
	while(1);
	return 0;
}
