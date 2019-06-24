/* ***********************************************
Author        :Mool
Created Time  :2018年10月18日 星期四 14时36分01秒
File Name     :201713160220-李常亮-ex10.cpp
************************************************ */
/*Huffman tree*/
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
using namespace std;
const int maxn=110;
struct node{
	int w,fa,lson,rson;
	node(){
		fa=lson=rson=0;
	}
};
typedef char** hc;
int n,num,len;
node rt[maxn];
int min(node rt[],int num){
	int mmin=0x3f3f3f3f;
	int cur=-1;
	for (int i=1;i<=num;i++)
		if (rt[i].w<mmin&&rt[i].fa==0){
			mmin=rt[i].w;
			cur=i;
		}
	//cout<<cur<<"\n";
	if (cur!=-1){
		rt[cur].fa=1;
		return cur;
	}
}
void select(node rt[],int num,int &s1,int &s2){
	s1=min(rt,num);
	s2=min(rt,num);
	s1=(s1>s2)?s2:s1;
	s2=(s1>s2)?s1:s2;
}
void createHt(node rt[]){
	if (n<=1)
		return;
	len=2*n-1;
	num=n;
	cout<<"please input the weight of each node:\n";
	for (int i=1;i<=n;i++)
		cin>>rt[i].w;
	for (int i=1;i<n;i++){
		int lson,rson;
		select(rt,num,lson,rson);
		rt[++num].w=rt[lson].w+rt[rson].w;
		rt[num].lson=lson;rt[num].rson=rson;
		rt[lson].fa=rt[rson].fa=num;
	}
}
void getHuffmanCode(node rt[],hc&code){
    code=new char*[n];
	for (int i=1;i<=n;i++){
		char *cur=new char[n];
		cur[n-1]='\0';
		int num=n-1;
		int now=i;
		while(rt[now].fa){
			--num;
			if (rt[rt[now].fa].lson==now)
				cur[num]='0';
			else
				cur[num]='1';
			now=rt[now].fa;
		}
		code[i]=new char[n+1];
		strcpy(code[i],&cur[num]);
	}
}
void show(hc &code){
	cout<<"huffmancode is here:\n";
	for (int i=1;i<=n;i++)
		cout<<code[i]<<"\n";
}
int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	ios::sync_with_stdio(false);
	cout<<"please input the number of leaf nodes:\n";
	cin>>n;
	hc code;
	createHt(rt);
	getHuffmanCode(rt,code);
	show(code);
    return 0;
}
