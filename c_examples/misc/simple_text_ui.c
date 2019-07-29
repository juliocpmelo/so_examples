#include <unistd.h>
#include <poll.h>
#include <stdio.h>

int main()
{
	/*IGNOREM ESSA LINHA DE CÓDIGO, POR ENQUANTO*/
	struct pollfd mypoll = { STDIN_FILENO, POLLIN|POLLPRI };

	char t = 'a';

	//gambiarra para retirar a necessidae do ENTER (só funciona no gnome)
	system ("/bin/stty raw"); 

	int x=10, y=10;
	while(1){

		/*desenha o tabuleiro e cursor*/
		int i,j;
		y = y + 1;
		y = y % 20;

		for (i=0;i<40; i++)
			printf("*");
		printf("\n\r");
		for (j=0;j<20; j++){ //coordenadas de y
			for (i=0;i<40; i++){ //coordenadas de x
				if(i==0 || i == 39)
					printf("*");
				else
					if(i==x && j==y)
						printf("+");
					else
						printf(" ");
			}
			printf("\n\r");
		}
		for (i=0;i<40; i++)
			printf("*");
		printf("\n\r");


		/*espera o comando específico*/
		printf("Digite o Comando (a ou d):\r\n");
		
		if( poll(&mypoll, 1, 200) ) //espera 200 ms para executar as linhas abaixo
		{
			read(STDIN_FILENO, &t, 1);
			//printf("Read string - %c\n", t);
			fflush(stdin);

			if(t=='a')
				x--;
			if(t=='d')
				x++;
			
			t='\0'; //evita manter o valor de t em todas as iteracoes
		}

		system("clear"); //limpa o console
	}

	return 0;
}
