package proxy;

public class Retailer implements Factory {
    private int num[]=new int[5];
    private int sold[]=new int[5];
    @Override
    public void create(String type) {}

    @Override
    public void query(String type) {

    }

    @Override
    public void sell(String type) {

    }
    public void raise(String type){}
    public void ask(String type){}
}
