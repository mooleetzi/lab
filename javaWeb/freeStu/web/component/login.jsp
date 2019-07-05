<%@ page contentType="text/html;charset=UTF-8" language="java" import="java.sql.*" %>
<html>
<head>
    <title>欢迎登录呀</title>
    <link href="/freeStu/static/css/bootstrap.min.css" rel="stylesheet" type="text/css">
</head>
<body>
<%
    String logstatus[]={"用户名不能为空","验证码错误","无此用户","密码错误","登录成功,返回首页"};
    String logtype="请登录";
    String flag=request.getParameter("login");
    if (flag!=null) {
        int f1 = new Integer(flag);
        int f2=0;
        try {
            f2=(Integer) session.getAttribute("login");
            if (f1==f2)
                logtype=logstatus[f1];
        }catch (NullPointerException e){}
    }

%>
<div class="container-fluid">
    <%@include file="header.jsp"%>
    <%
        String info[]={"",""};
        Cookie ck[]=request.getCookies();
        if (ck!=null)
            for (Cookie c :ck)
                if (c.getName().trim().equals("login"))
                    info = c.getValue().split("#");

    %>
    <form class="form-horizontal" name="login" action="dologin.jsp" method="post" onsubmit="return mySubmit()">
        <div class="form-group">
            <label for="inputEmail3" class="col-sm-1 control-label">用户名/邮箱</label>
            <div class="col-sm-10">
                <input type="text" name="username" value="<%=info[0]%>" class="form-control" id="inputEmail3" placeholder="用户名/邮箱">
            </div>
        </div>
        <div class="form-group">
            <label for="inputPassword3" class="col-sm-1 control-label">密码</label>
            <div class="col-sm-10">
                <input type="password" class="form-control" id="inputPassword3" placeholder="密码" name="password" value="<%=info[1]%>">
            </div>
        </div>
        <div class="form-group">
            <label for="inputPassword3" class="col-sm-1 control-label">验证码</label>
            <div class="col-sm-10">
                    <input type="text" name="verification" id="verification" class="form-control" placeholder="验证码">
                    <img name="image" src="/freeStu/component/validate.jsp" onclick="refresh()">
            </div>
        </div>
        <div class="form-group">
            <div class="col-sm-offset-1 col-sm-10">
                <div class="checkbox">
                    <label>
                        <input type="checkbox" name="autologin"> 两周内自动登录
                    </label>
                </div>
            </div>
        </div>
        <div class="form-group">
            <div class="col-sm-offset-1 col-sm-10">
                <button type="submit" class="btn btn-default">登录</button>
            </div>
        </div>
    </form>
    <div class="col-sm-offset-1 col-sm-5">
        <button class="btn btn-default" <%=logtype.equals("登录成功,返回首页")?"":"disabled='disabled'"%> onclick="backIndex()"><%=logtype%></button>
    </div>
</div>
<%@include file="footer.jsp"%>
<script type="text/javascript">
    function refresh() {
        login.image.src="/freeStu/component/validate.jsp?"+new Date();
    }
    function mySubmit() {
        let v=document.getElementById("verification").value;
        if (v==undefined||v.length==0) {
            alert("请先输入验证码");
            return false;
        }
        else
            return true;
    }
    function backIndex() {
        location.href="/freeStu/index.jsp";
    }
</script>
</body>
</html>
