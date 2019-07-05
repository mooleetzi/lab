<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%
    String path = request.getContextPath();
    String basePath = request.getScheme()+"://"+request.getServerName()+":"+request.getServerPort()+path+"/"; %>
<html>
<head>
    <title>Title</title>
    <base href="<%=basePath%>">
    <link href="static/css/header.css" type="text/css" rel="stylesheet" charset="UTF-8">
</head>
<body>
    <div class="logo-container">
        <img src="static/img/logo.png" width="156" height="156">
        <ul class="url-container">
            <li>
                <a href="page/imgdisplay.jsp">创意空间</a>
            </li>
            <li>
                <a href="page/person.jsp">个人中心</a>
            </li>
        </ul>
    </div>
</body>
</html>
