import java.net.*;
import java.time.*;
import java.time.format.*;
import java.util.concurrent.TimeUnit;
import java.io.*;

class ServerThread extends Thread {
	
	ServerSocket server = null;
	Socket client = null;
	String stringaRicevuta = null;
	String nome = null;
	String stringaModificata = null;
	BufferedReader inDalClient;
	DataOutputStream outVersoClient;
	private BufferedReader read;
	double distanza;
	
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
		InputStream inputStream = client.getInputStream();
		
		ObjectInputStream inDalClient = new ObjectInputStream(inputStream);
		outVersoClient = new DataOutputStream(client.getOutputStream());

		for(;;) {
			try {
				Veicolo auto = (Veicolo) inDalClient.readObject();
				if(auto.eu == 0)
				{
					System.out.println("REGISTRATO VEICOLO IN ENTRATA");
					System.out.println("Casello: " + auto.INcod_cas);
					System.out.println("Targa: " + auto.targa);
					System.out.println("Classe: "+ auto.classe);
				}else {
					LocalDateTime myDateObj = LocalDateTime.now(); 
					DateTimeFormatter myFormatObj = DateTimeFormatter.ofPattern("dd/MM/yyyy,HH:mm");  
					String dataora = myDateObj.format(myFormatObj); 
					System.out.println("REGISTRATO VEICOLO IN ENTRATA");
					System.out.println("Casello: " + auto.INcod_cas);
					System.out.println("Targa: " + auto.targa);
   					System.out.println("Classe: "+ auto.classe);    
					distanza = distanza(auto.INcod_cas, auto.OUTcod_cas);
					double p = prezzo(distanza, auto.classe);
					String prezzo = Double.toString(p);

					System.out.println("Emetto il biglietto");
					System.out.println("Prezzo: "+p);
					System.out.println(dataora);
					System.out.println("INGRESSO: "+getCitta(auto.INcod_cas));
					System.out.println("USCITA: "+getCitta(auto.OUTcod_cas));
					String send = prezzo+"|"+dataora + "|"+getCitta(auto.INcod_cas)+ "|"+getCitta(auto.OUTcod_cas);
					outVersoClient.writeBytes(send + '\n');
				}
				rec(auto);
			}catch(IOException e) {}
			
			System.out.println("\nAlzo la sbarra");
            outVersoClient.writeBytes("Sbarra alzata, puoi passare!" + '\n');
            TimeUnit.SECONDS.sleep(1);
            System.out.println("Abbasso la sbarra");
            outVersoClient.writeBytes("Sbarra abbassata!" + '\n');	
		}
	}

	public void rec(Veicolo v) throws IOException {
		int numProg = setProgNum();
		int cod_cas = v.INcod_cas;
		String targa = v.targa;
		String classe = v.classe;
		
	    
	    LocalDateTime myDateObj = LocalDateTime.now(); 
	    DateTimeFormatter myFormatObj = DateTimeFormatter.ofPattern("dd/MM/yyyy,HH:mm");  
	    String dataora = myDateObj.format(myFormatObj); 
	    

	    File file = new File("registro.txt");
		FileWriter myWriter = new FileWriter(file, true);
	    myWriter.write(numProg+","+cod_cas+","+dataora+","+targa+","+classe+","+v.eu+"\n");
	    myWriter.close();
	}
	
	public int setProgNum() 
	{	
		String line = null;
		try {

			File f = new File("registro.txt"); 
			if(f.exists())
			{
				read = new BufferedReader(new FileReader("registro.txt"));
				String line2 = null;
				while ((line = read.readLine()) != null) {
					line2 = line;
				}
				String[] split = line2.split(",");
				int progNum = Integer.parseInt(split[0]);
				
				return progNum+1;
			}else {

				return 1;
			}
			
		} catch (Exception e) {
			e.printStackTrace();
		}
		
		return -1;
	}
	
	public double distanza(int INcod_cas, int OUTcod_cas) 
	{	
		BufferedReader reader;
		double kmIN = 0;
		double kmOUT = 0;
		String line = null;
		try {
			reader = new BufferedReader(new FileReader("A14.txt"));
			line = reader.readLine();
			while(line != null) {
				String[] split = line.split(",");
				int cas = Integer.parseInt(split[2]);
				if(cas == INcod_cas)
				{
					kmIN = Double.parseDouble(split[0]);

				}else if(cas == OUTcod_cas) {
					kmOUT = Double.parseDouble(split[0]);
				}
				line = reader.readLine();
			}
			distanza = kmOUT - kmIN;
			if(distanza < 0)
				distanza = distanza*-1;
			reader.close();
			
			return distanza;
		} catch (IOException e) {
			e.printStackTrace();
		}
		
		return -1;
	
	}
	
	public double prezzo(double dist, String classe) {
		double p = 0;
		switch(classe) {
			case "A":
				p = 0.07231 * dist;
				break;
			case "B3":
				p = 0.07401 * dist;
				break;
			case "B4":
				p = 0.09862 * dist;
				break;
			case "B6":
				p = 0.17530 * dist;
				break;
			default:
				return -1;
				
		}
		return p;
	}
	
	public String getCitta(int cod_cas)
	{
		String line = null;
		BufferedReader reader;
		try {
			reader = new BufferedReader(new FileReader("A14.txt"));
			line = reader.readLine();
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
