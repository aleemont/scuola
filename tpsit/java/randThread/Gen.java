import java.util.concurrent.BlockingQueue;

class Gen extends Thread{
    private final BlockingQueue<Integer> buffer; //istanzio una coda circolare bloccante
    //costruttore
    public Gen(BlockingQueue<Integer> buffer){
      this.buffer = buffer;
    }
    //metodo eseguito dal thread
    public void run(){
      try{
            for(int i=0;i<10;++i){
                int n = (int)(Math.random()*100);      //genero un numero casuale
                buffer.put(n);      //inserisco il numero nel buffer
              }
          }catch(InterruptedException ie){System.out.println("Errore: "+ ie);}
        }
}
