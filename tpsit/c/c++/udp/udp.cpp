#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "udp.h"

using namespace udpNS;
using namespace std;
udp::udp(unsigned short port_number){
          struct sockaddr_in add;
          if((socket_id = socket(AF_INET, SOCK_DGRAM | SOCK_NONBLOCK, 0)) < 0){
            socket_id = -1;
            return;
          }
          memset ((char *)&add, 0, sizeof(add));
          add.sin_family = AF_INET;
          add.sin_port = htons(port_number);
          add.sin_addr.s_addr = 0;
          if(bind(socket_id, (struct sockaddr*)&add, sizeof(add)) < 0){
            close(socket_id);
            socket_id = -1;
            return;
          }
          return;
        }

udp::~udp(void){
  if (socket_id >= 0)
      close(socket_id);
  return;
}

int udp::send(unsigned long ip_address, unsigned short port_number,
                  unsigned char buffer[], int N_byte) {
        struct sockaddr_in add;
        if(socket_id < 0)
          return -1;
        memset((char*)&add, 0, sizeof(add));
        add.sin_family = AF_INET;
        add.sin_port = htons(port_number);
        add.sin_addr.s_addr = htonl(ip_address);

        if(sendto(socket_id, (void *)buffer, N_byte, 0,  (struct sockaddr*)&add, sizeof(add)) < 0)
          return -1;
        return 0;
      }

  int udp::receive(unsigned long *ip_address, unsigned short *port_number,
                    unsigned char *buffer, int size){
        struct sockaddr_in add;
        unsigned int dim = sizeof(add);
        int n;
        if(socket_id < 0)
          return -1;
        if((n = recvfrom(socket_id, (void *)buffer, size, 0, (struct sockaddr *)&add, &dim)) <= 0)
          return -1;
        return n;
      }
