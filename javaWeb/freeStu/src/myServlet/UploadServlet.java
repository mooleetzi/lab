package myServlet;
import java.io.IOException;
import javax.servlet.RequestDispatcher;
import javax.servlet.*;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import com.jspsmart.upload.File;
import com.jspsmart.upload.SmartUpload;
import com.jspsmart.upload.SmartUploadException;

public class UploadServlet extends HttpServlet {
    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        SmartUpload smartUpload=new SmartUpload();
        ServletConfig config=this.getServletConfig();
        smartUpload.initialize(config,req,resp);
        try {
            smartUpload.upload();
            File smartfile=smartUpload.getFiles().getFile(0);
            smartfile.saveAs("C:/User/13208308200:/Desktop"+smartfile.getFileName(),smartUpload.SAVE_PHYSICAL);
        }catch (SmartUploadException e){}
        String msg="上传成功";
        req.setAttribute("msg",msg);
        RequestDispatcher rd=req.getRequestDispatcher("register.jsp");
    }

}
