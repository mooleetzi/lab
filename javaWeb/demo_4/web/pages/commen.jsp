<%@ page import="com.opensymphony.xwork2.ActionContext" %>
<%@ page import="org.apache.struts2.ServletActionContext" %>
<%@ page import="java.io.File" %>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>

<%
    String base= ServletActionContext.getServletContext().getRealPath(File.separator);
%>
<link href="/static/css/bootstrap.min.css" rel="stylesheet" type="text/css">
<script src="/static/js/jquery.min.js"></script>