/* ***********************************************
Author        :Mool
Created Time  :2018年10月23日 星期二 19时19分16秒
File Name     :201713160220-李常亮-ex11.cpp
************************************************ */
/*graph*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <string>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <queue>
#include <set>
#include <map>
const int maxn=110;
using namespace std;
struct graph{
	int vetNum,edgeNum;
	int vet[maxn],vis[maxn];
	int edge[maxn][maxn];
	graph(){
		memset(vet,0,sizeof vet);
		memset(edge,0,sizeof edge);
		memset(vis,0,sizeof vis);
		cout<<"The graph is initialized.\n";
	}
};
void createGraph(graph&g){
	cout<<"please input the vetNum && edgeNum of this graph:\n";
	cin>>g.vetNum>>g.edgeNum;
	cout<<"please input each edge in a line:\n";
	for (int i=0;i<g.edgeNum;i++){
		int x,y;
		cin>>x>>y;
		g.edge[x][y]=g.edge[y][x]=1;
		g.vet[x]++;
		g.vet[y]++;
	}
	cout<<"created.\n";
}
void dfs(graph &g,int now){
	g.vis[now]=1;
	cout<<now<<" ";
	for (int i=1;i<maxn;i++)
		if (!g.vis[i]&&g.edge[now][i]){
			dfs(g,i);
		}
}
void bfs(graph&g,int s){
	int q[maxn*2];
	int h=0,t=1;
	q[0]=s;
	g.vis[s]=1;
	while(h<t){
		int now=q[h++];
		cout<<now<<" ";
		for (int i=1;i<maxn;i++)
			if (!g.vis[i]&&g.edge[now][i]){
				q[t++]=i;
				g.vis[i]=1;
			}
	}
}
int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	cout<<"------------adj matrix--------------\n";
	graph g;
	createGraph(g);
	cout<<"please input the start of this graph.\n";
	int s;
	while(cin>>s){
		if (g.vet[s])
			break;
		cout<<"error,please input again:\n";
	}
	cout<<"the permutation of dfs:\n";
	dfs(g,s);
	cout<<"\n";
	memset(g.vis,0,sizeof g.vis);
	cout<<"the permutation of bfs:\n";
	bfs(g,s);
    return 0;
}
