<%@ page contentType="text/html;charset=UTF-8" language="java" import="java.sql.*" %>
<%!String bgc = "lightblue";%>
<% String cur = request.getParameter("bgc");
    if (cur != null && !cur.isEmpty())
        bgc = cur;
%>
<html>
<head>
    <title>InfoCenter</title>
    <link href="static/css/style.css" rel="stylesheet" type="text/css" />
    <script src="https://cdn.bootcss.com/jquery/3.4.1/jquery.min.js"></script>
    <meta name="viewport" content="width=device-width,initial-scale=1,minimum-scale=1,maximum-scale=1,user-scalable=no" />
</head>
<body>
<%@include file="component/header.jsp" %>
<div id="app" style="background-color: <%=bgc%>">
    <div class="option">
        <%@include file="component/colorChoice.jsp"%>
    </div>
    <p>当前在线人数:<%=(Integer)application.getAttribute("loginCnt")==null?0:(Integer)application.getAttribute("loginCnt")%></p>
    <button class="btn btn-default" onclick="login()">登录</button>
    <button class="btn btn-default" onclick="register()">注册</button>
    <div class="slide-container">
    </div>
</div>
<%@include file="component/footer.jsp" %>
</body>
<script src="static/js/index.js">
</script>
</html>
