#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <pthread.h>

#define PORT 8000
#define MAXSZ 100
void* esegui(void *arg);

int main()
{
    int sockfd;
    int newsockfd;
    int portadin;
    char buf[100];
    struct sockaddr_in serverAddress;
    struct sockaddr_in clientAddress;
    
    unsigned int clientAddressLength;
    pthread_t serverThread;

    
    if((sockfd=socket(AF_INET,SOCK_STREAM,0)) < 0)
    {
      perror("Impossibile creare il socket");
      exit(EXIT_FAILURE);
    }
    memset(&serverAddress,0,sizeof(serverAddress));
    serverAddress.sin_family=AF_INET;
    serverAddress.sin_addr.s_addr=htonl(INADDR_ANY);
    serverAddress.sin_port=htons(PORT);


    if(bind(sockfd,(struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0)
    {
    	perror("Impossibile eseguire il bind");
    	exit(EXIT_FAILURE);
    }

    if(listen(sockfd,5) != 0)
    {
    	perror("Impossibile mettersi in ascolto");
    	exit(EXIT_FAILURE);
    }

    while(1)
    {

        puts("\nServizio attivo...");
        clientAddressLength=sizeof(clientAddress);
        newsockfd=accept(sockfd,(struct sockaddr*)&clientAddress,&clientAddressLength);
        portadin = clientAddress.sin_port;
        
        snprintf(buf, 100, "Connesso a %d: %s sulla porta: %d\n", newsockfd, inet_ntoa(clientAddress.sin_addr), portadin);
        
        printf("%s", buf);
        int *arg = malloc(sizeof(*arg));
        *arg = newsockfd;
        printf("%ls", arg);
        pthread_create(&serverThread,NULL,&esegui,arg);
    }

    return 0;
}

void* esegui(void *arg)
{
    int n;
    int newsockfd=*((int *) arg);
    char msg[MAXSZ];
    char buf[1024];

    pthread_detach(pthread_self());
    while(1)
    {
        n=recv(newsockfd,msg,MAXSZ,0);
        
        if(n==0)
        {
            close(newsockfd);
            break;
        }
        msg[n]=0;
        send(newsockfd,msg,n,0);
        snprintf(buf, 1024, "%d - Invio: %s", newsockfd, msg);
        printf("%s", buf);

    }
    close(newsockfd);
}
