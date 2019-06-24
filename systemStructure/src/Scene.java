import java.util.ArrayList;

public class Scene {
    private static Scene instance=null;
    private ArrayList<Player> user=new ArrayList<Player>();
    private String s1="神庙",s2="农村",s3="武器室";
    public static Scene getInstance(){
        if (instance==null)
            instance=new Scene();
        return instance;
    }
    public ArrayList<Player> getUser() {
        return user;
    }
    public void showMessages(Player u){
        user.add(u);
        System.out.println(u.getInfo()+" 进入了主场景，此场景包含"+s1+" "+s2+" "+s3);
    }
}
