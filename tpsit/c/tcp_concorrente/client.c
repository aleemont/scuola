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

#define PORT 6789
#define SERVER_IP "127.0.0.1"
#define MAXSZ 250
int main()
{
 int sockfd;//client socket

 struct sockaddr_in serverAddress;//indirizzo del server

 int n; //variabile di controllo per send e recv
 char msg1[MAXSZ]; //messaggio in uscita
 char msg2[MAXSZ]; //messaggio in entrata
 char nick[10];
 char msg[MAXSZ + strlen(nick)]; //Messaggio completo da inviare

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
 puts("Inserire nickname: ");
 fgets(nick, 10, stdin);
 nick[strcspn(nick, "\n")] = 0;
 
 while(1)
 {
  printf("\nInserire messaggio da inviare al server:\n");
  fgets(msg1,MAXSZ,stdin);
  sprintf(msg, "%s: %s", nick, msg1);
  if(msg[0]=='#')
   break;

  n=strlen(msg)+1;
  send(sockfd,msg,n,0);

  n=recv(sockfd,msg2,MAXSZ,0);

  printf("Ricevuto dal server:: %s\n",msg2);
 }

 return 0;
}
