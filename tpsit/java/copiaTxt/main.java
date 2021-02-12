import java.io.*;
import java.nio.*;
import java.util.concurrent.*;

class main{
      public static final int BUFFER_DIM = 1024;
      public static final int BUFFER_SIZE = 64;
      public static void main(String args[]) throws Exception{
            BlockingQueue<String> buf = new ArrayBlockingQueue<String>(BUFFER_SIZE);  //istanzio un oggetto di classe ArrayBlockinQueue di tipo String, che è una lista circolare bloccante.
            fread leggi = new fread(buf, args[0]);
            fwrite scrivi = new fwrite(buf, args[1]);
            try{
              leggi.start();
              scrivi.start();
              leggi.join();       //attendo che il thread 0 muoia
              scrivi.join();      //attendo che il thread 1 muoia
            }catch(InterruptedException ie){System.out.println("Errore: "+e);}
        }
}
