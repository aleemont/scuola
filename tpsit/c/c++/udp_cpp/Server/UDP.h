namespace server
{
    class UDP
    {

        private:
            int socket_id; // identificatore del socket
        
        public:

            UDP(unsigned short port_number=0);

            ~UDP (void);

            int send( unsigned long ip_address, unsigned short port_number,unsigned char buffer[], int N_byte);

            int receive( unsigned long *ip_address, unsigned short *port_number,unsigned char *buffer, int size);
        

    };
}
