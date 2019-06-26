<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>用户信息</title>
    <style>
        #user{
            height: 98vh;
            width: 98vw;
        }
    </style>
</head>
<body>
    <div id="user">
        <span>
            <a href="./../index.jsp">返回主页</a>
        </span>
        <%
            Integer login=(Integer)session.getAttribute("login");
            String username=null;
            String icon=null;
            if (login==null||login!=4)
                out.print("请先登录");
            else{//登录成功标志
                username=(String)session.getAttribute("username");
                icon=(String)session.getAttribute("icon");
                out.print("<p>欢迎你  " +username+"!</p>");
                String file="./../uploadFile/"+icon;
                out.print("<a href='/freeStu/download?file="+icon+"'>"+"<img width=100 height=100 src='"+file+"'></a>");
                out.print("点击头像下载");
            }
        %>
    </div>
</body>
</html>
