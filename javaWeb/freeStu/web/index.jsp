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
    <script src="https://cdn.bootcss.com/jquery/3.4.1/jquery.min.js"></script>
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
<script type="text/javascript">
</script>
<%@include file="component/footer.jsp" %>
</body>
<script src="static/js/index.js">
</script>
</html>
