import java.io.*;
import java.net.*;

public class Client {

	String nomeServer = "localhost";
	int portaServer = 8081;
	double operando = 0;
	String operatore;
	double res;
	Socket miosocket;
	BufferedReader tastiera;
	String stringaUtente;
	String stringaRicevutaDalServer;
	DataOutputStream outVersoServer;
	BufferedReader inDalServer;
	
	public Socket connetti() {
		
		System.out.println("2. CLIENT Partito in esecuzione");
		try
		{		
			tastiera = new BufferedReader(new InputStreamReader(System.in));
			miosocket = new Socket(nomeServer, portaServer);
			outVersoServer = new DataOutputStream(miosocket.getOutputStream());
			inDalServer = new BufferedReader(new InputStreamReader(miosocket.getInputStream()));
			System.out.println("3. Connesso a: " + nomeServer + " sulla porta:" + portaServer);
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
			System.out.print("\n4.Inserire primo operando: ");
			operando = Double.parseDouble(tastiera.readLine());
			System.out.println("\n5.Invio l'operando al server e attendo");
			outVersoServer.writeBytes(String.valueOf(operando)+'\n');

			System.out.print("7.Inserire secondo operando: ");
			operando = Double.parseDouble(tastiera.readLine());
			System.out.println("\n8.Invio l'operando al server e attendo");
			outVersoServer.writeBytes(String.valueOf(operando)+'\n');

			System.out.print("10.Inserire l'operatore (+, -, *, /, ^): ");
			operatore = tastiera.readLine();
			System.out.println("\n11.Invio l'operatore al server e attendo");
			outVersoServer.writeBytes(operatore+'\n');

			res = Double.parseDouble(inDalServer.readLine());
			System.out.println("15. Ricevuto risultato dal server: " + res);
			
			System.out.println("17. Operazione terminata.");
			miosocket.close();			
		}
		catch(Exception e)
		{
			System.out.println("Errore durante la comunicazione con il server!" + e);
			System.exit(1);
		}
		
	}
	
	
	public static void main(String[] args) {
		Client cli = new Client();
		cli.connetti();
		cli.comunica();
	}

}
