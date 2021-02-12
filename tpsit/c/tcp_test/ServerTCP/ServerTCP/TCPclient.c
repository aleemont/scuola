#include <stdio.h>
#include <string.h>
#include <WinSock.h>

#include "TCPclient.h"

SOCKET socket_id; // identificatore del socket

static unsigned long IP_to_bin(char ip_add[])
{
 unsigned long add;
 unsigned char byte;
 char *token;

 if ((token = strtok(ip_add,".")) == NULL)
	return 0x00000000;
 byte = (unsigned char)atoi(token);
 add = (unsigned long)byte * 16777216;
 if ((token = strtok(NULL,".")) == NULL)
	return 0x00000000;
 byte = (unsigned char)atoi(token);
 add += (unsigned long)byte * 65536;
 if ((token = strtok(NULL,".")) == NULL)
	return 0x00000000;
 byte = (unsigned char)atoi(token);
 add += (unsigned long)byte * 256;
 if ((token = strtok(NULL,".")) == NULL)
	return 0x00000000;
 byte = (unsigned char)atoi(token);
 add += (unsigned long)byte * 1;
 return add;
}

int TCPclient_connect(char ip_address[], unsigned short port_number)
{
 unsigned long binary_address = IP_to_bin(ip_address);
 struct sockaddr_in add; // struttura per indirizzo
 unsigned long arg = 1;
 WSADATA wsaData;

 // inizializzazione WinSock (versione 2.2)
 if (WSAStartup(0x0202, &wsaData) != 0)
   return -1;
 // costruzione struttura indirizzo
 memset(&add, 0, sizeof(add)); // azzeramento struttura
 add.sin_family = AF_INET; // dominio indirizzi IP
 add.sin_addr.s_addr = htonl(binary_address); // indirizzo IP server
 add.sin_port = htons(port_number); // numero di porta server
 // apertura socket TCP
 if (( socket_id = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
   {
	WSACleanup();
	return -1;
   }
 // connessione al socket del server
 if ( connect(socket_id, (struct sockaddr*)&add, sizeof(add)) == SOCKET_ERROR)
   {
	closesocket(socket_id);
	WSACleanup();
	return -1;
   }
 // impostazione socket non bloccante
 if (ioctlsocket(socket_id, FIONBIO, &arg) == SOCKET_ERROR)
   {
	closesocket(socket_id);
	WSACleanup();
	return -1;
   }
 return 0;
}

int TCPclient_receive(char buffer[], int size)
{
 int n;

 // ricezione dati (non bloccante)
 if ((n = recv(socket_id, (void*)buffer, (size_t)size, 0)) <= 0)
   return -1;
 return n;
}

int TCPclient_send(char* buffer, int num)
{
 int n;

 // trasmissione dati
 if ((n = send(socket_id, (void*)buffer, (size_t)num, 0)) < 0)
   return -1;
 return n;
}

void TCPclient_disconnect()
{
 // chiusura socket (disconnessione dal server)
 closesocket(socket_id);
 WSACleanup();
 return;
}
