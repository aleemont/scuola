#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <signal.h>
#define MAX 80
#define PORT 8082

void addr_init(struct sockaddr_in *addr, int port, long int ip);
void chat(int connfd);

int main(void)
{
  int rc;
  struct in_addr a;
  in_addr_t addr;
  addr = inet_addr("127.0.0.1");
  a.s_addr=addr;
  struct sockaddr_in server, client;
  rc = socket(AF_INET, SOCK_STREAM, 0);      //creo il socket
  if(rc < 0)
	{
    puts("Impossibile creare socket");
    return -1;
  }
  puts("Socket creato");

  memset(&server, 0, sizeof(server));   //azzeramento struttura
  memset(&client, 0, sizeof(client));   //azzeramento struttura

  addr_init (&server, PORT, addr);    //inizializzo l'IP
  puts("Inizializzazione riuscita");

  int b = bind(rc, (struct sockaddr*) &server, sizeof(server));   //bind del socket sulla porta specificata
  if(b < 0)
	{
    puts("Impossibile collegarsi sulla porta specificata");
    return -1;
  }

  int l = listen(rc, 5);
  if(l != 0)
  {
    puts("Impossibile mettersi in ascolto...");
    return -1;
  }
  puts("In ascolto...");

  int len = sizeof(client);
  int conn = accept(rc, (struct sockaddr *)&client, &len);
  if(conn < 0)
  {
    puts("Connessione al client: rifiutata");
    return -1;
  }
  puts("Connessione al client: accettata");
  chat(conn);
  close(rc);
}

void addr_init(struct sockaddr_in *addr, int port, long int ip)
{
  addr->sin_family = AF_INET; //Inizializzo la famiglia di indirizzi (ipv4)
  addr->sin_port = htons((u_short) port); //conversione in little-endian del numero di porta (msb first)
  addr->sin_addr.s_addr = INADDR_ANY;
}

void chat(int connfd)
{
    char buff[MAX];
    int n;
    while(1) {
        bzero(buff, MAX); //azzero il buffer

        read(connfd, buff, sizeof(buff)); // leggo il messaggio inviato dal client

        printf("Client: %s\t Tu: ", buff); // visualizzo il messaggio
        bzero(buff, MAX);
        n = 0;

        while ((buff[n++] = getchar()) != '\n'){} // Inserisco il messaggio da inviare nel buffer

        write(connfd, buff, sizeof(buff)); // Invio messaggio al client

        if (strncmp("exit", buff, 4) == 0) {  //se il messaggio è "exit" termina la chat
            printf("Chiudo la connessione...\n");
            break;
        }
    }
}
