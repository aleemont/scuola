#include <stdio.h>
#include <string.h>
#include <WinSock.h>

#include "sequence.h"

#define TCP_PORT 23365

int main(void)
{
	WSADATA wsaData;
	SOCKET request_socket_id; // socket per richieste di connessione
	SOCKET communication_socket_id; // socket comunicazione con client
	struct sockaddr_in server_add; // struttura per indirizzo server
	struct sockaddr_in client_add; // struttura per indirizzo client
	unsigned int client_add_size;
	char buffer[1024]; // buffer per ricezione
	char message[1024]; // messaggio ricevuto da client
	int index; // indice per costruzione stringa di comando
	unsigned int num; // variabile per numero da generare
	int i, n;

	// inizializzazione WinSock (versione 2.2)
	if (WSAStartup(0x0202, &wsaData) != 0)
		{
			printf("Errore inizializzazione WinSock!\r\n");
			return -1;
		}

	// apertura del socket
	if ((request_socket_id = socket(AF_INET, SOCK_STREAM,IPPROTO_TCP)) == INVALID_SOCKET)
		{
			printf("Errore apertura socket!\r\n");
			WSACleanup();
			return -1;
		}

	// costruzione della struttura per l'indirizzo del server
	memset(&server_add, 0, sizeof(server_add));
	server_add.sin_family = AF_INET;
	server_add.sin_addr.s_addr = 0; // indirizzo IP locale
	server_add.sin_port = htons(TCP_PORT); // numero di porta server

	// associazione del numero di porta al socket
	if (bind(request_socket_id, (struct sockaddr *)&server_add, sizeof(server_add)) == SOCKET_ERROR)
		{
			printf("Errore associazione socket!\r\n");
			closesocket(request_socket_id);
			WSACleanup();
			return -1;
		}

	// impostazione del socket per ricevere le richieste di connessione
	if (listen(request_socket_id, 1) == SOCKET_ERROR)
		{
			printf("Errore impostazione socket!\r\n");
			closesocket(request_socket_id);
			WSACleanup();
			return -1;
		}
	
	printf("Servizio attivo...\r\n");
	
	while (1)
	{
		client_add_size = sizeof(client_add);
		communication_socket_id = accept(request_socket_id, (struct sockaddr*)&client_add, &client_add_size);
		
		if (communication_socket_id != INVALID_SOCKET)
			{
				// connessione effettuata: ricezione messaggi dal client
				index = 0;
				while (1)
					{
						if ((n = recv(communication_socket_id, buffer, sizeof(buffer), 0)) <= 0)
							{
								// chiusura della connessione da parte del client
								closesocket(communication_socket_id);
								printf("...chiusura socket lato client!\r\n");
								break;
							}
						else
							{
								// ricezione caratteri:
								// costruzione del messaggio
								for (i=0; i<n; i++)
									if (buffer[i] == '\r' || buffer[i] == '\n')
									  {
										// messaggio completato: inserimento del
										// terminatore di stringa
										message[index] = '\0';
										index = 0;
										if (strcmp(message, "ASK") == 0)
										{
											// richiesta di generazione di
											// un nuovo numero
											num = sequence();
											sprintf(message,"%u\r\n", num);
											send(communication_socket_id, message, strlen(message), 0);
											printf("...inviato numero %u.\r\n",	num);
										}	 	
									  }
									else
									  {
											// copia del carattere nel messaggio
											if (index >= sizeof(message))
										 	 	index = 0;
										 	message[index] = buffer[i];
										 	index++;
									  }
							}
					}
		}
	}
	
	closesocket(request_socket_id);
	WSACleanup();
	return 0;
}
