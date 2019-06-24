/*
    变长梯形积分计算(sinx/x)定积分
*/
#include<iostream>
#include<cmath>
using namespace std;
inline double f(double x){
    if (x==0)
        return 1;
    return sin(x)/x;
}
double getIntegral(double a,double b,double eps){
    double h=b-a;
    double t1=h/2*(f(a)+f(b));
    while(1){
        double s=0,x=a+h/2;
        while(x<b){
            s+=f(x);
            x+=h;
        }
        double t2=t1/2+h*s/2;
        if (fabs(t2-t1)<eps)
            return t2;
        h/=2;
        t1=t2;
    }
}
int main(int argc, char const *argv[])
{
    double a,b,eps;
    cin>>a>>b>>eps;
    cout<<getIntegral(a,b,eps);
    return 0;
}
