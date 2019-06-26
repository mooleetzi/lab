package myServlet;

public class Verification {
    private static Verification instance=null;
    private char opt[]={'+','-','*'};
    public static Verification getInstance() {
        if (instance==null)
            instance=new Verification();
        return instance;
    }
    public int cal(int a,int b,int c){
        char op=opt[b];
        int ans=0;
        switch (op) {
            case '+':
                ans=a+c;
                break;
            case '-':
                ans=a-c;
                break;
            case '*':
                ans=a*c;
                break;
        }
        return ans;
    }
}
