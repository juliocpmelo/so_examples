#include <stdio.h>
#include <signal.h>

/*esse programa mata o PID que ele receber como argumento do main*/

int main(int argc, char **argv){

	if(argc == 2 && atoi(argv[1]) != 0){
		printf("Vou matar %s\n", argv[1]);
		kill(atoi(argv[1]), SIGKILL); //obs raise(signal) == kill (getpid(), signal)
	}
	else
		printf("Usage ./a.out <pid>\n");

	return 0;
}
