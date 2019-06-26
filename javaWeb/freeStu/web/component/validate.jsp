<%@ page import="java.awt.image.BufferedImage" %>
<%@ page import="java.awt.*" %>
<%@ page import="java.util.Random" %>
<%@ page import="myServlet.Verification" %>
<%@ page import="javax.imageio.ImageIO" %>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%
    response.setHeader("Cache-Control","no-cache");
    int width=80,height=20;
    BufferedImage bufferedImage=new BufferedImage(width,height,BufferedImage.TYPE_INT_RGB);
    Graphics g=bufferedImage.getGraphics();
    g.setColor(new Color(200,200,200));
    g.fillRect(0,0,width,height);
    Random random=new Random();
    Integer a=random.nextInt(100)+1;
    Integer b=random.nextInt(3);
    Integer c=random.nextInt(100)+1;
    char opt[]={'+','-','*'};
    Verification verification=Verification.getInstance();
    String rndStr=a.toString()+opt[b]+c.toString();
    Integer ans=verification.cal(a,b,c);
    session.setAttribute("rndAns",ans);
    g.setColor(Color.BLACK);
    g.setFont(new Font("",Font.PLAIN,20));
    g.drawString(rndStr,10,17);
    for (int i=0;i<100;i++){
        int x=random.nextInt(width);
        int y=random.nextInt(height);
        g.drawOval(x,y,1,1);
    }
    ImageIO.write(bufferedImage,"JPEG",response.getOutputStream());
    out.clear();
    out=pageContext.pushBody();
%>
