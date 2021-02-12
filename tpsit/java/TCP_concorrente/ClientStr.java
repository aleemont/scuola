import java.io.*;
import java.net.*;

public class ClientStr {

	String nomeServer = "localhost";
	int portaServer = 6789;
	Socket miosocket;
	BufferedReader tastiera;
	String stringaUtente;
	String nome;
	String stringaRicevutaDalServer;
	DataOutputStream outVersoServer;
	BufferedReader inDalServer;
	int primo;
	int secondo;
	int ris;
	
	public Socket connetti() {
		
		System.out.println("CLIENT Partito in esecuzione");
		try
		{		
			tastiera = new BufferedReader(new InputStreamReader(System.in));
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
        try{
            System.out.print("Inserisci Nome: ");
            
            nome = tastiera.readLine();
            outVersoServer.writeBytes(nome + '\n');
        }catch(Exception e){}
		for(;;)
		try {
			System.out.print("Scrivi: ");
			stringaUtente = tastiera.readLine();
			outVersoServer.writeBytes(stringaUtente + '\n');
			stringaRicevutaDalServer = inDalServer.readLine();
			System.out.println("Risposta dal server: "+stringaRicevutaDalServer);
			if(stringaUtente.equals("FINE")) {
				System.out.println("CLIENT: termina elaborazione e chiude connessione");
				miosocket.close();
				break;
			}
		}catch(Exception e) {}
		
	}
	
	
	public static void main(String[] args) {
		ClientStr cliente = new ClientStr();
		cliente.connetti();
		cliente.comunica();

	}

}
