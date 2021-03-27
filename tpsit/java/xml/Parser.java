import java.io.IOException;
import java.util.*;
import javax.xml.parsers.*;
import org.w3c.dom.*;
import org.xml.sax.SAXException;

public class Parser 
{

    private List articoli;

    public Parser()
    {
        articoli = new ArrayList();
    }

    public List parseDocument(String filename) throws ParserConfigurationException, SAXException, IOException
    {
        DocumentBuilderFactory factory;
        DocumentBuilder builder;
        Document document;
        Element root, element;
        NodeList nodelist;
        Articolo articolo;
        // creazione dell’albero DOM dal documento XML
        factory = DocumentBuilderFactory.newInstance();
        builder = factory.newDocumentBuilder();
        document = builder.parse(filename);
        root = document.getDocumentElement();
        // generazione della lista degli elementi "channel"
        nodelist = root.getElementsByTagName("item");
        if (nodelist != null && nodelist.getLength() > 0) {
            for (int i = 0; i < nodelist.getLength(); i++) {
                element = (Element) nodelist.item(i);
                articolo = getArticolo(element);
                articoli.add(articolo);
            }
        }
        return articoli;
    }

    private Articolo getArticolo(Element element) 
    {
        Articolo articolo;
        String titolo = getTextValue(element, "title");
        String descrizione = getTextValue(element, "description");
        String link = getTextValue(element, "link");
        String pubDate = getTextValue(element, "pubDate");
        articolo = new Articolo(titolo, descrizione, link, pubDate);
        return articolo;
    }
    
    // restituisce il valore testuale dell’elemento figlio specificato
    private String getTextValue(Element element, String tag) 
    {
        String value = null;
        NodeList nodelist;
        nodelist = element.getElementsByTagName(tag);
        if (nodelist != null && nodelist.getLength() > 0) {
            value = nodelist.item(0).getFirstChild().getNodeValue();
        }
        return value;
    }
    
    // restituisce il valore intero dell’elemento figlio specificato
    private int getIntValue(Element element, String tag) 
    {
        return Integer.parseInt(getTextValue(element, tag));
    }
    
    // restituisce il valore numerico dell’elemento figlio specificato
    private float getFloatValue(Element element, String tag) 
    {
        return Float.parseFloat(getTextValue(element, tag));
    }

    public static void main(String[] args) 
    {
        List articoli = null;
        Parser dom = new Parser();
        try 
        {
            articoli = dom.parseDocument("https://www.ansa.it/sito/ansait_rss.xml");
        } catch (ParserConfigurationException | SAXException | IOException exception) 
        {
            System.out.println("Errore!");
        }
        // iterazione della lista e visualizzazione degli oggetti
        System.out.println("Articoli recuperati: " + articoli.size());
        Iterator iterator = articoli.iterator();
        int i=0;
        while (iterator.hasNext() && i<15) {
            System.out.println(iterator.next().toString());
            i++;
        }
    }
}
