package myServlet;

import DAO.UserDao;
import VO.User;
import com.jspsmart.upload.File;
import com.jspsmart.upload.SmartUpload;
import com.jspsmart.upload.SmartUploadException;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletConfig;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;
import java.security.NoSuchAlgorithmException;
import java.sql.*;
public class registerSheetFormat extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        SmartUpload smartUpload=new SmartUpload();
        ServletConfig config=this.getServletConfig();
        smartUpload.initialize(config,req,resp);
        File smartfile=null;
        try {
            smartUpload.upload();
            smartfile=smartUpload.getFiles().getFile(0);
            smartfile.saveAs("C:\\code\\lab\\javaWeb\\freeStu\\web\\uploadFile\\"+smartfile.getFileName(),smartUpload.SAVE_PHYSICAL);
            System.out.println(smartfile.getFileName());
        }catch (SmartUploadException e){
            System.out.println("上传失败"+smartfile.getFileName());
            e.printStackTrace();

        }
        String msg="上传成功";
        req.setAttribute("msg",msg);
        String username=smartUpload.getRequest().getParameter("username");
        String password=smartUpload.getRequest().getParameter("password");
        String passwordR=smartUpload.getRequest().getParameter("passwordR");
        int regis=-1;
        if (username==null||username.isEmpty()) {
            regis = 1;
            req.getSession().setAttribute("register",regis);
            resp.sendRedirect("index.jsp");
            return;
        }
        if (password==null||password.isEmpty()) {
            regis = 2;
            req.getSession().setAttribute("register",regis);
            resp.sendRedirect("index.jsp");
            return;
        }
        if (passwordR==null||!password.equals(passwordR)) {
            regis = 3;
            req.getSession().setAttribute("register",regis);
            resp.sendRedirect("index.jsp");
            return;
        }
        UserDao userDao=new UserDao();
        User user=userDao.findByUsername(username);
        boolean flag=false;
        if (user==null){
            try {
                flag=userDao.insert(username,password,smartfile==null?"":smartfile.getFileName());
                if (flag)
                    regis=0;
                else
                    regis=4;
            }catch (NoSuchAlgorithmException e){
                e.printStackTrace();
            }
        }
        else
            regis=5;
//        RequestDispatcher rd=req.getRequestDispatcher("register.jsp");
        req.getSession().setAttribute("register",regis);
        resp.sendRedirect("index.jsp");
    }

    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        this.doGet(req,resp);
    }
}
