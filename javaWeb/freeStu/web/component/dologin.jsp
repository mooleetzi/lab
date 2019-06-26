<%@ page contentType="text/html;charset=UTF-8" language="java" import="java.sql.*" %>
<%@ page import="VO.User" %>
<html>
<head>
    <title>login</title>
</head>
<body>
<jsp:useBean id="userdao" class="DAO.UserDao"></jsp:useBean>
<%
    String username = request.getParameter("username");
    String autologin = request.getParameter("autologin");
    String passwd=request.getParameter("password");
    String verification=request.getParameter("verification");
    String rndAns=session.getAttribute("rndAns").toString();
    if (username==null||username.isEmpty()) {
        session.setAttribute("login",0);//用户名不为空
        response.sendRedirect("./../index.jsp");
        return;
    }
    if (!rndAns.equals(verification)){
        session.setAttribute("login",1);//验证码错误
        response.sendRedirect("./../index.jsp");
        return;
    }
    int flag=-1;
    User user=userdao.findByUsername(username);
    if (user==null)
        flag=2;//无此用户
    else {
        boolean f=user.isEauql(passwd);
        if (f) {
            flag = 4;//登录成功
            Integer now=(Integer)application.getAttribute("loginCnt");
            if (now==null)
                application.setAttribute("loginCnt",1);
            else
                application.setAttribute("loginCnt",now+1);
        }
        else
            flag=3;//密码错误
    }
    if ("on".equals(autologin)){
        Cookie ck=new Cookie("login",username+"#"+passwd);
        ck.setMaxAge(30*24*60*60);
        ck.setPath("/freeStu");
        response.addCookie(ck);
    }
    session.setAttribute("login",flag);
    session.setAttribute("username",user.getUsername());
    session.setAttribute("icon",user.getIcon());
    response.sendRedirect("./../index.jsp");
%>
</body>
</html>
