/* ***********************************************
Author        :Mool
Created Time  :2018年10月07日 星期日 17时58分42秒
File Name     :201713160220-李常亮-ex7.cpp
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
struct Stu{
	char *num;
	char *name;
	int score;
	Stu(){
		num=new char[8];
		name=new char[80];
		score=-1;
	}
};
struct Queue{
	int front;
	int rear;
	Stu *base;
};
void note(){
	cout<<"--------------------------------------\n";
	cout<<"1.init this queue.\n";
	cout<<"2.push a data into this queue.\n";
	cout<<"3.get the front data from this queue.\n";
	cout<<"4.pop the front data from this queue.\n";
	cout<<"5.print the queue and then quit.\n";
	cout<<"0.quit.\n";
	cout<<"--------------------------------------\n";
	cout<<"please choose:\n";
}
int initQueue(Queue &s){
	s.front=s.rear=0;
	s.base=new Stu[maxn];
	return 1;
}
int push(Queue &s,Stu now){
	if ((s.rear+1)%maxn==s.front)
		return 0;
	s.base[s.rear++]=now;
	return 1;
}
int pop(Queue &s){
	if (s.front==s.rear)
		return 0;
	s.front++;
	return 1;
}
Stu *top(Queue &s){
	if (s.front==s.rear)
		return NULL;
	return &(s.base[s.front]);
}
int empty(Queue &s){
	if (s.front==s.rear)
		return 1;
	return 0;
}
int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
    int c=1;
	note();
	Queue s;
	while(c&&cin>>c&&c){
		switch(c){
			case 1:{
				if (initQueue(s))
					cout<<"Initialization success.\n";
				else
					cout<<"Initialization failed.\n";
				break;
			}
			case 2:{
				Stu now;
				cout<<"please input the information.\n";
				cout<<"Student number:\n";
				cin>>now.num;
				cout<<"Student name:\n";
				cin>>now.name;
				cout<<"Student score:\n";
				cin>>now.score;
				if (push(s,now)==0)
					cout<<"this queue is overflow.\n";
				break;
			}
			case 4:{
				if (pop(s))
					cout<<"Queuepoping success.\n";
				else
					cout<<"runtime error. For this Queue is empty.\n";
				break;
			}
			case 3:{
				Stu *now=top(s);
				if (now==NULL){
					cout<<"runtime error.For this Queue is empty.\n";
					break;
				}
				cout<<"The front element on the queue is:\n";
				cout<<"Student number: ";
				cout<<now->num<<"\n";
				cout<<"Student name: ";
				cout<<now->name<<"\n";
				cout<<"Student score: "<<now->score<<"\n";
				break;
			}
			case 5:{
				int cur=1;
				while(!empty(s)){
					Stu *now=top(s);
					pop(s);
					if (now==NULL){
						cout<<"runtime error.For this Queue is empty.\n";
						break;
					}
					cout<<cur<<": \n";
					cout<<"Student number: ";
					cout<<now->num<<"\n";
					cout<<"Student name: ";
					cout<<now->name<<"\n";
					cout<<"Student score: "<<now->score<<"\n";
					cur++;
				}
				c=0;
				break;
			}
		}
		note();
	}
	cout<<"Bye.\n";
    return 0;
}
