import java.io.*;
import java.net.*;
import java.util.*;

public class ServerStr
{
	ServerSocket server = null;
	Socket client = null;
	String rec = null;
	String mod = null;
	BufferedReader in;
	DataOutputStream out;

	public Socket attesa()
	{
		try
		{
			System.out.println("1. SERVER attivo ...");

			server = new ServerSocket(6789);  //apro un socket sulla porta 6789

			client = server.accept();  //apro la connessione

			server.close();

			in = new BufferedReader(new InputStreamReader (client.getInputStream())); //per ricevere
			out = new DataOutputStream(client.getOutputStream()); //per inviare
		}
		catch(Exception e)
		{
			System.out.println(e.getMessage());
			System.out.println("Errore durante l'attesa");
			System.exit(1);
		}
		return client;
	}

	public void chat()
	{
		try
		{
			System.out.println("3. Connesso al client. In attesa di ricevere la stringa...");
			rec = in.readLine(); //leggo la stringa inviata dal client
			System.out.println("6. Ricevuta la stringa dal client: " + rec);

			mod = rec.toUpperCase();  //la trasformo in MAIUSCOLO
			System.out.println("7. Invio la stringa al client: ");
			out.writeBytes(mod + '\n');   //invio la stringa trasformata al client

			System.out.println("9. Chiudo la connessione");
			client.close();
		}
	}

	public static void main(String args[])
	{
		ServerStr ser = new ServerStr();
		ser.wait();
		ser.chat();
	}
}
