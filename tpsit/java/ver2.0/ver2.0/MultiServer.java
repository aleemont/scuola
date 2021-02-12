
import java.io.*;
import java.net.*;
import java.util.*;

/**
 * Realizzazione di un Server TCP Concorrente
 * 
 * 
 * @author Vito RUSSO 
 * @version 1.0
 */
   
    public class MultiServer{
        public void start(){
            try{
                ServerSocket serverSocket = new ServerSocket(6789);
                for (;;)
                {
                    System.out.println(" 1 Server in attesa ... ");
                    Socket socket = serverSocket.accept();
                    System.out.println(" 3 Server socket " + socket);
                    ServerThread serverThread = new ServerThread(socket);
                    serverThread.start();
                }
            }
            catch (Exception e) {
                System.out.println(e.getMessage());   
                System.out.println("Errore durante l'istanza del server!");
                System.exit(1);
            }
        }
    
    
    public static void main(String args[]) 
    {
        MultiServer tcpServer = new MultiServer();
        tcpServer.start();
    }
}
