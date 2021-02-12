import java.net.*;
import java.io.*;

class ServerThread extends Thread {
	
	ServerSocket server = null;
	Socket client = null;
	String stringaRicevuta = null;
	String nome = null;
	String stringaModificata = null;
	BufferedReader inDalClient;
	DataOutputStream outVersoClient;
	
	public ServerThread(Socket socket) {
		this.client = socket;
	}
	
	public void run() {
		try {
			comunica();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	
	public void comunica() throws Exception{
		inDalClient = new BufferedReader(new InputStreamReader(client.getInputStream()));
		outVersoClient = new DataOutputStream(client.getOutputStream());
		nome = inDalClient.readLine();
		for(;;) {
			stringaRicevuta = inDalClient.readLine();
			if(stringaRicevuta == null || stringaRicevuta.equals("FINE")) {
				outVersoClient.writeBytes(stringaRicevuta+"CHIUSURA CONNESSIONE"+"\n");
				System.out.println("Echo sul server: "+ stringaRicevuta);
				break;
			}else{
                outVersoClient.writeBytes(stringaRicevuta + '\n');
                stringaRicevuta = nome + ": " + stringaRicevuta;
				System.out.println(stringaRicevuta);
			}
			
		}
		outVersoClient.close();
		inDalClient.close();
		System.out.println("Chiusura socket "+ client);
		client.close();
	}
}
