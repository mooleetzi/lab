/*
2018.09.26 21.24
201713160220 lcl
data structure ex2
链表的增删改查
*/
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<string>
using namespace std;
struct node{
    char *name=new char[50];
    char *num=new char[50];
    int score;
};
struct Link{
    node data;
    Link *next;
    Link(){
        next=NULL;
        data=*new node();
    }
};
typedef Link* link;
int initLink(link &rt){
    rt=new Link();
    if (rt!=NULL)
        return 1;
    return 0;
}
void note(){
    cout<<"-------------------------\n";
    cout<<"1.初始化链表\n";
    cout<<"2.前插法构建链表\n";
    cout<<"3.后插法构建链表\n";
    cout<<"4.求链表长度\n";
    cout<<"5.显示链表内容\n";
    cout<<"6.查找学生信息\n";
    cout<<"7.获取学生信息\n";
    cout<<"8.插入学生信息\n";
    cout<<"9.删除学生信息\n";
    cout<<"10.销毁链表\n";
    cout<<"0.退出\n";
    cout<<"请选择:\n";
}
void createList_H(link rt){
    FILE *fp=fopen("ex2.txt","r");
    int score;
    char name[50];
    char num[50];
    rt->next=NULL;
    while(fscanf(fp,"%s%s%d",num,name,&score)!=EOF){
        //cout<<num<<" "<<name<<" "<<score<<"\n";
        link now=new Link();
        memcpy(now->data.name,name,sizeof name);
        memcpy(now->data.num,num,sizeof num);
        now->data.score=score;
        now->next=rt->next;
        rt->next=now;
        //cout<<now->data.num<<" "<<now->data.name<<" "<<now->data.score<<"\n";
    }
    fclose(fp);
    cout<<"构建完成.\n";
}
void createList_R(link rt){
    FILE *fp=fopen("ex2.txt","r");
    char name[50];
    char num[50];
    int score;
    link pm=rt;
    rt->next=NULL;
    while(fscanf(fp,"%s%s%d",num,name,&score)!=EOF){
        link now=new Link();
        memcpy(now->data.name,name,sizeof name);
        memcpy(now->data.num,num,sizeof num);
        now->data.score=score;
        pm->next=now;
        pm=now;
    }
    cout<<"构建完成.\n";
    fclose(fp);
}
void listDisplay(link rt){
    rt=rt->next;
    while(rt!=NULL){
        cout<<rt->data.num<<" "<<rt->data.name<<" "<<rt->data.score<<"\n";
        rt=rt->next;
    }
}
link locateElem(link rt,char s[]){
    while(rt!=NULL){
        if (strcmp(s,rt->data.name)==0)
            return rt;
        rt=rt->next;
    }
}
int listLength(link rt){
    int cnt=0;
    while(rt->next!=NULL){
        cnt++;
        rt=rt->next;
    }
    return cnt;
}
int getElem(link rt,int index,node &e){
    int cur=0;
    while(cur++<index)
        rt=rt->next;
    e=rt->data;
    if (rt==NULL)
        return 0;
    return 1;
}
int listInsert(link rt,int index){
    int cnt=0;
    while(cnt<index){
        cnt++;
        rt=rt->next;
    }
    link now=new Link();
    cout<<"请输入学生学号，姓名，成绩:\n";
    char *name=new char[50];
    char *num=new char[50];
    int score;
    cin>>num>>name>>score;
    now->data.name=name;
    now->data.num=num;
    now->data.score=score;
    if (rt==NULL)
        return 0;
    if (rt->next==NULL)
        rt->next=now;
    else{
        link s=new Link();
        s=rt->next;
        rt->next=now;
        now->next=s;
    }
    return 1;
}
int listDelete(link rt,int index){
    int cnt=0;
    while(cnt<index-1){
        cnt++;
        rt=rt->next;
    }
    if (rt==NULL||rt->next==NULL)
        return 0;
    if (rt->next->next==NULL)
        rt->next=NULL;
    else
        rt->next=rt->next->next;
    return 1;
}
int listDestroy(link &rt){
    while(rt){
        link s=rt;
        delete s;
        rt=rt->next;
    }
    if (rt)
        return 0;
    return 1;
}
int main(){
    int c;
    link rt;
    note();
    int flag=1;
    while(flag&&cin>>c&&c){
        switch(c){
            case 1:{
                int k=initLink(rt);
                if (k)
                    cout<<"初始化成功.\n";
                else{
                    flag=0;
                    cout<<"初始化失败.\n";
                }
                break;
            }
            case 2:{
                createList_H(rt);
                break;
            }
            case 3:{
                createList_R(rt);
                break;
            }
            case 4:{
                cout<<"当前链表长度为:"<<listLength(rt)<<".\n";
                break;
            }
            case 5:{
                listDisplay(rt);
                break;
            }
            case 6:{
                cout<<"请输入查找学生姓名:\n";
                char name[50];
                cin>>name;
                link now=new Link();
                now=locateElem(rt,name);
                if (now!=NULL){
                    cout<<name<<"查找成功,地址为:"<<now<<"\n信息如下:\n";
                    cout<<"学号:"<<now->data.num<<" 成绩:"<<now->data.score<<"\n";
                }
                else
                    cout<<"查找失败.\n";
                break;
            }
            case 7:{
                cout<<"请输入要获取的学生index:\n";
                int index;
                cin>>index;
                node query;
                int k=getElem(rt,index,query);
                if (k){
                    cout<<"获取成功,第"<<index<<"个学生信息如下:\n";
                    cout<<query.num<<" "<<query.name<<" "<<query.score<<"\n";
                }
                else
                    cout<<"获取失败.\n";
                break;
            }
            case 8:{
                cout<<"请输入插入位置:\n";
                int index;
                cin>>index;
                int k=listInsert(rt,index);
                if (k)
                    cout<<"插入成功.\n";
                else
                    cout<<"插入失败.\n";
                break;
            }
            case 9:{
                cout<<"请输入删除位置:\n";
                int index;
                cin>>index;
                int k=listDelete(rt,index);
                if (k)
                    cout<<"删除成功.\n";
                else
                    cout<<"删除失败.\n";
                break;
            }
            case 10:{
                int k=listDestroy(rt);
                if (k)
                    cout<<"销毁成功.\n";
                else
                    cout<<"销毁失败.\n";
                flag=0;
                break;
            }
        }
        note();
    }
    return 0;
}
