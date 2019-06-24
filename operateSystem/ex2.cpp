#include<iostream>
#include<cstdio>
#include<cstring>
#include<unistd.h>
#include<signal.h>
using namespace std;
int ctrl_cNum=0;
void ctrl_c(int sig){
	(void) signal(SIGINT,ctrl_c);
	++ctrl_cNum;
}
int main(){
    signal(SIGINT,ctrl_c);
    char ch;
    while(ch=getchar()!='\n');
	cout<<ctrl_cNum<<"\n";
}
