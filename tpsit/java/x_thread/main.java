import java.util.Scanner;

public class main {

	public static void main(String[] args) throws InterruptedException {

		try (Scanner in = new Scanner(System.in))
		{
			System.out.println("Inserire la prima riga: ");

			int i = Integer.parseInt(in.nextLine());
      Thread[] thr = new Thread[3];
      for(int c=0;c<3;c++){
            thr[c] = new Thread(new x_thread(i+=3));
			      thr[c].start();
		}
	}
}
}
