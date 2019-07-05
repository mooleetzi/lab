<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>创意空间</title>
    <script src="https://cdn.bootcss.com/jquery/3.4.1/jquery.min.js"></script>
    <meta name="viewport" content="width=device-width,initial-scale=1,minimum-scale=1,maximum-scale=1,user-scalable=no" />
    <link href="/freeStu/static/css/bootstrap.min.css" rel="stylesheet" type="text/css">
</head>
<body>
<div class="container-fluid">
    <%@include file="/component/header.jsp"%>
    <div class="img-container">

    </div>
</div>
<%@include file="/component/footer.jsp"%>
</body>
<script>
    const response=$.ajax({url:'http://www.cdutzy.com/API/allImages',async:false}).responseJSON;
    const img=Array.from(response);
    let imgContainer=document.getElementsByClassName("img-container")[0];
    let cur=document.createElement("div");
    cur.className="row";
    for (let i=0;i<img.length;i++){
        let nowDiv=document.createElement("div");
        nowDiv.style.overflow="hidden";
        nowDiv.className="col-md-4";
        let now=document.createElement("img");
        now.className="img-responsive center-block img-rounded";
        now.src=img[i].img_url;
        nowDiv.appendChild(now);
        cur.appendChild(nowDiv);
        if ((i+1)%3==0){
            imgContainer.appendChild(cur);
            cur=document.createElement("div");
            cur.className="row";
        }
    }
</script>
</html>
