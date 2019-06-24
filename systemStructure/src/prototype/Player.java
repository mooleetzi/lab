package prototype;

public class Player implements Cloneable{
    protected String name;
    protected String gender;
    protected String clother;
    protected String skill;
    public Object clone() throws CloneNotSupportedException{
        return super.clone();
    }

    public void setGender(String gender) {
        this.gender = gender;
    }

    public void setName(String name) {
        this.name = name;
    }

    public void setClother(String clother) {
        this.clother = clother;
    }

    public void setSkill(String skill) {
        this.skill = skill;
    }
}
