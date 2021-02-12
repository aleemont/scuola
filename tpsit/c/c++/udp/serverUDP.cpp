#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include "udp.h"
#include "sequence.h"

#define UDP_PORT 23365

using namespace udpNS;
using namespace std;

int main(void){
  unsigned char buffer[1024];
  unsigned long ip_address;
  unsigned short port_number;
  unsigned int num;
  int n;

  udp socket(UDP_PORT);

  std::cout << "Servizio attivo..."<<endl;

  while (1) {
    if((n = socket.receive(&ip_address, &port_number, buffer, sizeof(buffer))) > 0){
      buffer[n] = '\0';
      if(strcmp((char *)buffer, "ASK") == 0){
        num = htonl(sequence());
        socket.send(ip_address, port_number, (unsigned char *)&num, sizeof(unsigned int));
      }
    }
  }
  return 0;
}
