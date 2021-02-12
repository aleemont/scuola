/**
 * La classe x_no_thread ha 2 metodi: 
 * printXY stampa la stringa s passata per parametro
 * nella posizione (y,x) attraverso la sequenza di escape ANSI.
 * 
 * barra richiama ripetutamente il metodo printXY, passandogli per parametri
 * la riga che viene letta da linea di comando, la posizione x che viene
 * assegnata da un ciclo for in aumento e in decremento.
 *
 * @Alessandro Monticelli
 * @21/10/2020
 */
class x_no_thread{
	void printXY(int x, int y, String s){
		try{
			Thread.sleep(35);
			System.out.print("\033["+y+";"+x+"H"+s);
			}
		catch(Exception e){
			System.out.println("Errore!"+e);
			}
		}
	void barra(int pos){
		while(true){
			for(int i = 0; i < 80; i++)
				printXY(i, pos, " x ");
			for(int i = 78; i>=0; i--)
				printXY(i, pos, " x ");
			}
	}
}
