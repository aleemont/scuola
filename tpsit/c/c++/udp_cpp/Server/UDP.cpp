#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include "UDP.h"
using namespace server;
using namespace std;


    UDP::UDP(unsigned short port_number)
    {

        struct sockaddr_in add; // struttura per indirizzo locale

        // apertura socket UDP non bloccante

        if ((socket_id = socket( AF_INET, SOCK_DGRAM | SOCK_NONBLOCK, IPPROTO_UDP)) < 0)
        {

            socket_id = -1;

            return;

        }

        // costruzione struttura indirizzo

        memset((char*)&add, 0, sizeof(add)); // azzeramento struttura

        add.sin_family = AF_INET; // dominio indirizzi IP

        add.sin_port = htons(port_number); // numero di porta UDP locale

        add.sin_addr.s_addr = 0; // indirizzo IP locale

        // associazione socket a numero di porta

        if (bind(socket_id, (struct sockaddr*)&add, sizeof(add)) < 0)
        {

            close(socket_id);

            socket_id = -1;

            return;

        }
        
        return;
    
    }

    // distruttore

    UDP::~UDP (void)
    {

        if (socket_id >= 0)

            close(socket_id);

        return;

    }

    // trasmissione di dati al computer remoto

    // parametri:

    // ip_address: indirizzo IP destinatario

    // port_number: numero di porta UDP destinatario

    // buffer: dati da trasmettere

    // N_byte: numero di byte da trasmettere

    // valore restituito: -1 in caso di errore, altrimenti 0

    int UDP::send( unsigned long ip_address, unsigned short port_number,unsigned char buffer[], int N_byte)
    {

        struct sockaddr_in add; // struttura per indirizzo destinazione

        if (socket_id < 0)

            return -1;

        // costruzione struttura indirizzo

        memset((char*)&add, 0, sizeof(add)); // azzeramento struttura

        add.sin_family = AF_INET; // dominio indirizzi IP

        add.sin_port = htons(port_number); // numero di porta UDP

        add.sin_addr.s_addr = htonl(ip_address); // indirizzo IP

        // trasmissione datagram

        if (sendto (socket_id, (void*)buffer, N_byte, 0,(struct sockaddr*)&add, sizeof(add)) < 0)

            return -1;

        return 0;

    }

    // ricezione di dati dal computer remoto

    // parametri:

    // ip_address: restituisce l'indirizzo IP del mittente

    // port_number: restituisce il numero di porta UDP del mittente

    // buffer: dati ricevuti

    // size: dimensione del buffer

    // valore restituito: numero di byte ricevuti, -1 in caso di errore

    int UDP::receive( unsigned long *ip_address, unsigned short *port_number,unsigned char *buffer, int size)
    {

        struct sockaddr_in add; // struttura per indirizzo mittente

        unsigned int dim = sizeof(add);

        int n;

            if (socket_id < 0)

                return -1;

        // ricezione datagram (non bloccante)

            if ((n = recvfrom( socket_id, (void*)buffer, size, 0, (struct sockaddr*)&add, &dim)) <= 0)

                return -1;

        // estrazione indirizzo IP e numero di porta UDP mittente

        *ip_address = ntohl(add.sin_addr.s_addr);

        *port_number = ntohs(add.sin_port);

        return n;

    }

