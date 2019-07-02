package myServlet;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

public class download extends HttpServlet {
    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        String file=req.getParameter("file");
        resp.setContentType("application/x-download");
        String path="/uploadFile/"+file;
        resp.addHeader("Content-Disposition", "attachment;filename=" +file);
        try {
            RequestDispatcher rd=req.getRequestDispatcher(path);
            if (rd!=null)
                rd.forward(req,resp);
            resp.flushBuffer();
        }catch (Exception e){
            e.printStackTrace();
        }
        System.out.println(path);
//        resp.sendRedirect("index.jsp");
    }

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        this.doPost(req,resp);
    }
}
