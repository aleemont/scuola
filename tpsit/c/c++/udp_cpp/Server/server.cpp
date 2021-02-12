#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include "UDP.h"
#include "sequence.h"

#define UDP_PORT 23365

using namespace server;
using namespace std;

int main(void)

{

    unsigned char buffer[1024]; // buffer per ricezione

    unsigned long ip_address;

    unsigned short port_number;

    unsigned int num; // variabile per numero da generare

    int n;

    // creazione oggetto di classe UDP (socket con porta numero

    // 23365)

    UDP socket(UDP_PORT);

    cout << "Servizio attivo..." << endl;

    while (1)
    {

        if ((n = socket.receive( &ip_address, &port_number, buffer, sizeof(buffer))) > 0)
        {

        // ricezione di un datagram e verifica del messaggio

            buffer[n] = '\0'; // terminatore di stringa

            if (strcmp((char*)buffer, "ASK") == 0)

            {

                // richiesta di generazione di un nuovo numero

                num = htonl(sequence());
                cout << "Inviato il numero " << num;
                socket.send(ip_address, port_number,( unsigned char*)&num,sizeof(unsigned int));

            }

        }

    }

    return 0;

}
