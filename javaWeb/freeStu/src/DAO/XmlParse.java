package DAO;
import java.io.*;
import javax.xml.parsers.*;
import org.w3c.dom.*;
import org.xml.sax.SAXException;

public class XmlParse {
    private DocumentBuilderFactory documentBuilderFactory=DocumentBuilderFactory.newInstance();
    public Document parse(String file){
        Document document=null;
        try {
            DocumentBuilder documentBuilder = documentBuilderFactory.newDocumentBuilder();
            document=documentBuilder.parse(new File(file));
        }catch (ParserConfigurationException e){
            e.printStackTrace();
        }
        catch (SAXException e){
            e.printStackTrace();
        }
        catch (IOException e){
            e.printStackTrace();
        }
        return document;
    }
}
