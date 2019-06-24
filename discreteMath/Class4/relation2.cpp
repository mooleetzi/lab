#include<bits/stdc++.h>
//#define local
#define rep(i,x,y) for (int i=x;i<y;i++)
#define mt(a,x) memset(a,x,sizeof a)
using namespace std;
map<char,int> node;
char m[100];
int mat[10][10];
int n,q;
bool zifan(int p[][10]);
bool trans(int p[][10]);
bool duichen(int p[][10]);
bool allsame(int p[][10]);
void print_gx(int [][10]);
void print_djl(int p[][10]);
int main(){
    cin>>n>>q;
    mt(mat,0);
    rep(i,0,n){
        char ch;
        cin>>ch;
        node[ch]=i;
        m[i]=ch;
    }
    rep(i,0,q){
        char c1,c2;
        cin>>c1>>c2;
        mat[node[c1]][node[c2]]=1;
    }
    print_gx(mat);
    cout<<"是否是等价关系:"<<((allsame(mat)==1)?"是":"否")<<"\n";
    if (allsame(mat))
        print_djl(mat);
    return 0;
}
bool zifan(int p[][10]){
    rep(i,0,n)
        if (!p[i][i])
            return 0;
    return 1;
}
bool trans(int p[][10]){
    int a[10][10];
    mt(a,0);
    rep(k,0,n)
        rep(i,0,n)
            rep(j,0,n)
                a[k][i]+=p[k][j]*p[j][i];
    rep(i,0,n)
        rep(j,0,n)
            if (!p[i][j]&&a[i][j])
                return 0;
    return 1;
}
bool duichen(int p[][10]){
    rep(i,0,n)
        rep(j,0,n)
            if (p[i][j]&&!p[j][i])
                    return 0;
    return 1;
}
bool allsame(int p[][10]){
    if (duichen(p)&&zifan(p)&&trans(p))
        return 1;
    return 0;
}
void print_gx(int p[][10]){
    cout<<"此关系的关系矩阵表示:\n";
    rep(i,0,n){
        rep(j,0,n)
            cout<<p[i][j]<<" ";
        cout<<"\n";
    }
}
void print_djl(int p[][10]){
    rep(i,0,n){
        cout<<m[i]<<"的等价类:[";
        rep(j,0,n)
            if (p[i][j])
                cout<<m[j]<<" ";
        cout<<"]\n";
    }
}
