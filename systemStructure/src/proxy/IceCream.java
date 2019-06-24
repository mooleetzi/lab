package proxy;
enum IceCreamType{
    IceCreamA,IceCreamB,IceCreamC,IceCreamD,IceCreamE
}
public class IceCream {
    private IceCreamType iceCreamType=null;
    public IceCream(){}
    public IceCream(String type){
        iceCreamType=IceCreamType.valueOf(type);
    }
}
