package action;

import POJO.TUser;
import com.opensymphony.xwork2.ActionContext;
import com.opensymphony.xwork2.ActionSupport;
import com.opensymphony.xwork2.ModelDriven;
import com.sun.deploy.util.StringUtils;
import org.hibernate.Session;
import org.hibernate.SessionFactory;
import org.hibernate.Transaction;
import org.hibernate.cfg.Configuration;
import POJO.QueryImpl;
import org.hibernate.jpamodelgen.util.StringUtil;

import java.util.Map;

public class MySqlUtils extends ActionSupport implements ModelDriven<QueryImpl> {
    private QueryImpl query=new QueryImpl();
    private Session getSession(){
        //创建Session工厂对象
        SessionFactory factory = new Configuration().configure().buildSessionFactory();
        //得到Session对象
        return factory.openSession();
    }
    public String userQueryByUsername(){
        if (query.getUsername()!=null){
            Session session=getSession();
            Transaction transaction=session.beginTransaction();
            transaction.begin();
            TUser tUser=null;
            try {
                String username=query.getUsername();
                tUser= (TUser) session.createQuery("from TUser where username="+username).uniqueResult();
            }catch (Exception e){}
            finally {
                transaction.commit();
                session.close();
            }
            if (tUser!=null) {
                ActionContext.getContext().getSession().put("userResult", tUser);
                return SUCCESS;
            }
        }
        return ERROR;
    }
    @Override
    public QueryImpl getModel() {
        return query;
    }
}
