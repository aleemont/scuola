import java.util.concurrent.BlockingQueue;

class Print extends Thread{
  private final BlockingQueue<Integer> buffer;     //istanzio una coda circolare bloccante
  //costruttore
  public Print(BlockingQueue<Integer> buffer){
    this.buffer = buffer;
  }
  //metodo eseguito dal thread
  public void run(){
      try{
        int n = 0;
        for(int i=0;i<10;++i){
            n = buffer.take();         //estraggo la testa della coda
            System.out.println(n);   //stampo il numero
          }
      }catch(InterruptedException ie){System.out.println("Errore: "+ ie);}
    }
  }
