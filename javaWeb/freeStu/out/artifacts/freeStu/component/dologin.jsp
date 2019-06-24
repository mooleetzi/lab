<%@ page contentType="text/html;charset=UTF-8" language="java" import="java.sql.*" %>
<html>
<head>
    <title>login</title>
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
    String autologin = request.getParameter("autologin");
    String passwd=request.getParameter("password");
    if (username!=null&&!username.isEmpty())
        username=username.trim();
    else
        response.sendRedirect("./../index.jsp");
    if (passwd!=null&&!passwd.isEmpty())
        passwd=passwd.trim();
    if (autologin!=null&&!autologin.isEmpty())
        autologin=autologin.trim();
    if (username!=null&&!username.isEmpty()){
        psm.setString(1,username);
        ResultSet rs = psm.executeQuery();
        int flag=0;
        try {
            String password = "";
            if (rs.next()) {
                password = rs.getString("password").trim();
                if (password.equals(passwd)) {
                    flag=1;
                    if (application.getAttribute("loginCnt")==null){//application记录登录次数
                        application.setAttribute("loginCnt",1);
                    }else
                        application.setAttribute("loginCnt",(Integer)application.getAttribute("loginCnt")+1);

                } else {
//                        out.print("密码错误.");
                    flag=0;

                }
            } else {
//                    out.print("用户不存在");
                flag=-1;
            }
        } catch (SQLException e) {
            e.printStackTrace();
            flag=-1;
        }
        finally {
            if ("on".equals(autologin)){
                Cookie ck=new Cookie("login",username+"#"+passwd);
                ck.setMaxAge(30*24*60*60);
                ck.setPath("/freeStu");
                response.addCookie(ck);
            }
        }
        session.setAttribute("login",flag);
        response.sendRedirect("./../index.jsp");
    }
%>
</body>
</html>
