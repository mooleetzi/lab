#include<bits/stdc++.h>
//#define local
#define rep(i,x,y) for (int i=x;i<y;i++)
#define mt(a,x) memset(a,x,sizeof a)
using namespace std;
map<char,int> node;
int mat[10][10];
int n,m;
bool zifan(int p[][10]);
bool fzifan(int p[][10]);
bool trans(int p[][10]);
bool duichen(int p[][10]);
bool fduichen(int p[][10]);
void print_ni(int p[][10]);
void print_hc(int a[][10]);
void print_r(int [][10]);
void print_s(int [][10]);
void print_t(int [][10]);
int main(){
    #ifdef local
        freopen("relation.txt","r",stdin);
    #endif
    cin>>n>>m;
    mt(mat,0);
    rep(i,0,n){
        char ch;
        cin>>ch;
        node[ch]=i;
    }
    rep(i,0,m){
        char c1,c2;
        cin>>c1>>c2;
        mat[node[c1]][node[c2]]=1;
    }
    cout<<"是否自反:"<<((zifan(mat)==1)?"是":"否")<<"\n";
    cout<<"是否反自反:"<<((fzifan(mat)==1)?"是":"否")<<"\n";
    cout<<"是否传递:"<<((trans(mat)==1)?"是":"否")<<"\n";
    cout<<"是否对称:"<<((duichen(mat)==1)?"是":"否")<<"\n";
    cout<<"是否反对称:"<<((fduichen(mat)==1)?"是":"否")<<"\n";
    print_ni(mat);
    print_hc(mat);
    print_r(mat);
    print_s(mat);
    print_t(mat);
    return 0;
}
bool zifan(int p[][10]){
    rep(i,0,n)
        if (!p[i][i])
            return 0;
    return 1;
}
bool fzifan(int p[][10]){
    rep(i,0,n)
        if (p[i][i])
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
bool fduichen(int p[][10]){
    int flag=1;
    rep(i,0,n)
        if (p[i][n-i-1])
            flag=0;
    if (flag)
        return 1;
    rep(i,0,n)
        rep(j,0,n)
            if (p[i][j]&&p[j][i])
                    return 0;
    return 1;
}
void print_ni(int p[][10]){
    int a[10][10];
    mt(a,0);
    cout<<"原关系:\n";
    rep(i,0,n){
        rep(j,0,n){
            cout<<p[i][j]<<" ";
            a[i][j]=p[i][j];
        }
        cout<<"\n";
    }
    cout<<"逆关系:\n";
    rep(i,0,n){
        rep(j,0,n)
            cout<<a[j][i]<<" ";
        cout<<"\n";
    }
    return;
}
void print_hc(int a[][10]){
    cout<<"此关系上的二次幂:\n";
    int p[10][10];
    mt(p,0);
    rep(k,0,n)
        rep(i,0,n)
            rep(j,0,n)
                p[k][i]+=a[k][j]*a[j][i];
    rep(i,0,n){
        rep(j,0,n)
            cout<<p[i][j]<<" ";
        cout<<"\n";
    }
    return;
}
void print_r(int p[][10]){
    cout<<"此关系的自反闭包:\n";
    rep(i,0,n){
        rep(j,0,n)
            if (i!=j)
                cout<<p[i][j]<<" ";
            else
                cout<<1<<" ";
        cout<<"\n";
    }
    return;
}
void print_t(int p[][10]){
    cout<<"此关系的传递闭包:\n";
    rep(k,0,n)
        rep(i,0,n)
            rep(j,0,n)
                if (p[i][k]&&p[j][j])
                    p[i][j]=1;
    rep(i,0,n){
        rep(j,0,n)
            cout<<p[i][j]<<" ";
        cout<<"\n";
    }
}
void print_s(int p[][10]){
    cout<<"此关系的对称闭包:\n";
    rep(i,0,n){
        rep(j,0,n)
            if (p[i][j]||p[j][i])
                cout<<1<<" ";
            else
                cout<<0<<" ";
        cout<<"\n";
    }
    return;
}
