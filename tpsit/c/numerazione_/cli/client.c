#include <stdio.h>
#include <time.h>
#include <string.h>

#include "udp.h"

#define TIMEOUT 1*CLOCKS_PER_SEC
#define UDP_PORT 8081

int main(int argc, char* argv[]){
	unsigned char buffer[1024] = "ASK";
	unsigned long ip_address;
	unsigned short port_number;
	unsigned long start, now;
	unsigned int *num = (unsigned int*)buffer;

	if(argc < 2){
		puts("./client <ip server> \r");
		return -1;
	}
	if(UDP_init(0) < 0){
		puts("Errore inizializzazione \r");
		return -1;
	}
	ip_address = IP_to_bin(argv[1]);
	port_number = UDP_PORT;
	UDP_send(ip_address, port_number, buffer, strlen((char *)buffer));
	start = clock();
	now = clock();
	while((now - start) < TIMEOUT){
			if (UDP_receive( &ip_address, &port_number, buffer,sizeof(buffer)) == sizeof(unsigned int)){
				printf("Ricevuto numero: %u. \r\n",*num);
        UDP_close();
				return 0;
			}
		now = clock();
	}

	puts("Nessuna risposta dal server \r");
	UDP_close();
	return -1;
}
