<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Title</title>
</head>
<body>
<div class="register">
    <form name="register" action="register" method="post">
        <div>
            userName:<input type="text" name="username">
        </div>
        <div>
            passWord:<input type="password" name="password">
        </div>
        <div>
            passWord:<input type="password" name="passwordR">
        </div>
        <button type="submit">注册</button>
        <%
//            try {
//                int flag=(Integer)session.getAttribute("register");
//                if (flag==0)
//                    out.print("已存在用户");
//                else if (flag==-1)
//                    out.print("两次密码不一致");
//                else if (flag==1)
//                    out.print("注册成功");
//            }catch (NullPointerException e){}

        %>
    </form>

</div>
</body>
</html>
