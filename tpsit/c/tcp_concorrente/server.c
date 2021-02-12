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

#define PORT 6789 //porta su cui connettersi
#define MAXSZ 250 //dimensione buffer
#define MAXCONN 10
void* task(void *arg);

int main(void)
{
 int sockfd; //server socket (padre)
 int childSockfd; //server socket (figlio)

 struct sockaddr_in server; //indirizzo server (ricezione)
 struct sockaddr_in client; //indirizzo client (scrittura)

 unsigned int clientAddressLen;
 pthread_t serverThread;
 
 if((sockfd=socket(AF_INET,SOCK_STREAM,0)) < 0 )
 {
	int error = errno;
	printf("Errore nella creazione del socket: %d [%s]", errno, strerror(error));
 }
 //Inizializzazione dell'indirizzo ip del server
 memset(&server,0,sizeof(server));
 server.sin_family=AF_INET;
 server.sin_addr.s_addr=htonl(INADDR_ANY);
 server.sin_port=htons(PORT);

 //bind del socket sulla porta specificata 
 if(bind(sockfd,(struct sockaddr *)&server, sizeof(server)) < 0)
 {
 	int error = errno;
 	printf("Errore nel bind: %d [%s]", errno, strerror(error));
 }

 //Server in ascolto
 listen(sockfd, MAXCONN);

 while(1)
 {
  //Processo padre che aspetta le conessioni da parte dei client
  printf("\n*****Server in ascolto:*****\n");
  clientAddressLen=sizeof(client);
  childSockfd = accept(sockfd, (struct sockaddr*) &client, &clientAddressLen);
  printf("CONNESSO! al client: %s\n", inet_ntoa(client.sin_addr));
  //Quando riceve la connessione di un client crea un processo figlio
  pthread_create(&serverThread, NULL, &task, (void *) (intptr_t)childSockfd);
 }

 return 0;
}
void* task(void *arg)
{
 int n; //variabile di controllo per la ricezione
 int childSockfd = (intptr_t)arg; //socket server figlio
 char msg[MAXSZ]; //buffer

 pthread_detach(pthread_self()); /* marca il thread come "detached"
 									permettendo il rilascio delle
 									risorse al termine dell'esecuzione
 									della funzione*/
 while(1)
 {
  n=recv(childSockfd,msg,MAXSZ,0);
  if(n==0)
  {
   int error = errno;
   printf("Errore nella ricezione del buffer: %d [%s]", errno, strerror(error));
   shutdown(childSockfd, 2);
   break;
  }
  msg[n]=0;
  send(childSockfd,msg,n,0);

  printf("%s\n",msg);
 }
 shutdown(childSockfd, 2);
}
