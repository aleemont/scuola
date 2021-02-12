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
void chat(int sd);

int main()
{
  int sd;
  struct in_addr a;
  in_addr_t addr;
  addr = inet_addr("127.0.0.1");
  a.s_addr=addr;
  struct sockaddr_in server, client;
  sd = socket(AF_INET, SOCK_STREAM, 0);      //creo il socket
  if(sd < 0)
  {
    puts("Impossibile creare socket");
    return -1;
  }
  puts("Socket creato");

  memset(&server, 0, sizeof(server));   //azzeramento struttura
  memset(&client, 0, sizeof(client));   //azzeramento struttura

  addr_init (&server, PORT, addr);    //inizializzo l'IP
  puts("Inizializzazione riuscita");

  int conn = connect(sd, (struct sockaddr*)&server, sizeof(server));
    if (conn != 0) {
        puts("Impossibile collegarsi al server");
        return -1;
    }
    puts("Connesso al server..\n");

    // function for chat
    chat(sd);

    // close the socket
    close(sd);
}

void addr_init(struct sockaddr_in *addr, int port, long int ip)
{
  addr->sin_family = AF_INET; //Inizializzo la famiglia di indirizzi (ipv4)
  addr->sin_port = htons((u_short) port); //conversione in little-endian del numero di porta (msb first)
  addr->sin_addr.s_addr = INADDR_ANY;
}

void chat(int sd)
{
    char buff[MAX];
    int n;
    while(1)
    {
        bzero(buff, sizeof(buff));
        printf("Tu: ");
        n = 0;
        while ((buff[n++] = getchar()) != '\n'){}
        write(sd, buff, sizeof(buff));
        bzero(buff, sizeof(buff));
        read(sd, buff, sizeof(buff));
        printf("Ricevuto: %s", buff);
        if ((strncmp(buff, "exit", 4)) == 0)
        {
            printf("Chiudo la connessione...\n");
            break;
        }
    }
}
