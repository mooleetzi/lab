import java.util.ArrayList;

public class Player {
    private String info;
    public Player(){
        info="剑圣盖聂";
    }
    public Player(String info){
        this.info=info;
    }

    public String getInfo() {
        return info;
    }
    public void moveIn(Scene u){
        u.showMessages(this);
    }
    public ArrayList<Player> getOtherUsers(){
        ArrayList<Player> ans=Scene.getInstance().getUser();
        for (int i=0;i<ans.size();i++)
            if (ans.get(i).equals(this))
                ans.remove(i);
        return ans;
    }
}
