#include <sys/types.h>
#include <sys/socket.h>
#include<sys/wait.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<signal.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <errno.h>

#define MAXLEN 1024

unsigned int sequence(void){
	FILE *file;
	unsigned int n;
	file = fopen("number.txt", "r+");
	if(file == NULL)
		return 0;
	if(fscanf(file, "%u", &n) != 1){
		fclose(file);
		return 0;
	}
	++n;
	fseek(file, 0, SEEK_SET);
	fprintf(file, "%u", n);
	fclose(file);

	return n;
}

void addr_init(struct sockaddr_in *addr, int port, long int ip){
  addr->sin_family = AF_INET; //Inizializzo la famiglia di indirizzi (ipv4)
  addr->sin_port = htons((u_short) port); //conversione in little-endian del numero di porta (msb first)
  addr->sin_addr.s_addr = INADDR_ANY;
}

int main(int argc, char *argv[]){
  if(argc < 3){
    printf("./rcv <IP> <porta>\n");
    return -1;
  }
  unsigned short int port = atoi(argv[2]);
  unsigned int num;
  int len, n;
  int rc = 0;
  char buffer[MAXLEN];
  struct sockaddr_in server, client;
  struct in_addr a;
  in_addr_t addr;
  addr = inet_addr(argv[1]);
  a.s_addr=addr;

  memset(&server, 0, sizeof(server));
  memset(&client, 0, sizeof(client));

  addr_init (&server, port, addr);
  puts("Inizializzazione riuscita");

  rc = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if(rc < 0){
    puts("Impossibile creare socket");
    return -1;
  }

  int b = bind(rc, (struct sockaddr*) &server, sizeof(server));
  if(b < 0){
    puts("Impossibile collegarsi sulla porta specificata");
    return -1;
  }

  printf("In ascolto sulla porta: %i\n", port);
  len = sizeof(client);
  while(1){
   n = recvfrom(rc, (char *)buffer, MAXLEN, MSG_WAITALL, (struct sockaddr *) &client, &len);
   buffer[n] = '\0';
   printf("Ricevuto: %s\n", buffer);
   if(strcmp((char *)buffer, "ASK") == 0){
     num = sequence();
     sendto(rc, (int *)&num, sizeof(num), MSG_CONFIRM, (struct sockaddr *) &client, len);
     printf("...inviato numero %u. \r\n", num);
   }
  }
  return 0;
}
