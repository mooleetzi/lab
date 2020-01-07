package bean;

public class Coffee {
    private Bean bean;
    private Flavour flavour;
    public Coffee(Bean bean,Flavour flavour){
        this.bean=bean;
        this.flavour=flavour;
    }
    public long getPrice(){
        return bean.getPrice()+flavour.getPrice();
    }
}
