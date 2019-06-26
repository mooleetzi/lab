package DAO;
import java.io.UnsupportedEncodingException;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.sql.*;
import VO.User;
import org.w3c.dom.*;
import sun.misc.BASE64Encoder;

public class UserDao {
    private XmlParse xmlParse=new XmlParse();
    private String DbDriver=null;
    private String DbUserName=null;
    private String DbPassword=null;
    private String DbUrl=null;
    private String DbInsert=null;
    private String DbUpdate=null;
    private String DbSelect=null;
    private Connection con=null;
    private String EncoderByMd5(String str) throws NoSuchAlgorithmException, UnsupportedEncodingException {
        //确定计算方法
        MessageDigest md5=MessageDigest.getInstance("MD5");
        BASE64Encoder base64en = new BASE64Encoder();
        //加密后的字符串
        String newstr=base64en.encode(md5.digest(str.getBytes("utf-8")));
        return newstr;
    }
    public UserDao(){
        String absUrl="C:\\code\\lab\\javaWeb\\freeStu\\src\\DAO\\config.xml";
        Document document=xmlParse.parse(absUrl);
        Element element=document.getDocumentElement();
        NodeList nodeList=element.getElementsByTagName("base").item(0).getChildNodes();
        for (int i=0;i<nodeList.getLength();i++){
            Node node=nodeList.item(i);
            if (node.getNodeName().equals("driver"))
                DbDriver=node.getTextContent();
            if (node.getNodeName().equals("url"))
                DbUrl=node.getTextContent();
            if (node.getNodeName().equals("user"))
                DbUserName=node.getTextContent();
            if (node.getNodeName().equals("password"))
                DbPassword=node.getTextContent();
        }
        nodeList=element.getElementsByTagName("operation").item(0).getChildNodes();
        for (int i=0;i<nodeList.getLength();i++){
            Node node=nodeList.item(i);
            if (node.getNodeName().equals("insert")){
                NodeList cur=node.getChildNodes();
                for (int j=0;j<cur.getLength();j++) {
                    Node now=cur.item(j);
                    if (now.getNodeName().equals("sql"))
                        DbInsert = now.getTextContent();
                }
            }
            if (node.getNodeName().equals("select")){
                NodeList cur=node.getChildNodes();
                for (int j=0;j<cur.getLength();j++) {
                    Node now=cur.item(j);
                    if (now.getNodeName().equals("sql"))
                        DbSelect = now.getTextContent();
                }
            }
            if (node.getNodeName().equals("update")){
                NodeList cur=node.getChildNodes();
                for (int j=0;j<cur.getLength();j++) {
                    Node now=cur.item(j);
                    if (now.getNodeName().equals("sql"))
                        DbUpdate = now.getTextContent();
                }
            }
        }
        try{
            Class.forName(DbDriver);
            con=DriverManager.getConnection(DbUrl,DbUserName,DbPassword);

        }catch (ClassNotFoundException e){
            e.printStackTrace();
        }
        catch (SQLException e){
            e.printStackTrace();
        }
    }
    public User findByUsername(String name){
        User user=null;
        try {
            PreparedStatement psm = con.prepareStatement(DbSelect);
            psm.setString(1,name);
            ResultSet rs=psm.executeQuery();
            if (rs.next()){
                user=new User();
                user.setUsername(name);
                user.setPassword(rs.getString("password"));
                user.setIcon(rs.getString("icon"));
            }
        }catch (SQLException e){
            e.printStackTrace();
        }
        return user;
    }
    public int insert(User user)throws NoSuchAlgorithmException, UnsupportedEncodingException{
        int flag=-1;
        try {
            PreparedStatement psm=con.prepareStatement(DbInsert);
            System.out.println(DbInsert);
            psm.setString(1,user.getUsername());
            psm.setString(2,EncoderByMd5(user.getPassword()));
            psm.setString(3,user.getIcon());
            flag=psm.executeUpdate();
            System.out.println(flag);
        }catch (SQLException e){
            e.printStackTrace();
        }
        return flag;
    }
    public boolean insert(String name,String pass,String icon)throws NoSuchAlgorithmException, UnsupportedEncodingException{
        User user=new User();
        user.setUsername(name);
        user.setPassword(pass);
        user.setIcon(icon);
        return insert(user)!=-1;
    }
}
