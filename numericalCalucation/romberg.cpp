/*
    龙贝格逐次分半加速求积分
 */
#include <iostream>
#include <cmath>
#include <vector>
using namespace std;
inline double f(double x)
{
    if (x == 0)
        return 1;
    return sin(x) / x;
}
inline void print(vector<double> x){
    for (auto xx:x)
        cout<<xx<<" ";
    cout<<"\n";
}
struct romberg
{
    vector<double> s,c,r,t;
    double a,b;
    romberg(double a,double b){
        this->a=a;
        this->b=b;
    }
    romberg(){}
    void getTn()
    {
        vector<double> ans;
        double h = b - a;
        double t1 = h / 2 * (f(a) + f(b));
        for (int i = 0; i < 4; i++)
        {
            t.emplace_back(t1);
            double s = 0, x = a + h / 2;
            while (x < b)
            {
                s += f(x);
                x += h;
            }
            double t2 = t1 / 2 + h * s / 2;
            h /= 2;
            t1 = t2;
        }
    }
    void getSn(){
        for (int i=0;i<3;i++)
            s.emplace_back(4.0/3*t[i+1]-1.0/3*t[i]);
    }
    void getCn(){
        for (int i=0;i<2;i++)
            c.emplace_back(16.0/15*s[i+1]-1.0/15*s[i]);
    }
    void getRn(){
        r.emplace_back(64.0/63*c[1]-1.0/63*c[0]);
    }
    double getInterval(){
        getTn();
        getSn();
        getCn();
        getRn();
        return r.front();
    }
    void debug(){
        print(t);
        print(s);
        print(c);
        print(r);
    }
};
int main(){
    double a,b;
    cin>>a>>b;
    romberg cal(a,b);
    cout<<cal.getInterval()<<"\n";
    return 0;
}