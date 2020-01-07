<%@ page import="java.util.List" %>
<%@ page import="bean.Bean" %>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@page import="xmlparser.XmlParser" %>
<%@ page import="bean.Flavour" %>
<html>
<head>
    <title>时光咖啡厅</title>
    <link href="static/css/bootstrap.min.css" rel="stylesheet" type="text/css">
    <style>
        .bean-item:hover{
            transform: scale(1.1);
            transition: all ease 1s;
        }
        .bean-item{
            transition: all ease 1s;
        }
    </style>
</head>
<body>

<div class="container-fluid center-block" style="width: 1100px;margin-top: 100px">
    <p style="text-align: center">时光咖啡屋</p>
    <form action="addCoffee">
        <%
            List<Flavour> flavours = (List<Flavour>) request.getSession().getAttribute("beans");
            if (flavours != null) {

                for (int i = 0; i < flavours.size(); i++) {
                    Flavour flavour = flavours.get(i);
        %>
        <div style="width: 200px;display: inline-block" class="bean-item">
            <p><%=flavour.getName()%>
            </p>
            <p><%=flavour.getPrice()%>
            </p>
            <input type="radio" name="bean" value="<%=flavour.getClassName()%>" >
        </div>

        <% }
        }
        else {
            response.sendRedirect("getList");
        }%>
        <input type="submit" value="确定">
    </form>


</div>
<script>


    function getQueryString(name)
    {
        var reg = new RegExp("(^|&)"+ name +"=([^&]*)(&|$)");
        var r = window.location.search.substr(1).match(reg);//search,查询？后面的参数，并匹配正则
        if(r!=null)
            return  unescape(r[2]);
        return null;
    }



</script>
</body>
</html>
