import java.net.*;

public class MultiServer {
	private ServerSocket serverSocket;

	public void start() {
		try {
			serverSocket = new ServerSocket(6789);
			for(;;) 
			{
				System.out.println("Server in attesa...");
				Socket socket = serverSocket.accept();
				System.out.println("Server socket " + socket);
				ServerThread serverThread = new ServerThread(socket);
				serverThread.start();
			}
		}catch(Exception e) {
			System.out.println(e.getMessage());
			System.exit(1);
		}
	}
	
	public static void main (String[] args) {
		MultiServer tcpServer = new MultiServer();
		tcpServer.start();
	}
}
