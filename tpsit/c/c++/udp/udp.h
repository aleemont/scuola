namespace udpNS{
  class udp{
  protected:
      int socket_id;
    public:
      udp(unsigned short port_number = 0);

      ~udp(void);

      int send(unsigned long ip_address, unsigned short port_number,
                    unsigned char buffer[], int N_byte);

      int receive(unsigned long *ip_address, unsigned short *port_number,
                    unsigned char *buffer, int size);

  };
}
