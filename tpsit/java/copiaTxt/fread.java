import java.io.*;
import java.util.concurrent.*;

class fread extends Thread{
    private final BlockingQueue<String> buffer;           //istanzio una coda circolare bloccante
    File file;        //nome del file di output
    //costruttore
    public fread(BlockingQueue<String> buffer, String file_n){
      this.buffer = buffer;
      this.file = new File(file_n);
    }
    public void run(){
      try{
        long length = file.length();          //calcolo la lunghezza in byte del file
        InputStream fin = new FileInputStream(file);       //apro lo stream di lettura
        String line;        //stringa da inserire nel buffer
        int n_bytes = 1024;             //dimensione degli array di byte da inserire nel buffer
       do{
          try{
              if(length < 1024){
                byte[] b = new byte[(int)length];             //se length è inferiore a 1kB allora b avrà dimensione length, per evitare la lettura di byte superflui
                n_bytes = fin.read(b,0,(int)length);        //leggo length bytes dal file e li inserisco in b. Il metodo ritorna il numero di bytes letti.
                line = new String(b);             //istanzio line come una nuova Stringa contenente b
                buffer.put(line);         //inserisco line nel buffer
                break;
              }
              else{
                length -= n_bytes;            //calcolo bytes rimanenti
                byte[] b = new byte[n_bytes];
                n_bytes = fin.read(b,0,n_bytes);        //leggo n_bytes bytes dal file e li inserisco in b. Il metodo ritorna il numero di bytes letti.
                line = new String(b);           //istanzio line come una nuova Stringa contenente b
                buffer.put(line);           //inserisco line nel buffer
              }
          }catch(InterruptedException ie){System.out.println("Errore: "+ ie); }
      }while(true);
      fin.close();
    }catch(IOException e){System.out.println("Errore apertura file: "+e);}
  }
}
