public class Articolo
{

    private String titolo;
    private String descrizione;
    private String url;
    private String dataPub;

    public Articolo()
    {
        this.titolo = "";
        this.descrizione = "";
        this.url = "";
        this.dataPub = "";

    }

    public Articolo(String titolo, String descrizione, String url, String dataPub)
    {
        this.titolo = titolo;
        this.descrizione = descrizione;
        this.url = url;
        this.dataPub = dataPub;
    }

    public Articolo(Articolo articolo)
    {
        this.titolo = articolo.titolo;
        this.descrizione = articolo.descrizione;
        this.url = articolo.url;
        this.dataPub = articolo.dataPub;
    }

    public String getDescrizione()
    {
        return descrizione;
    }

    public void setDescrizione(String descrizione)
    {
            this.descrizione = descrizione;
    }

    public String getTitolo()
    {
        return titolo;
    }

    public void setTitolo(String titolo)
    {
            this.titolo = titolo;
    }

    public String getUrl()
    {
        return url;
    }

	public void setUrl(String url)
    {
        this.url = url;
    }
    
    public String getDataPub()
    {
        return dataPub;
    }

    public void setPubDate(String dataPub)
    {
        this.dataPub = dataPub;
    }

    public String toString()
    {
        return "\t\t" + titolo + "\n\n" + descrizione + "\n\nURL: " + url + "\nDATA: " + dataPub + "\n\n";
    }
}
