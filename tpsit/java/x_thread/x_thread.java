import java.util.concurrent.TimeUnit;

public class x_thread implements Runnable {

	private int pos;
	Object mutex = new Object();

	public x_thread(int pos){
		this.pos = pos;
	}

	public void run(){
		while(true){
	        for(int i=0; i<80; ++i){
	            try {
	            	coutXY(i,pos," x ");
								Thread.sleep(15);
							}catch (InterruptedException e) {System.out.println("Errore: "+e);break;}
	        }
	        for(int i=78; i>=0; i--){
	            try {
	            	coutXY(i,pos," x ");
								Thread.sleep(15);
							} catch (InterruptedException e) {System.out.println("Errore: "+e);break;}
	        }
	    }
	}

	public void coutXY(int x, int y, String s) throws InterruptedException{
		synchronized(mutex){
			System.out.println("\033["+y+";"+x+"H"+s+"\n");
		}
	}
}
