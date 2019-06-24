#include<iostream>
#include<cstring>
#include<fstream>
using namespace std;
const int maxn=1e2+10;
const int inf=0x3f3f3f3f;
int vis[maxn];
struct Matrix{
    int a[maxn][maxn];
    int vetNum,edgeNum;
    Matrix(){
        vetNum=edgeNum=0;
        memset(a,0x3f,sizeof a);
    }
};
struct edge{
    int to,w;
    edge *next;
    edge(){
        next=NULL;
    }
};
struct node{
    edge *first;
    node(){
        first=NULL;
    }
};
struct List{
    int vetNum,edgeNum;
    node vet[maxn];
    List(){
        for (int i=0;i<maxn;i++)
            vet[i].first=NULL;
    }
};
void createUDN(List &l,Matrix &m){
    cout<<"please input the vetNum && edgeNum of this grap\n";
    ifstream in("graph.txt",ios::in);
//    cin>>l.vetNum>>l.edgeNum;
    in>>l.vetNum>>l.edgeNum;
    m.vetNum=l.vetNum,m.edgeNum=l.edgeNum;
    cout<<"please input the start,end and the weight of this edge in the following lines:\n";
    for (int i=0;i<l.edgeNum;i++){
        int s,t,w;
//        cin>>s>>t>>w;
        in>>s>>t>>w;
        m.a[s][t]=m.a[t][s]=w;
        edge * now=new edge();
        now->to=t;
        now->w=w;
        now->next=l.vet[s].first;
        l.vet[s].first=now;
        now=new edge();
        now->to=s;
        now->w=w;
        now->next=l.vet[t].first;
        l.vet[t].first=now;
    }
    cout<<"adj list && adj matrix have been created.\n";
}
int minTree(Matrix & m){
    int tot=0;
    int ans=0;
    int dis[m.vetNum+1];
    for (int i=1;i<=m.vetNum;i++)
        dis[i]=m.a[1][i];
    dis[1]=0;
    for (int i=1;i<=m.vetNum;i++){
        int mini=inf;
        int index=-1;
        for (int j=1;j<=m.vetNum;j++)
        if (!vis[j]&&dis[j]<mini){
            index=j;
            mini=dis[j];
        }
        for (int j=1;j<=m.vetNum;j++)
            if (dis[j]>m.a[j][index])
                dis[j]=m.a[j][index];
        vis[index]=1;
        tot++;
        ans+=mini;
    }
    cout<<"adj matrix && prim:\n";
    return ans;
}
int minTree(List &l){
    int dis[l.vetNum+1];
    memset(vis,0,sizeof vis);
    memset(dis,0x3f,sizeof dis);
    int ans=0;
    dis[1]=0;
    for (int i=1;i<=l.vetNum;i++){
        int mini=inf;
        int index=-1;
        for (int j=1;j<=l.vetNum;j++)
        if (!vis[j]&&dis[j]<mini){
            mini=dis[j];
            index=j;
        }
        vis[index]=1;
        ans+=mini;
        for (edge *now=l.vet[index].first;now!=NULL;now=now->next){
            int to=now->to;
            if (dis[to]>now->w)
                dis[to]=now->w;
        }
    }
    cout<<"adj list && prim:\n";
    return  ans;
}
int main(){
    List l;
    Matrix m;
    cout<<"--------------adj matrix && adj list----------------------\n";
    memset(vis,0,sizeof vis);
    createUDN(l,m);
    for (int i=1;i<=m.vetNum;i++){
        for (int j=1;j<=m.vetNum;j++)
            if (m.a[i][j]<inf)
                cout<<m.a[i][j]<<" ";
            else cout<<"* ";
        cout<<"\n";
    }
    cout<<"min tree:\n";
    cout<<minTree(m)<<"\n";
    cout<<minTree(l)<<"\n";
    cout<<"-------------done-----------------------------------.\n";
    return 0;
}
