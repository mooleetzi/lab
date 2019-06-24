/* ***********************************************
Author        :Mool
Created Time  :2018年10月23日 星期二 19时50分58秒
File Name     :201713160220-李常亮-ex12.cpp
************************************************ */

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
int vis[maxn];
struct edge{
	int to;
	edge *next;
	edge(){
		next=NULL;
	}
};
struct node{
	int data;
	edge *first;
	node(){
		first=NULL;
		data=0;
	}
};
struct List{
	node vet[maxn];
	int vetNum,edgeNum;
};
void createList(List&g){
	cout<<"please input the vetNum && edgeNum of this graph:\n";
	cin>>g.vetNum>>g.edgeNum;
	cout<<"please input each edge in a line:\n";
	for (int i=0;i<g.edgeNum;i++){
		int x,y;
		cin>>x>>y;
		edge *now=new edge();
		now->to=y;
		now->next=g.vet[x].first;
		g.vet[x].first=now;
		g.vet[x].data++;
		g.vet[y].data++;
		now=new edge();
		now->to=x;
		now->next=g.vet[y].first;
		g.vet[y].first=now;
	}
	cout<<"created.\n";
}
void dfs(List&g,int cur){
	vis[cur]=1;
	cout<<cur<<" ";
	for (edge *now=g.vet[cur].first;now!=NULL;now=now->next){
		int to=now->to;
		if (!vis[to])
			dfs(g,to);
	}
}
void bfs(List&g,int s){
	int q[maxn*2];
	memset(vis,0,sizeof vis);
	memset(q,0,sizeof q);
	int h=0,t=1;
	q[0]=s;
	cout<<"bfs:\n";
	vis[s]=1;
	while(h<t){
		int now=q[h++];
		cout<<now<<" ";
		for (edge *cur=g.vet[now].first;cur!=NULL;cur=cur->next){
			int to=cur->to;
			if (!vis[to]){
				q[t++]=to;
				vis[to]=1;
			}
		}
	}
}
int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
    cout<<"------------adj list--------------\n";
	List g;
	createList(g);
	cout<<"please input the start of this graph.\n";
	int s;
	while(cin>>s){
		if (g.vet[s].data)
			break;
		cout<<"error,please input again:\n";
	}
	cout<<"the permutation of dfs:\n";
	dfs(g,s);
	cout<<"\n";
	cout<<"the permutation of bfs:\n";
	bfs(g,s);
    return 0;
}
