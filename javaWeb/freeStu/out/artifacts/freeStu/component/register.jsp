<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Title</title>
</head>
<body>
<div class="register">
    <form name="register" action="register" method="post" enctype="multipart/form-data">
        <div>
            userName:<input type="text" name="username">
        </div>
        <div>
            passWord:<input type="password" name="password">
        </div>
        <div>
            passWord:<input type="password" name="passwordR">
        </div>
        <div>
            请选择头像:<input type="file" name="myFile">
        </div>
        <button type="submit">注册</button>
    </form>
    ${msg}
    <%
        String status[]={"注册成功","用户名不能为空","密码不能为空","两次密码应该一致","注册失败,请重试","已存在此用户"};
        try {
            out.print(status[(Integer)(session.getAttribute("register"))]);
        }catch (Exception e){}
    %>
</div>
</body>
</html>
