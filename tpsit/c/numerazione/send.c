#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <time.h>

void addr_init(struct sockaddr_in *addr, int port, long int ip){
  addr->sin_family = AF_INET; //Inizializzo la famiglia di indirizzi (ipv4)
  addr->sin_port = htons((u_short) port); //conversione in little-endian del numero di porta (msb first)
  addr->sin_addr.s_addr = ip;
}

int main(int argc, char *argv[]){

  if(argc < 3){
    printf("./send <IP> <PORTA>\n");
    return -1;
  }
  char *msg = "ASK";
  char buffer[1024];
  int port = atoi(argv[2]);
  int sd = 0;
  int now, start;
  in_addr_t addr;
  struct in_addr a;
  struct sockaddr_in server;
  memset(&addr, 0, sizeof(addr));
  addr = inet_addr(argv[1]);
  a.s_addr=addr;

  memset(&server, 0, sizeof(server));

  printf("IP associato a 0x%x: %s\n", addr, inet_ntoa(a));        //inet_ntoa() trasforma l'ip nella notazione puntata standard
  addr_init(&server, port, addr);
  puts("Inizializzazione riuscita");

  sd=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if(sd < 0){
    puts("Impossibile creare socket");
    return -1;
  }
  puts("Socket creato");

  int len;
  unsigned int num;
  sendto(sd, (char *)msg, strlen(msg), MSG_CONFIRM, (struct sockaddr *) &server, sizeof(server));
  printf("Invio: \"%s\" al server\n", msg);
  len = sizeof(server);
  int n = recvfrom(sd, (void *)&num, sizeof(unsigned int), MSG_WAITALL, (struct sockaddr *) &server, &len);
  printf("Ricevuto: %u\n",num);
  shutdown(sd, 2);
  return 0;
}
