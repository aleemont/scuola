
import java.io.*;
import java.net.*;

/**
 * Realizzazione di un Client TCP
 * 
 * @author Vito RUSSO 
 * @version 1.0
 */
public class ClientStr
{
    // variabili d'istanza - sostituisci l'esempio che segue con il tuo
    String nomeServer = "79.27.251.65";  //localhost
    int portaServer = 6789;
    Socket miosocket;
    BufferedReader tastiera;
    String stringaUtente;
    String stringaRicevutaDalServer;
    String nickname;
    DataOutputStream outVersoServer;
    BufferedReader inDalServer;
    
    public Socket connetti(){
        System.out.println("2 CLIENT partito in esecuzione ...");
        try
        {
            //per l'input da tastiera
            tastiera = new BufferedReader(new InputStreamReader(System.in));
            
            //inserire il nickname
            System.out.println("inserisci il tuo NickName:");
            nickname = tastiera.readLine();
                
            //crea un socket
            miosocket = new Socket(nomeServer, portaServer);
            //miosocket = new Socket(InetAddress.getLocalHost(), portaServer);
            
            //associo due oggetti al socket per effettuare la scrittura e la lettura
            outVersoServer = new DataOutputStream(miosocket.getOutputStream());
            inDalServer = new BufferedReader(new InputStreamReader (miosocket.getInputStream()));
        }
        catch (UnknownHostException e){
            System.err.println("Host sconosciuto"); }
        catch (Exception e) {
             System.out.println(e.getMessage());   
             System.out.println("Errore durante la connessione!");
             System.exit(1);
        }
        return miosocket;
    }
    
    public void comunica(){
        for (;;)
            try
            {
                System.out.println("4 ...  inserisci la stringa da trasmettere al server:");
                stringaUtente = tastiera.readLine();
                
                //la spedisco al server
                System.out.println("5 ...  invio la stringa al server e attendo ...");
                outVersoServer.writeBytes( "[" + nickname + "] " + stringaUtente + '\n');
                
                //leggo la risposta dal server
                stringaRicevutaDalServer = inDalServer.readLine();
                System.out.println("7 ...  risposta dal server "+'\n'+stringaRicevutaDalServer );
                
                if (stringaUtente.equals("FINE")) {
                    //chiudo la connessione
                    System.out.println("8 CLIENT: termina elaborazione e chiude la connessione" );
                    miosocket.close();
                    break;
                }
            }
             catch (Exception e) {
                 System.out.println(e.getMessage());   
                 System.out.println("Errore durante la comunicazione col server!");
                 System.exit(1);
            }
    }
    
  
    public static void main(String args[]) 
    {
        ClientStr cliente = new ClientStr();
        cliente.connetti();
        cliente.comunica();
    }
}
