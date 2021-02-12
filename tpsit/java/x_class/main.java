/**
 *
 * @Alessandro Monticelli
 * @21/10/2020
 */

import java.util.Scanner;

class main{
	public static void main(String[] args){
		x_no_thread Stampa = new x_no_thread();
		int r = 0;
		Scanner keyboard = new Scanner(System.in);
		System.out.print("Inserire riga: ");
		r = keyboard.nextInt();
		Stampa.barra(r);
		}
}
