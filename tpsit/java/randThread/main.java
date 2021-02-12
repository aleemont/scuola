import java.util.concurrent.BlockingQueue;
import java.util.concurrent.ArrayBlockingQueue;
class main{
  public static final int BUFFER_DIM = 3;
  public static void main(String[] args){
      BlockingQueue<Integer> buffer = new ArrayBlockingQueue<Integer>(BUFFER_DIM);
      Gen producer = new Gen(buffer);
      Print consumer = new Print(buffer);
      try{
        producer.start();
        consumer.start();
        producer.join();
        consumer.join();
      }catch(InterruptedException ie){
        System.out.println("Fatal: " +ie);
      }
  }
}
