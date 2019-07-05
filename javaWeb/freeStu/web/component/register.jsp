<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>欢迎注册呀</title>
    <link href="/freeStu/static/css/bootstrap.min.css" rel="stylesheet" type="text/css">
</head>
<body>
<%
    String flag=request.getParameter("register");
    String status[] = {"注册成功,返回首页", "用户名不能为空", "密码不能为空", "两次密码应该一致", "注册失败,请重试", "已存在此用户"};
    String registerType="请注册";
    if (flag!=null) {
        int f1=new Integer(flag);
        int f2=0;
        try {
            f2=(Integer)session.getAttribute("register");
            if (f1==f2)
                registerType=status[f1];
        } catch (NullPointerException e) {}
    }
%>
<div class="container-fluid">
    <%@include file="header.jsp"%>
    <form name="register" action="/freeStu/register" class="form-horizontal" method="post" enctype="multipart/form-data">
        <div class="form-group">
            <label for="inputEmail3" class="col-sm-1 control-label">用户名/邮箱</label>
            <div class="col-sm-10">
                <input type="text" name="username" class="form-control" id="inputEmail3" placeholder="用户名/邮箱">
            </div>
        </div>
        <div class="form-group">
            <label for="inputPassword3" class="col-sm-1 control-label">密码</label>
            <div class="col-sm-10">
                <input type="password" class="form-control" id="inputPassword3" placeholder="密码" name="password">
            </div>
        </div>
        <div class="form-group">
            <label for="inputPassword3" class="col-sm-1 control-label">重复密码</label>
            <div class="col-sm-10">
                <input type="password" class="form-control" id="inputPasswordR" placeholder="重复密码" name="passwordR">
            </div>
        </div>
        <div class="form-group">
            <label for="exampleInputFile" class="col-sm-1 control-label">请选择头像</label>
            <div class="col-sm-10">
                <input type="file" id="exampleInputFile" name="myFile">
            </div>
        </div>
        <div class="form-group">
            <div class="col-lg-offset-1 col-sm-10">
                <button type="submit" class="btn btn-default">注册</button>
            </div>
        </div>
    </form>
    <div class="col-lg-offset-1">
        <button class="btn btn-default" <%=registerType.equals("注册成功,返回首页")?"":"disabled='disabled'"%> onclick="backIndex()"><%=registerType%></button>
    </div>
</div>
<%@include file="footer.jsp"%>
<script type="text/javascript">
    function backIndex() {
        location.href="/freeStu/index.jsp";
    }
</script>
</body>
</html>
