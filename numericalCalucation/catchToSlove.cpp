#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
const int maxn=110;
double a[maxn],b[maxn],c[maxn],y[maxn],x[maxn];
double l[maxn],u[maxn];
int n;
int main(){
    cin>>n;
    for (int i=0;i<n;i++){
        if (i==0)
            cin>>b[0]>>c[0];
        else if (i==n-1)
            cin>>a[n-1]>>b[n-1];
        else
            cin>>a[i]>>b[i]>>c[i];
    }
    for (int i=0;i<n;i++)
        cin>>y[i];
    l[0]=b[0];
    for (int i=0;i<n-1;i++){
        u[i]=c[i]/l[i];
        l[i+1]=b[i+1]-a[i+1]*u[i];
    }
    y[0]/=l[0];
    for (int i=1;i<n;i++)
        y[i]=(y[i]-a[i]*y[i-1])/l[i];
    x[n-1]=y[n-1];
    for (int i=n-2;i>-1;i--)
        x[i]=y[i]-u[i]*x[i+1];
    for (int i=0;i<n;i++)
        cout<<"x["<<i+1<<"]="<<x[i]<<"\n";
    return 0;
}
/*
4
2 -1
-1 3 -2
-2 4 -2
-3 5
3 1 0 -5
4 
2 1
0.5 2 0.5
0.5 2 0.5
1 2
0 3 -6 0
*/