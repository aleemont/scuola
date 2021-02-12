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

#define PORT 80
#define TIMEOUT	2*CLOCKS_PER_SEC

void addr_init(struct sockaddr_in *addr, int port, long int ip);

int main(int argc, char *argv[])
{
  if(argc != 3)
  {
  	puts("Funzionamento: ./client <server[ip] o [www.example.foo]> </path/to/file>");
  	return -1;
  }
  int sd;  
  struct in_addr a;
  in_addr_t addr;
//###############################RISOLUZIONE DNS####################################
  struct addrinfo hints, *res;
  int errcode;
  char addrstr[100];
  void *ptr;
  memset (&hints, 0, sizeof (hints));
  hints.ai_family = PF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags |= AI_CANONNAME;
  errcode = getaddrinfo (argv[1], NULL, &hints, &res); //salvo le informazioni dell'host nella struttura
  if (errcode != 0)
  {
   perror ("getaddrinfo");
   return -1;
  }
  printf ("Host: %s\n", argv[1]);
  while (res)
  {
   inet_ntop (res->ai_family, res->ai_addr->sa_data, addrstr, 100); 
  switch (res->ai_family)		//controllo la famiglia dell'indirizzo (IPv4 o IPv6)
  {
    case AF_INET:
     ptr = &((struct sockaddr_in *) res->ai_addr)->sin_addr;     //salvo l'informazione nella struttura
     break;
    case AF_INET6:
     ptr = &((struct sockaddr_in6 *) res->ai_addr)->sin6_addr;
     break;
  }
  inet_ntop (res->ai_family, ptr, addrstr, 100);                //converto l'ip nella nomenclatura standard puntata
  printf("IPv%d address: %s (%s)\n", res->ai_family == PF_INET6 ? 6 : 4,
          addrstr, res->ai_canonname);               //stampo il risultato
  res = res->ai_next;                               //passo alla prossima struttura, nel caso in cui l'host abbia diversi ip
   }
//##################################################################################
      
  addr = inet_addr(addrstr);  
  a.s_addr=addr;
  int opt = 1;
  int n;
  int i = 0;
  unsigned long start, now;
  struct sockaddr_in server;
  char GET[100];  //STRINGA DI GET
  snprintf(GET,25+strlen(addrstr)+strlen(argv[2]), "GET %s HTTP/1.1\r\nHost:%s\r\n\r\n", argv[2], addrstr);//, argv[2], addrstr); //formatto la stringa per la richiesta
  char buffer[9000];
  printf("0x%x : %s\n", addr, inet_ntoa(a));
  sd = socket(AF_INET, SOCK_STREAM, 0);      //creo il socket
  if(sd < 0)
  {
    puts("Impossibile creare socket");
    shutdown(sd,2);
    return -1;
  }
  puts("Socket creato");

  if (setsockopt(sd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
  { 
    perror("setsockopt"); 
    shutdown(sd,2);
    exit(EXIT_FAILURE); 
  }                          

  memset(&server, 0, sizeof(server));   //azzeramento struttura
  bzero(buffer,strlen(buffer));
 
  addr_init (&server, PORT, addr);    //inizializzo l'IP
  puts("Inizializzazione riuscita");

  int conn = connect(sd, (struct sockaddr*)&server, sizeof(server));
  if (conn != 0)
  {
    puts("Impossibile collegarsi al server");
    shutdown(sd,2);
    return -1;
  }
  puts("Connesso al server..\n");
  puts("Invio GET request al server...");
  puts("################################");
  puts(GET);
  puts("################################");
  if (send(sd, GET, strlen(GET), 0) < 0)
  {
    puts("Errore, impossibile inviare la richiesta al server");
  }
/*  puts("\n\nRicevuto: ");
  recv(sd, buffer, 65536, 0);*/
  start = clock(); // tempo iniziale attesa
  now = clock(); // tempo attuale
  while ((now - start) < TIMEOUT)
   {
    if ((n =recv(sd, &buffer[i], sizeof(buffer)-i, 0)) > 0)
    {
    // ricevuti caratteri: ricostruzione risposta
    i += n;
    if (buffer[i-1] == '\r' || buffer[i-1] == '\n')
    {
     // risposta completa
     buffer[i-2] = '\0';
     printf("Ricevuto: \r\n %s\r\n", buffer);
     shutdown(sd,2);
     break;
     return 0;
	}
   }
   now = clock(); // aggiornamento tempo attuale
  }
  printf("%s", buffer);
  shutdown(sd,2);
  return 0;
 }

 void addr_init(struct sockaddr_in *addr, int port, long int ip)
 {
   addr->sin_family = AF_INET; //Inizializzo la famiglia di indirizzi (ipv4)
   addr->sin_port = htons((u_short) port); //conversione in little-endian del numero di porta (msb first)
   addr->sin_addr.s_addr = ip ;
 }
