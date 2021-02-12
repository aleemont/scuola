import java.io.*;
import java.util.concurrent.*;

class fwrite extends Thread{
  private final BlockingQueue<String> buffer;           //istanzio una coda circolare bloccante
  String file;        //nome del file di output
  //costruttore
  public fwrite(BlockingQueue<String> buffer, String file){
    this.buffer = buffer;
    this.file = file;
  }
  public void run(){
    try{
    FileOutputStream fout = new FileOutputStream(file);
    byte[] b;
    while(true){
      try{
         String line = new String(buffer.take());           //inserisco la testa del buffer in line
         b = new byte[line.length()];           //istanzio un array di byte di dimensioni pari alla lunghezza di line
         b = line.getBytes();           //inserisco il contenuto di line in b
         fout.write(b);             //scrivo b sul file
      }catch(InterruptedException ie){break;}
    }
  }catch(IOException e){System.out.println("Errore");}
  }
  }
