/* ***********************************************
Author        :Mool
Created Time  :2018年10月04日 星期四 10时52分43秒
File Name     :201713160220-李常亮-ex5.cpp
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
struct Stack{
	Stu *base;
	int top;
	int size;
	int maxSize;
};
int initStack(Stack &s){
	s.base=new Stu[110];
	s.top=0;
	s.size=0;
	s.maxSize=110;
	return 1;
}
int empty(Stack &s){
	if (s.size<0)
		return 1;
	return 0;
}
void push(Stack &s,Stu now){
	for (int i=s.size;i>0;i--)
		s.base[i]=s.base[i-1];
	s.base[0]=now;
	s.size++;
}
int pop(Stack &s){
	for (int i=1;i<s.size;i++)
		s.base[i-1]=s.base[i];
	s.size--;
	if (s.size<0)
		return 0;
	return 1;
}
Stu* top(Stack &s){
	if (empty(s))
		return NULL;
	return s.base;
}
int destroyStack(Stack &s){
	for (int i=0;i<s.size;i++){
		delete[] s.base[i].num;
		delete[] s.base[i].name;
	}
	return 1;
}
void note(){
	cout<<"--------------------------------------\n";
	cout<<"1.init this stack.\n";
	cout<<"2.push a data into this stack.\n";
	cout<<"3.pop the top data from this stack.\n";
	cout<<"4.get the top data from this stack.\n";
	cout<<"5.destroy this stack.\n";
	cout<<"0.quit.\n";
	cout<<"--------------------------------------\n";
	cout<<"please choose:\n";
}
int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	int c;
	note();
	Stack s;
	while(cin>>c&&c){
		switch(c){
			case 1:{
				if (initStack(s))
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
				push(s,now);
				break;
			}
			case 3:{
				if (pop(s))
					cout<<"Stackpoping success.\n";
				else
					cout<<"runtime error. For this Stack is empty.\n";
				break;
			}
			case 4:{
				Stu *now=top(s);
				if (now==NULL){
					cout<<"runtime error.For this Stack is empty.\n";
					break;
				}
				cout<<"The top element on the stack is:\n";
				cout<<"Student number: ";
				cout<<now->num<<"\n";
				cout<<"Student name: ";
				cout<<now->name<<"\n";
				cout<<"Student score: "<<now->score<<"\n";
				break;
			}
			case 5:{
				if (destroyStack(s))
					cout<<"destroy sucess.\n";
				else cout<<"destroy failed.\n";
				break;
			}
		}
		note();
	}
	cout<<"Bye.\n";
    return 0;
}
