package bean;

import java.util.Date;

public class Product {
    private Coffee coffee;
    private Date time;
    public Product(Coffee coffee,Date time){
        this.coffee=coffee;
        this.time=time;
    }

    public Coffee getCoffee() {
        return coffee;
    }

    public Date getTime() {
        return time;
    }

    public void setCoffee(Coffee coffee) {
        this.coffee = coffee;
    }

    public void setTime(Date time) {
        this.time = time;
    }
    public long getPrice(){
        return coffee.getPrice();
    }
}
