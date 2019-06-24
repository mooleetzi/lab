#include<iostream>
#include<cstring>
using namespace std;
const int maxn=110;
const int inf=0x3f3f3f3f;
struct matrix{
    int vetNum,edgeNum;
    int a[maxn][maxn];
    matrix(){
        vetNum=edgeNum=0;
        memset(a,0x3f,sizeof a);
    }
};
void createDN(matrix &m){
    ifstream in("graph.txt",ios::in);
    cout<<"please input the vetNum && edgeNum of this graph\n";
//    cin>>m.vetNum>>m.edgeNum;
    in>>m.vetNum>>m.edgeNum;
    cout<<"please input the start,end and the weight of this edge in the following lines:\n";
    for (int i=0;i<m.edgeNum;i++){
        int s,t,w;
        in>>s>>t>>w;
//        cin>>s>>t>>w;
        m.a[s][t]=w;
    }
    cout<<"adj matrix has been created.\n";
    in.close();
}
void dijkstra(const matrix &m,int s,int t){
    int dis[m.vetNum+1];
    memset(dis,0x3f,sizeof dis);
    int vis[m.vetNum+1];
    memset(vis,0,sizeof vis);
    for (int i=1;i<=m.vetNum;i++)
        dis[i]=m.a[s][i];
    dis[s]=0;
    int pre[m.vetNum];
    memset(pre,-1,sizeof pre);
	for (int i=1;i<=m.vetNum;i++)
		if (m.a[s][i]<inf)
			pre[i]=s;
    for (int i=0;i<m.vetNum;i++){
        int mini=inf;
        int index=-1;
        for (int j=1;j<=m.vetNum;j++)
        if (dis[j]<mini&&!vis[j]){
            mini=dis[j];
            index=j;
        }
		if (index==-1)
			break;
        vis[index]=1;
        for (int j=1;j<=m.vetNum;j++)
            if (!vis[j]&&dis[j]>dis[index]+m.a[index][j]){
                dis[j]=dis[index]+m.a[index][j];
				pre[j]=index;
			}
    }
	int cur=t;
	int path[m.vetNum+1];
	int cnt=0;
    while(t!=-1){
        path[cnt++]=t;
		t=pre[t];
    }
	for (int i=cnt-1;i>-1;i--)
		cout<<path[i]<<((i==0)?"\n":"->");
    cout<<dis[cur]<<"\n";
}
int main(){
    cout<<"--------------adj matrix && dijkstra---------------\n";
    matrix m;
    createDN(m);
    for (int i=1;i<=m.vetNum;i++){
        for (int j=1;j<=m.vetNum;j++)
            if (m.a[i][j]<inf)
                cout<<m.a[i][j]<<" ";
            else cout<<"* ";
        cout<<"\n";
    }
    cout<<"please input the start and end:\n";
    int s,t;
    cin>>s>>t;
    cout<<"shortest path is :\n";
    dijkstra(m,s,t);
    cout<<"---------------------------done--------------------\n";
    return 0;
}
