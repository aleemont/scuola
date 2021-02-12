package scuola.progetto;

class Persona{
  public String colore;           //stato (sano, asintomatico, sintomatico, guarito, morto)
  public boolean fermo;       //In movimento o fermo
  public int Vd;          //Numero di incontri in un giorno
  public Persona(String colore, boolean fermo, int Vd){
    this.colore = colore;
    this.fermo = fermo;
    this.Vd = Vd;
  }



}
