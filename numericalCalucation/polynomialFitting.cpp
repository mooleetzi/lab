/*
    多项式拟合
 */
#include<iostream>
#include<vector>
#include<cmath>
using namespace std;
using vd=vector<double>;
class Gauss
{
private:
    vector<vd> a;
    vd b;
    int n;
    void choose(int col)
    {
        double d = a[col][col];
        int c = col;
        for (int i = col + 1; i < n; i++)
            if (fabs(a[i][col]) > fabs(d))
            {
                d = a[i][col];
                c = i;
            }
        if (c != col)
        {
            swap(a[c], a[col]);
            swap(b[c], b[col]);
        }
    }
    void debug()
    {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n + 1; j++)
                if (j < n)
                    cout << a[i][j] << "   ";
                else
                    cout << b[i] << "\n";
    }

public:
    Gauss() {}
    Gauss(int n, vector<vd> &c, vd &d)
    {
        this->n = n;
        a.assign(c.begin(),c.end()), b.assign(d.begin(),d.end());
        // for (auto x:a){
        //     for (auto y:x)
        //         cout<<y<<" ";
        //     cout<<"\n";
        // }
        // for (auto x:b)
        //     cout<<x<<" ";
        // cout<<"\n";
        run();
    }
    void getData()
    {
        cin >> n;
        for (int i = 0; i < n; i++)
        {
            vd now;
            for (int j = 0; j < n + 1; j++)
            {
                double x;
                cin >> x;
                if (j == n)
                    b.emplace_back(x);
                else
                    now.emplace_back(x);
            }
            a.emplace_back(now);
        }
        run();
    }
    void run()
    {
        for (int k = 0; k < n - 1; k++)
        {
            choose(k);
            for (int i = k + 1; i < n; i++)
                a[i][k] /= a[k][k];
            for (int i = k + 1; i < n; i++)
                for (int j = k + 1; j < n; j++)
                    a[i][j] -= a[i][k] * a[k][j];
            for (int i = k + 1; i < n; i++)
                b[i] -= a[i][k] * b[k];
        }
        b[n - 1] /= a[n - 1][n - 1];
        for (int i = n - 2; i >= 0; i--)
        {
            double c1 = 1 / a[i][i];
            double sum = 0;
            for (int j = i + 1; j < n; j++)
                sum += a[i][j] * b[j];
            b[i] = c1 * (b[i] - sum);
        }
    }
    void print()

    {
        for (int i = 0; i < n; i++)
            cout << "x" << i + 1 << "=" << b[i] << "\n";
    }
    vd getAns(){
        return b;
    }
};
struct polyFit{
    int n,len;
    vd x,y,ans,b;
    vector<vd> a;
    polyFit(vd &xx,vd &yy){
        x.assign(xx.begin(),xx.end());
        y.assign(yy.begin(),yy.end());
        len=x.size();n=2;
        init();
    }
    polyFit(){}
    polyFit(vd& xx,vd& yy,int n){
        x.assign(xx.begin(),xx.end());
        y.assign(yy.begin(),yy.end());
        len=x.size(),this->n=n;
        init();
    }
    void init(){
        for (int i=0;i<=n;i++){
            vd cur;
            for (int j=i;j<=i+n;j++){
                double now=0;
                for (int k=0;k<len;k++)
                    now+=pow(x[k],j);
                cur.emplace_back(now);
            }
            double t=0;
            for (int j=0;j<len;j++)
                t+=pow(x[j],i)*y[j];
            b.emplace_back(t);
            a.emplace_back(cur);
        }
        Gauss g(n+1,a,b);
        ans=g.getAns();
    }
    void debug(){
        for (auto x:a){
            for (auto y:x)
                cout<<y<<" ";
            cout<<"\n";
        }
        for (auto x:b)
            cout<<x<<" ";
        cout<<"\n";
    }
    vd getAns(){
        return ans;
    }
};
int main(){
    vd x,y;
    int n;
    cin>>n;
    for (int i=0;i<n;i++){
        double xx,yy;
        cin>>xx>>yy;
        x.emplace_back(xx),y.emplace_back(yy);
    }
    polyFit cal(x,y);
    vd ans(cal.getAns());
    cout<<"y=";
    for (int i=0;i<ans.size();i++){
        if (!i)
            cout<<ans[i];
        else{
            if (ans[i]>0)
                cout<<"+";
            cout<<ans[i]<<"x^"<<i;
        }
    }
    return 0;
}
/*
7
1 2
2 3
3 6
4 7
6 5
7 3
8 2

 */