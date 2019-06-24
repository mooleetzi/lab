/* ***********************************************
Author        :Mool
Created Time  :2018年10月16日 星期二 19时09分08秒
File Name     :201713160220-李常亮-ex9.cpp
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
struct node{
	char data;
	node *lson;
	node *rson;
	node(){
		data=' ';
		lson=NULL;
		rson=NULL;
	}
};
char *str=new char [110];// use to create
int cur=0;// use to create
using namespace std;
void initbTree(node *rt){
	//rt->data=' ';//the data of an emoty node is ' '
	//rt->lson=NULL;
	//rt->rson=NULL;
}
int empty(node *rt){
	if (rt->lson==NULL&&rt->rson==NULL)
		return 1;
	return 0;
}
int getDepth(node *rt,int depth){//get the depth of this tree
	if (rt==NULL)
		return depth-1;
	int l=getDepth(rt->lson,depth+1);
	int r=getDepth(rt->rson,depth+1);
	return depth=max(l,r);
}
char getRoot(node *rt){//get the root data of this tree
	return rt->data;
}
int getLeaf(node *rt){//get the leaf nodes of this tree
	if (rt==NULL)
		return 0;
	if (rt->lson==NULL&&rt->rson==NULL)
		return 1;
	return getLeaf(rt->lson)+getLeaf(rt->rson);
}
int getNode(node *rt){//get the number of nodes
	if (rt==NULL)
		return 0;
	return getNode(rt->lson)+getNode(rt->rson)+1;

}
void preTraverse(node *rt){//print the data of this tree in preorder
	if (rt==NULL)
		return;
	cout<<rt->data;
	preTraverse(rt->lson);
	preTraverse(rt->rson);
}
void inTraverse(node *rt){//print the data of this tree in inorder

	if (rt==NULL)
		return;
	inTraverse(rt->lson);
	cout<<rt->data;
	inTraverse(rt->rson);
}
void postTraverse(node *rt){//print the data of this tree in postorder

	if (rt==NULL)
		return;
	postTraverse(rt->lson);
	postTraverse(rt->rson);
	cout<<rt->data;
}
node *getAddress(node *rt,char data){//get the data's address in memory
	if (rt==NULL)
		return NULL;
	if (rt->data==data)
		return rt;
	node *ans1=getAddress(rt->lson,data);
	node *ans2=getAddress(rt->rson,data);
	if (ans1)
		return ans1;
	else if (ans2)
		return ans2;
	else
		return NULL;
}
void assign(node *now,char el){//update
	if (now)
		now->data=el;
}
char getFa(node *rt,node *now){
	if (rt==NULL)
		return ' ';
	if (rt->lson==now||rt->rson==now)
		return rt->data;
	char f1=getFa(rt->lson,now);
	char f2=getFa(rt->rson,now);
	if (f1!=' ')
		return f1;
	else if (f2!=' ')
		return f2;
	else
		return ' ';
}
char getLson(node *now){
	if (now->lson)
		return now->lson->data;
	return ' ';
}
char getRson(node *now){
	if (now->rson)
		return now->rson->data;
	return ' ';
}
node *preCreate(){
	node *now=new node();
	char data;
	cin>>data;
	if (data=='#')//use '#' to mark leaf nodes
		now=NULL;
	else{
		now->data=data;
		now->lson=preCreate();
		now->rson=preCreate();
	}
	return now;
}
void note(node *rt,int op){
	cout<<"---------------------------------------------------------------\n";
	if (!op)
		cout<<"after init this empty binary tree, is it empty (1:yes 0:no)"<<empty(rt);
	else
		cout<<"after ctreating this binary tree, is it empty (1:yes 0:no)"<<empty(rt);
	cout<<"\nthe depth of this btree is "<<getDepth(rt,0)<<"\n";
	char root=getRoot(rt);
	if (root==' ')
		cout<<"this binary tree is empty,has no root.\n";
	else
		cout<<"the root of this binary tree is "<<root<<".\n";
	cout<<"---------------------------------------------------------------\n";
	if (op){
		cout<<"the number of leaves in this tree is : "<<getLeaf(rt)<<"\n";
		cout<<"the number of nodes in this tree is : "<<getNode(rt)<<"\n";
		cout<<"the depth of this tree is : "<<getDepth(rt,0)<<"\n";
		cout<<"get the data of this tree in preorder:\n";
		preTraverse(rt);
		cout<<"\nget the data of this tree in inorder:\n";
		inTraverse(rt);
		cout<<"\nget the data of this tree in postorder:\n";
		postTraverse(rt);
		cout<<"\n---------------------------------------------------------\n";
		cout<<"please input the data you want to search:\n";
		char el1,el2;
		cin>>el1;
		node *now=getAddress(rt,el1);
		if (now)
			cout<<"the address of this element is : "<<now<<'\n';
		else cout<<"no response.\n";
		cout<<"-----------------------------------------------------------\n";
		if (now){
			cout<<"please input the new element to replace the old:\n";
			cin>>el2;
			assign(now,el2);
			cout<<"get the data of this tree in preorder:\n";
			preTraverse(rt);
			char fa=getFa(rt,now);
			if (fa!=' ')
				cout<<"\n"<<el2<<"'s parent is "<<fa<<".\n";
			else
				cout<<el2<<" has no parent.\n";
			char lchild=getLson(now);
			if (lchild!=' ')
				cout<<el2<<"'s lchild is "<<lchild<<".\n";
			else
				cout<<el2<<" has no lchild.\n";
			char rchild=getRson(now);
			if (rchild!=' ')
				cout<<el2<<"'s rchild is "<<rchild<<".\n";
			else
				cout<<el2<<" has no rchild.\n";
		}
	}
}
void destroyTree(node *rt){
	if (rt==NULL)
		return;
	destroyTree(rt->lson);
	destroyTree(rt->rson);
	delete rt;
}
int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
    node *rt=new node();
	initbTree(rt);
	note(rt,0);
	cout<<"please input the data in preorder:\n";
	rt=preCreate();
	note(rt,1);
	destroyTree(rt);
    return 0;
}