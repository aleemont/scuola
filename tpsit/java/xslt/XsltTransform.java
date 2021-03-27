import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.net.URL;
import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.stream.XMLStreamException;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;
import javax.xml.transform.stream.StreamSource;

import org.w3c.dom.Document;

public class XsltTransform{
    public static void main(String[] args) throws XMLStreamException,
            IOException, Exception {
        URL url = new URL("https://www.ansa.it/sito/ansait_rss.xml");
        DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
        factory.setNamespaceAware(true);
        DocumentBuilder builder = factory.newDocumentBuilder();
        Document doc = builder.parse(url.openStream());
        DOMSource source = new DOMSource(doc);

        // Creare una istanza TransformerFactory
        TransformerFactory transfomerFactory = TransformerFactory.newInstance();

        // XSLT per la trasformazione
        Transformer transformer = transfomerFactory
                .newTransformer(new StreamSource(XsltTransform.class
                        .getResourceAsStream("ansa.xslt")));

        // salvataggio del file in html
        File empTableOutput = new File("ansa.html");
        StreamResult result = new StreamResult(empTableOutput);
        transformer.transform(source, result);
        
        // visualizzazione del file sulla console
        BufferedReader br = new BufferedReader(new FileReader(empTableOutput));
        try {
            String line = null;
            while ((line = br.readLine()) != null) {
                System.out.println(line);
            }
        } finally {
            br.close();
        }
    }
}
