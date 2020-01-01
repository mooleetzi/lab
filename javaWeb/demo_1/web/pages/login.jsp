<%@ taglib prefix="s" uri="/struts-tags"%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title><s:text name="title"></s:text></title>
</head>
<body>
<s:i18n name="globalMessages">
    <span><s:text name="check"></s:text></span>
    <a href="changeLocale?request_locale=zh_CN"><s:text name="chinese"></s:text></a>
    <a href="changeLocale?request_locale=en_US"><s:text name="english"></s:text></a>
    <br/>
    <h3><s:text name="title"></s:text></h3>
    <form action="Login!manager" method="post">
        <p><s:text name="manager"></s:text>&nbsp;<s:text name="login"></s:text></p>
        <label>
            <s:text name="username"></s:text>:<input type="text" name="username">
            <s:fielderror fieldName="Musername"/>
        </label>
        <br>
        <label>
            <s:text name="account"></s:text>:<input type="text" name="account">
            <s:fielderror fieldName="Maccount"/>
        </label>
        <s:fielderror fieldName="notEqual"/>
        <s:fielderror fieldName="notManager" />
        <br>
        <input type="submit" value="<s:text name="submit"/>">
    </form>
    <form action="Login_normal" method="post">
        <p><s:text name="normal"></s:text>&nbsp;<s:text name="login"></s:text></p>
        <label>
            <s:text name="username"></s:text>:<input type="text" name="username">
            <s:fielderror fieldName="Nusername"/>
        </label>
        <br>
        <label>
            <s:text name="account"></s:text>:<input type="text" name="account">
            <s:fielderror fieldName="Naccount"/>
        </label>
        <br>
        <s:fielderror fieldName="notEqual"/>
        <s:fielderror fieldName="notNormal" />
        <input type="submit" value="<s:text name="submit"/>">
    </form>
</s:i18n>
</body>
</html>
