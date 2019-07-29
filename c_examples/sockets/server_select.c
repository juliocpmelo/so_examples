/*
** selectserver.c -- a cheezy multiperson chat server
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define PORT "9034"   // port we're listening on

// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int main(void)
{

		/*conjunto de checagem para as conexoes*/
    fd_set master;
    fd_set read_fds;
    /*numero maximo de file descriptors*/
		int fdmax; 

    int server_socket;
    int newfd; 
    struct sockaddr_storage remoteaddr; 
    socklen_t addrlen;

    char buf[256]; 
		int nbytes;

		char remoteIP[INET6_ADDRSTRLEN];

		int yes=1;
		int i, j, rv;

		FD_ZERO(&master);
		FD_ZERO(&read_fds);

		server_socket = socket(AF_INET, SOCK_STREAM, 0);
		if (server_socket < 0) { 
			perror("Creating socket");
			exit(-1);
		}

		setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));

	
		struct sockaddr_in serv_addr;
		serv_addr.sin_family = AF_INET;
		serv_addr.sin_addr.s_addr = INADDR_ANY;
		serv_addr.sin_port = htons(5555);
		/*bind cria um servico na máquina corrente na porta especificada*/
	
		if (bind(server_socket, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
			close(server_socket);
			perror("bind");
			exit(-1);
		}

		// listen
		if (listen(server_socket, 10) == -1) {
			perror("listen");
			exit(3);
		}

		//adiciona o socket na lista de sockets 
		FD_SET(server_socket, &master);

		// guarda o número do maior file descriptor
		fdmax = server_socket; 

		for(;;) {
			read_fds = master; // copia a lista

			/*select bloqueia até que qualquer um dos sockets na lista receba uma requisicao*/
			if (select(fdmax+1, &read_fds, NULL, NULL, NULL) == -1) {
				perror("select");
				exit(4);
			}

			/*se desbloqueou, entao podemos iterar na lista e verificar qual foi o requerente*/
			for(i = 0; i <= fdmax; i++) {
				if (FD_ISSET(i, &read_fds)) { //testa se o elemento atual está marcado como "requisicao recebida" 
					if (i == server_socket) { //se for o server_socket

						/*só pode ter sido uma chamada de connect pelo cliente, entao aceitamos aquela requisicao*/
						addrlen = sizeof remoteaddr;
						newfd = accept(server_socket,
								(struct sockaddr *)&remoteaddr,
								&addrlen);

						if (newfd == -1) {
							perror("accept");
						} else {
							//adiciona o novo socket criato à lista
							FD_SET(newfd, &master); 
							if (newfd > fdmax) {    
								fdmax = newfd;
							}
							printf("selectserver: new connection from %s on "
									"socket %d\n",
									inet_ntop(remoteaddr.ss_family,
										get_in_addr((struct sockaddr*)&remoteaddr),
										remoteIP, INET6_ADDRSTRLEN),
									newfd);
						}
					} else {
						/*nesse caso foi um dado enviado por um dos clientes*/
						if ((nbytes = recv(i, buf, sizeof buf, 0)) <= 0) {
							if (nbytes == 0) {
								/*se lemos 0 bytes a conexao foi quebrada*/
								printf("selectserver: socket %d hung up\n", i);
							} else {
								perror("recv");
							}
							close(i);
							/*remove da lista de sockets*/
							FD_CLR(i, &master); 
						} else {
							/*recebeu dados*/
							for(j = 0; j <= fdmax; j++) {
								// envia os dados para todos os outros clientes
								if (FD_ISSET(j, &master)) {
									/*exclui o servidor e o próprio cliente*/
									if (j != server_socket && j != i) {
										if (send(j, buf, nbytes, 0) == -1) {
											perror("send");
										}
									}
								}
							}
						}
					} 
				} 
			} 
		} 
    
    return 0;
}
