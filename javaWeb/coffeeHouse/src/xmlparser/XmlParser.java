

import bean.Bean;
import bean.Flavour;
import org.w3c.dom.Document;
import org.w3c.dom.NamedNodeMap;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;
import org.xml.sax.SAXException;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class XmlParser {
    private DocumentBuilderFactory dbFactory = null;
    private DocumentBuilder db = null;
    private Document document = null;
    private List<Bean> beans = null;
    private List<Flavour> flavours=null;
    private String path;
    private static XmlParser instance=null;
    private XmlParser(){
        try {
            dbFactory=DocumentBuilderFactory.newInstance();
            db=dbFactory.newDocumentBuilder();
        }catch (ParserConfigurationException e){
            e.printStackTrace();
        }
    }
    public static XmlParser getInstance(){
        if (instance==null)
            instance=new XmlParser();
        return instance;
    }
    public void setPath(String path){
        this.path=path;
    }
    public List<Bean> getBeans() throws IOException, SAXException {
        document=db.parse(path);
        NodeList nodeList=document.getElementsByTagName("bean");
        List<Bean> list=new ArrayList<>();
        for (int i=0;i<nodeList.getLength();i++){
            Bean bean=new Bean();
            Node node=nodeList.item(i);
            NamedNodeMap map=node.getAttributes();
            String name=map.getNamedItem("name").getTextContent();
            bean.setName(name);
            String path=map.getNamedItem("image").getTextContent();
            bean.setImgPath(path);
            long price=Long.valueOf(map.getNamedItem("price").getNodeValue());
            bean.setPrice(price);
            String className=map.getNamedItem("classname").getTextContent();
            bean.setClassName(className);
            list.add(bean);
        }
        return list;
    }
    public List<Flavour> getFlavours() throws IOException, SAXException {
        document=db.parse(path);
        NodeList nodeList=document.getElementsByTagName("flavour");
        List<Flavour> list=new ArrayList<>();
        for (int i=0;i<nodeList.getLength();i++){
            Flavour flavour=new Flavour();
            Node node=nodeList.item(i);
            NamedNodeMap map=node.getAttributes();
            String name=map.getNamedItem("name").getTextContent();
            flavour.setName(name);
            long price=Long.valueOf(map.getNamedItem("price").getNodeValue());
            flavour.setPrice(price);
            String className=map.getNamedItem("classname").getTextContent();
            flavour.setClassName(className);
            list.add(flavour);
        }
        return list;
    }
}
