<%@ page contentType="text/html;charset=UTF-8" language="java" import="java.sql.*" %>
<html>
<head>
    <title>login</title>
</head>
<body>
<div class="login">
    <%
        String info[]={"",""};
        Cookie ck[]=request.getCookies();
        if (ck!=null)
            for (Cookie c :ck)
                if (c.getName().trim().equals("login"))
                    info = c.getValue().split("#");

    %>
    <form name="login" action="component/dologin.jsp" method="post">
        login
        <div>
            userName:<input type="text" name="username" value="<%=info[0]%>">
        </div>
        <div>
            passWord:<input type="password" name="password" value="<%=info[1]%>">
        </div>
        <div>
            两周内自动登录:
            <input type="checkbox" name="autologin" id="autologin">
        </div>
        <input type="submit" value="登录">
        <p>当前登录人数:<%=(Integer)application.getAttribute("loginCnt")==null?0:(Integer)application.getAttribute("loginCnt")%></p>
    </form>
    <%
        try {
            int flag=(Integer)session.getAttribute("login");
            if (flag==1)
                out.print("登录成功");
            else if (flag==0)
                out.print("密码错误");
            else if (flag==-1)
                out.print("账号不存在");
        }catch (NullPointerException e){}

    %>
</div>
</body>
</html>
