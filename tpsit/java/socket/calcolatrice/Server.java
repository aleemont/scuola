import java.io.*;
import java.net.*;
import java.util.*;

public class Server
{
	ServerSocket server = null;
	double operando1 = 0;
	double operando2 = 0;
	String operatore;
	double res = 0;
	Socket client = null;
	BufferedReader in;
	DataOutputStream out;

	public Socket attesa()
	{
		try
		{
			System.out.println("1. SERVER attivo ...");

			server = new ServerSocket(8081);

			client = server.accept();

			server.close();

			in = new BufferedReader(new InputStreamReader (client.getInputStream()));
			out = new DataOutputStream(client.getOutputStream());
		}
		catch(Exception e)
		{
			System.out.println(e.getMessage());
			System.out.println("Errore durante il wait");
			System.exit(1);
		}
		return client;
	}

	public void chat()
	{
	      try{
			System.out.println("3. Connesso al client. In attesa di ricevere gli operandi...");
			operando1 = Double.parseDouble(in.readLine());
			System.out.println("6. Ricevuto primo operando dal client: " + operando1);
			operando2 = Double.parseDouble(in.readLine());
			System.out.println("9. Ricevuto Secondo operando dal client: " + operando2);
			operatore = in.readLine();
			System.out.println("12. Ricevuto Secondo operando dal client: " + operatore);
			switch(operatore)
			{
				case "+": res = operando1 + operando2; break;
				case "-": res = operando1 - operando2; break;
				case "/": res = operando1 / operando2; break;
				case "*": res = operando1 * operando2; break;
				case "^": res = Math.pow(operando1, operando2); break;
			}

			System.out.println("13. Calcolato: " + res);
			System.out.println("14. Invio il risultato al client");
			out.writeBytes(String.valueOf(res));

			System.out.println("16. Chiudo la connessione");
			client.close();
			} catch(IOException e){System.exit(1);}
	}

	public static void main(String args[])
	{
		Server ser = new Server();
		ser.attesa();
		ser.chat();
	}
}
