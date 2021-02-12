import java.io.*;
import java.net.*;

public class ClientStr {

	String nomeServer = "localhost";
	int portaServer = 6789;
	int cas;
	int cas2;
	Socket miosocket;
	BufferedReader tastiera;
	String stringaUtente;
	String targa;
	String classe;
	String flag = "no";
	String stringaRicevutaDalServer;
	ObjectOutputStream outVersoServer;
	BufferedReader inDalServer;

	
	public Socket connetti() {
		
		System.out.println("CLIENT Partito in esecuzione\n");
		try
		{		
			tastiera = new BufferedReader(new InputStreamReader(System.in));
			miosocket = new Socket(nomeServer, portaServer);
			outVersoServer = new ObjectOutputStream(miosocket.getOutputStream());
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
		
		for(;;)
		try {
			if(flag.equalsIgnoreCase("no"))
			{
				System.out.print("Inserire il codice del casello di entrata: ");
				stringaUtente = tastiera.readLine();
				cas = Integer.parseInt(stringaUtente);
				if(cercaCasello(cas))		
					System.out.println("\nSEI AL KM: " + getCasello(cas));
				else
					System.out.println("\n[ATTENZIONE]Il casello selezionato non esiste");
				System.out.print("\nInserisci la targa del tuo veicolo: ");
				targa = tastiera.readLine();
				System.out.print("\nInserisci la classe (A, B3, B4, B5): ");
				classe = tastiera.readLine();
				Veicolo vec = new Veicolo(cas, targa, classe, 0, 0);
				outVersoServer.writeObject(vec);
				stringaRicevutaDalServer = inDalServer.readLine();
				System.out.println("RICEVUTO: "+stringaRicevutaDalServer);
				stringaRicevutaDalServer = inDalServer.readLine();
				System.out.println("RICEVUTO: "+stringaRicevutaDalServer);
				
				System.out.print("Stai uscendo dall'autostrada? (Si/No): ");
				flag = tastiera.readLine();
			}else{
				System.out.print("Inserisci il codice del casello di uscita: ");
				stringaUtente = tastiera.readLine();
				cas2 = Integer.parseInt(stringaUtente);
				if(cercaCasello(cas2))		
					System.out.println("\nSEI AL KM: " + getCasello(cas2));
				else
					System.out.println("\n[ATTENZIONE]Il casello selezionato non esiste");
				Veicolo vec = new Veicolo(cas, targa, classe, cas2, 1);
				outVersoServer.writeObject(vec);
			}
		}catch(Exception e) {}
		
	}
	
	
	public static void main(String[] args) {
		ClientStr cliente = new ClientStr();
		cliente.connetti();
		cliente.comunica();

	}
	
	public boolean cercaCasello(int cod_cas) 
	{
		BufferedReader reader;
		try {
			reader = new BufferedReader(new FileReader("A14.txt"));
			String line = reader.readLine();
			while (line != null) {
				String[] split = line.split(",");
				int cas = Integer.parseInt(split[2]);
				if(cas == cod_cas)
				{
					reader.close();
					return true;
				}
				line = reader.readLine();
			}
			reader.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
		
		return false;
	}
	
	public double getCasello(int cod_cas) 
	{
		BufferedReader reader;
		try {
			reader = new BufferedReader(new FileReader("A14.txt"));
			String line = reader.readLine();
			while (line != null) {
				String[] split = line.split(",");
				int cas = Integer.parseInt(split[2]);
				if(cas == cod_cas)
				{
					double km = Double.parseDouble(split[0]);
					reader.close();
					return km;
				}
				line = reader.readLine();
			}
			reader.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
		
		return -1;
	}
	
	public String getCitta(int cod_cas)
	{
		BufferedReader reader;
		try {
			reader = new BufferedReader(new FileReader("A14.txt"));
			String line = reader.readLine();
			while (line != null) {
				String[] split = line.split(",");
				int cas = Integer.parseInt(split[2]);
				if(cas == cod_cas)
				{
					String citta = split[1];
					reader.close();
					return citta;
				}
				line = reader.readLine();
			}
			reader.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
		
		return null;
	}
}
