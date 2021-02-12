import java.io.*;
import java.net.*;

public class Client {

	String nomeServer = "localhost";
	int portaServer = 80;
	Socket miosocket;
	BufferedReader tastiera;
	String stringaUtente;
	String stringaRicevutaDalServer;
	DataOutputStream outVersoServer;
	BufferedReader inDalServer;
	
	public Socket connetti() {
		
		System.out.println("CLIENT Partito in esecuzione");
		try
		{		
			tastiera = new BufferedReader(new InputStreamReader(System.in));
			System.out.println("Inserire IP del server: ");
			nomeServer = tastiera.readLine();
			miosocket = new Socket(nomeServer, portaServer);
			outVersoServer = new DataOutputStream(miosocket.getOutputStream());
			inDalServer = new BufferedReader(new InputStreamReader(miosocket.getInputStream()));
		}
		catch(UnknownHostException e) {
			System.err.println("Host Sconosciuto!");
		}
		catch(Exception e) {
			System.out.println("Errore durante la connessione!");
			System.exit(1);
		}
		
		return miosocket;
	}
	
	public void comunica() {
		
		try
		{
			stringaUtente = "GET / HTTP/1.1\r\nHost:"+nomeServer+"\r\n\r\n";
			System.out.println("Invio la stringa al server e attendo");
			outVersoServer.writeBytes(stringaUtente);
			System.out.println("RISPOSTA DAL SERVER: " + '\n');
			while((stringaRicevutaDalServer = inDalServer.readLine()) != null)
			{
			System.out.println(stringaRicevutaDalServer);
			}
			
			System.out.println("CLIENT: Termina elaborazione e chiude connessione");
			miosocket.close();			
		}
		catch(Exception e)
		{
			System.out.println("Errore durante la comunicazione con il server!");
			System.exit(1);
		}
		
	}
	
	
	public static void main(String[] args) {
		Client cliente = new Client();
		cliente.connetti();
		cliente.comunica();

	}

}
