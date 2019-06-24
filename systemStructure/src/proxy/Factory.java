package proxy;

public interface Factory {
    public void create(String type);
    public void sell(String type);
    public void query(String type);
}
