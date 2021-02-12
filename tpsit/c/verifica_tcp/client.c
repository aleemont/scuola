#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<string.h>
#include<errno.h>
#include<pthread.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

#define PORT 5000
#define SERVER_IP "127.0.0.1"
#define MAXSZ 250
int main()
{
 puts("Benvenuti nel sistema GiorgiPass\n");
 int sockfd;//client socket

 struct sockaddr_in serverAddress;//indirizzo del server
 
 FILE *autostrada;
 autostrada = fopen("a14.txt", "r+");
 int n; //variabile di controllo per send e recv
 char request[MAXSZ]; //messaggio in uscita
 char received[MAXSZ];
 char targa[7];
 char casello[100];
 //char scontrino[MAXSZ + strlen(nick)]; //Messaggio completo da inviare
 
 unsigned int INcod_casello = 0;
 puts("Tentativo di connessione al server");
 if((sockfd=socket(AF_INET,SOCK_STREAM,0)) < 0 )
 {
	int error = errno;
	printf("Errore nella creazione del socket: %d [%s]", errno, strerror(error));
 }
 //Inizializzazione dell'indirizzo
 memset(&serverAddress,0,sizeof(serverAddress));
 serverAddress.sin_family=AF_INET;
 serverAddress.sin_addr.s_addr=inet_addr(SERVER_IP);
 serverAddress.sin_port=htons(PORT);

 //Connessione del client sulla porta specificata
 connect(sockfd,(struct sockaddr *)&serverAddress,sizeof(serverAddress));
 //Ciclo infinito per invio e ricezione
 puts("Inserire targa auto: ");
 fgets(targa, 7, stdin);
 targa[strcspn(targa, "\n")] = 0;
 
 while(1)
 {
  printf("\nInserire codice casello in entrata:\n");
  scanf("%u", &INcod_casello);
  sprintf(request, "%s: %u", targa, &INcod_casello);
  if(request[0]=='#')
   break;

  n=strlen(request)+1;
  send(sockfd,request,n,0);

  n=recv(sockfd,received,MAXSZ,0);

  printf("Ricevuto dal server:: %s\n",received);
 }

 return 0;
}
