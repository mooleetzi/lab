package prototype;

public class User {
    private Player prototype;
    private Player copy;

    public User(){}
    public User(Player o){
        prototype=o;
        try {
            copy = (Player) prototype.clone();
        }catch (Exception e){}
    }
    public void setPrototype(Player prototype) {
        this.prototype = prototype;
        try {
         copy=(Player) this.prototype.clone();
        }catch (Exception e) {}
    }
    public void setName(String name){
        copy.setName(name);
    }
    public void setGender(String gender){
        copy.setGender(gender);
    }
}
