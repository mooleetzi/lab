/*
    龙格-库塔求解常微分方程初值
 */
#include<iostream>
#include<cmath>
#include<vector>
using namespace std;
inline double f(double x,double y){
    return y-2*x/y;
}
struct rungeKutta{
    double x0,y0,h,n;
    vector<pair<double,double>> ans;
    rungeKutta(double a,double b,double c,double d){
        x0=a,y0=b,h=c,n=d;
        init();
    }
    rungeKutta(){}
    void init(){
        int tot=n;
        while(tot--){
            double x1=x0+h;
            double k1=f(x0,y0),k2=f(x0+h/2,y0+h/2*k1),k3=f(x0+h/2,y0+h/2*k2),k4=f(x1,y0+h*k3);
            double y1=y0+h/6*(k1+2*k2+2*k3+k4);
            ans.emplace_back(make_pair(x1,y1));
            x0=x1;
            y0=y1;
        }
    }
    vector<pair<double,double>> getAns(){
        return ans;
    }
};
int main(){
    double x,y,h,n;
    cin>>x>>y>>h>>n;
    rungeKutta cal(x,y,h,n);
    vector<pair<double,double>> ans=cal.getAns();
    for (auto x:ans)
        cout<<"f("<<x.first<<")="<<x.second<<"\n";
    return 0;
}