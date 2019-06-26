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
    <form name="login" action="component/dologin.jsp" method="post" onsubmit="return mySubmit()">
        login
        <div>
            userName:<input type="text" name="username" value="<%=info[0]%>">
        </div>
        <div>
            passWord:<input type="password" name="password" value="<%=info[1]%>">
        </div>
        <div>
            verification:<input type="text" name="verification" id="verification">
            <br>
            <img name="image" src="component/validate.jsp" onclick="refresh()">
        </div>
        <div>
            两周内自动登录:
            <input type="checkbox" name="autologin" id="autologin">
        </div>

        <input type="submit" value="登录">
        <p>当前登录人数:<%=(Integer)application.getAttribute("loginCnt")==null?0:(Integer)application.getAttribute("loginCnt")%></p>
    </form>
    <%
        String logstatus[]={"用户名不能为空","验证码错误","无此用户","密码错误","登录成功"};
        try {
            Integer flag=(Integer)session.getAttribute("login");
            out.print(logstatus[flag]);
        }catch (NullPointerException e){}

    %>
</div>
<script type="text/javascript">
    function refresh() {
        login.image.src="component/validate.jsp?"+new Date();
    }
    function mySubmit() {
        let v=document.getElementById("verification").value;
        if (v==undefined||v.length==0) {
            alert("请先输入验证码");
            return false;
        }
        else
            return true;
    }
</script>
</body>
</html>
