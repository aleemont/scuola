import java.io.Serializable;

public class Veicolo implements Serializable{
	public int INcod_cas;
	public String targa;
	public String classe;
	public int OUTcod_cas;
	public int eu; //0=Entrata 1=Uscita
	
	public Veicolo(int INcod_cas, String targa, String classe, int OUTcod_cas, int eu) {
        this.INcod_cas = INcod_cas;
        this.targa = targa;
        this.classe = classe;
        this.OUTcod_cas = OUTcod_cas;
        this.eu = eu;
	}
	
}
