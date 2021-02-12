package scuola.progetto;

class Malattia{
  final double I;       //Probabilità di infettare
  final double S;     //Probabilità di sviluppare sintomi
  final double L;     //Probabilità di morte
  final int D;          //Giorni tra contagio e guarigione
  public Malattia(double I, double S, double L, int D){
    this.I = I;
    this.S = S;
    this.L = L;
    this.D = D;
    final int Inc =  (int)D/6;      //Giorni di incubazione
  }

}
