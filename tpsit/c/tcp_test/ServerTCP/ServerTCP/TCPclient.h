// inizializza il socket creando una connessione con il server
// identificato da indirizzo IP e numero di porta TCP specificati
// restituisce -1 in caso di errore, 0 in caso di successo
int TCPclient_connect(char ip_address[], unsigned short port_number);

// trasmette al server num caratteri contenuti nel buffer
// restituisce -1 in caso di errore, altrimenti il numero di
// caratteri trasmessi
int TCPclient_send(char buffer[], int num);

// riceve una sequenza di caratteri nel buffer di dimensione size
// restituisce -1 in caso di errore o di dati non disponibili,
// il numero di caratteri ricevuti in caso di successo
int TCPclient_receive(char* buffer, int size);

// chiude il socket disconnettendosi dal server
void TCPclient_disconnect();
