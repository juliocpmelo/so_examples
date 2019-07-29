

#include <iostream>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

static int index = 0;
static bool filho = false;


using namespace std;

void usr1_children_callback(int sig_id){

	cout << "Sou o processo "<< index << " meu PID é " << getpid() << endl;
}

void usr1_parent_callback(int sig_id){

	cout << "Sou o processo PAI meu PID é " << getpid() << endl;
}

int main(){

	int p1 = fork();
	if(p1 == 0){ //processo 1
		signal(SIGUSR1, usr1_children_callback);
		filho = true;
		index = 1;
		while (true);
	}

	int p2 = fork();
	if(p2 == 0){ //processo 2
		signal(SIGUSR1, usr1_children_callback);
		filho = true;
		index = 2;
		while (true);
	}

	int p3 = fork();
	if(p3 == 0){ //processo 3
		signal(SIGUSR1, usr1_children_callback);
		filho = true;
		index = 3;
		while (true);
	}

	int p4 = fork();
	if(p4 == 0){ //processo 4
		signal(SIGUSR1, usr1_children_callback);
		filho = true;
		index = 4;
		while (true);
	}


	signal(SIGUSR1, usr1_parent_callback);
	int pids[] = {p1, p2, p3, p4};
	cout << "Processos criados PIDs" << endl;
	cout << "P0=" << p1 << endl;
	cout << "P1=" << p2 << endl;
	cout << "P2=" << p3 << endl;
	cout << "P3=" << p4 << endl;
	char choice;
	int pindex;
	while(true){//processo pai;
		cout << "Escolha uma opcao s, c, k:" <<endl; 
		cin >> choice;

		switch(choice){
			case 's':
			{
				cout << "Digite o índice do processo que seja parar 0 à 3:"<<endl;
				cin >> pindex;
				cout << "sig stop em processo " << pids[pindex] << endl;
				kill(pids[pindex], SIGSTOP);
				break;
			}
			case 'c':
			{
				cout << "Digite o índice do processo que seja continuar 0 à 3:" <<endl;
				cin >> pindex;
				cout << "sig cont em processo " << pids[pindex] << endl;
				kill(pids[pindex], SIGCONT);
				break;
			}
			case 'k':
			{
				cout << "Digite o índice do processo que seja matar 0 à 3:" <<endl;
				cin >> pindex;
				cout << "sig kill em processo " << pids[pindex] << endl;
				kill(pids[pindex], SIGKILL);
				break;
			}

		
		
		}
		
	
	}
	return 0;
}
