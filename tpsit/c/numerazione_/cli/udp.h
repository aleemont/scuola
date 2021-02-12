unsigned long IP_to_bin(char ip_address[]);

int UDP_init(unsigned short port_number);

int UDP_send(unsigned long ip_address, unsigned short port_number,
		unsigned char data[], int N_byte);

int UDP_receive(unsigned long *ip_address, unsigned short *port_number, 
		unsigned char data[], int size);

void UDP_close();
