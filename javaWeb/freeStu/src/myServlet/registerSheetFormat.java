package myServlet;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;
import java.sql.*;
public class registerSheetFormat extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        String username=req.getParameter("username");
        String password=req.getParameter("password");
        String passwordR=req.getParameter("passwordR");
        PrintWriter out=resp.getWriter();
        if (username==null||username.isEmpty()) {
            out.println("用户名不能为空");
            return;
        }
        if (password==null||password.isEmpty()){
            out.println("密码不能为空");
            return;
        }
        if (passwordR==null||!password.equals(passwordR)){
            out.println("两次密码应该一致");
            return;
        }
        String JDriver = "com.microsoft.sqlserver.jdbc.SQLServerDriver";
        String connectDB = "jdbc:sqlserver://127.0.0.1:1433;DatabaseName=javaWebDb";
        try {
            Class.forName(JDriver);
            String user = "sa";
            String pass = "sqlserver2017";
            Connection con = DriverManager.getConnection(connectDB, user, pass);
            Statement cmd = con.createStatement();
            PreparedStatement psm = con.prepareStatement("select * from userTable where username=?");
            psm.setString(1,username);
            ResultSet rs=psm.executeQuery();
            if (rs.next()){
                out.println("已存在用户"+username);
                return;
            }
        }catch (ClassNotFoundException e){
            out.println("查询信息失败，请重试");
            return;
        }
        catch (SQLException e){
            out.println("查询信息失败，请重试");
            return;
        }
        try {
            Class.forName(JDriver);
            String user = "sa";
            String pass = "sqlserver2017";
            Connection con = DriverManager.getConnection(connectDB, user, pass);
            Statement cmd = con.createStatement();
            PreparedStatement ps = con.prepareStatement("insert into userTable values (?,?)");
            ps.setString(1,username);
            ps.setString(2,password);
            ps.executeUpdate();
        }catch (ClassNotFoundException e){
            out.println("插入信息失败，请重试");
            return;
        }
        catch (SQLException e){
            out.println("插入信息失败，请重试");
            return;
        }
        out.println("注册成功");
    }

    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        this.doGet(req,resp);
    }
}
