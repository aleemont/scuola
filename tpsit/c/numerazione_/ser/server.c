#include <stdio.h>
#include <string.h>

#include "udp.h"
#include "sequence.h"

#define UDP_PORT 8081

int main(void){
	unsigned char buffer[1024];
	unsigned long ip_address;
	unsigned short port_number;
	unsigned int num;
	int n;

	if(UDP_init(UDP_PORT) < 0){
		puts("Errore di inizializzazione \r");
		return -1;
	}
	puts("Servizio attivo... \r");
	while(1){
		if((n = UDP_receive(&ip_address, &port_number, buffer, sizeof(buffer))) > 0){
			if(strcmp((char *)buffer, "ASK") == 0){
				num = sequence();
				UDP_send(ip_address, port_number, (void *)&num, sizeof(unsigned int));
				printf("...inviato numero %u. \r\n", num);
			}
		}
	}
	UDP_close();
	return 0;
}
