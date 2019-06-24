<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>allnews</title>
</head>
<body>
    <%
        Integer flag=(Integer)session.getAttribute("login");
        if (flag==null||flag!=1)
            out.print("<p style='position:fixed'>请您登录</p>");
        else
            out.print("");
    %>
</body>
</html>
