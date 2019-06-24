<%@ page contentType="text/html;charset=UTF-8" language="java" import="java.sql.*" %>
<html>
<head>
    <title>Title</title>
</head>
<body>
<%
    String JDriver = "com.microsoft.sqlserver.jdbc.SQLServerDriver";
    String connectDB = "jdbc:sqlserver://127.0.0.1:1433;DatabaseName=javaWebDb";
    Class.forName(JDriver);
    String user = "sa";
    String pass = "sqlserver2017";
    Connection con = DriverManager.getConnection(connectDB, user, pass);
    Statement cmd = con.createStatement();
    PreparedStatement psm = con.prepareStatement("select * from userTable where username=?");
    String username = request.getParameter("username");
    String passwd=request.getParameter("password");
    String passwdR=request.getParameter("passwordR");
    if (username!=null&&!username.isEmpty())
        username=username.trim();
    if (passwd!=null&&!passwd.isEmpty())
        passwd=passwd.trim();
    if (passwdR!=null&&!passwdR.isEmpty())
        passwdR=passwdR.trim();
    int flag=0;
    try {
        psm.setString(1,username);
        ResultSet rs=psm.executeQuery();
        if (rs.next()){
            flag=0;//已存在用户
        }
        else {
            if (!passwd.equals(passwdR))
                flag=-1;//两次密码不一致
            else {
                flag = 1;//注册成功
                PreparedStatement ps = con.prepareStatement("insert into userTable values (?,?)");
                ps.setString(1,username);
                ps.setString(2,passwd);
                ps.executeUpdate();
            }
        }
    }catch (Exception e){}
    finally {
        session.setAttribute("register",flag);
        response.sendRedirect("./../index.jsp");
    }
%>
</body>
</html>
