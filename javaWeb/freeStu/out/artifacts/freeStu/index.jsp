<%@ page contentType="text/html;charset=UTF-8" language="java" import="java.sql.*" %>
<%!String bgc = "cyan";%>
<% String cur = request.getParameter("bgc");
    if (cur != null && !cur.isEmpty())
        bgc = cur;
%>
<html>
<head>
    <title>InfoCenter</title>
    <link href="static/css/style.css" rel="stylesheet" type="text/css" />
</head>
<body>
<%@include file="component/header.jsp" %>
<div id="app" style="background-color: <%=bgc%>">
    <div class="option">
        <%@include file="component/colorChoice.jsp"%>
    </div>
    <div class="my-login">
        <%@include file="component/login.jsp"%>
    </div>
    <div class="my-register">
        <%@include file="component/register.jsp"%>
    </div>
    <div class="slide-container">
    </div>
</div>
<script src="static/js/index.js">
</script>
<%@include file="component/footer.jsp" %>
</body>
</html>
