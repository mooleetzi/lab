/*
2018.09.25 20.35
201713160220 lcl
data structure ex1
顺序表的增删改查
*/
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int maxsize=110;
struct node{
    char name[20];
    int num,score;
    node(){
        num=-1;
        score=0;
    }
};
struct List{
    node *el;
    int len;
//    List(){
//        el=new node();
//        len=0;
//    }
};
void note(){
    cout<<"-----------------\n";
    cout<<"|1-初始化顺序表\n";
    cout<<"|2-构建顺序表\n";
    cout<<"|3-显示表长\n";
    cout<<"|4-显示顺序表内容\n";
    cout<<"|5-查找学生信息\n";
    cout<<"|6-获取学生信息\n";
    cout<<"|7-插入学生信息\n";
    cout<<"|8-删除学生信息\n";
    cout<<"|9-销毁顺序表\n";
    cout<<"|0-退出\n";
    cout<<"-----------------\n";
}
int initList(List &rt){//初始化
    rt.el=new node();
    rt.len=0;
    if (rt.el==NULL)
        return 0;
    return 1;
}
void createList(List &rt){//创建
    char *name=new char[20];
    int num,score;
    int len;
    cout<<"请依次输入学生姓名，学号，成绩(以* 0 0结束:\n";
    while(cin>>name>>num>>score&&(num+score)){
        len=rt.len;
        //cout<<len<<"\n";
        //cout<<name<<" "<<num<<" "<<score<<"\n";
        if (len)
            cout<<rt.el[len-1].name<<" "<<rt.el[len-1].num<<" "<<rt.el[len-1].score<<"\n";
        strcpy(rt.el[len].name,name);
        rt.el[len].num=num;
        rt.el[len].score=score;
        rt.len++;
    }
}
void traverseList(List &rt){//显示
    for (int i=0;i<rt.len;i++){
        cout<<"| 第"<<i+1<<"个学生信息:\n";
        cout<<"|    姓名:"<<rt.el[i].name<<" 学号:"<<rt.el[i].num<<" 成绩:"<<rt.el[i].score<<"\n";
    }
}
int locateElem(const List & rt,char name[]){//查找
    for (int i=0;i<rt.len;i++){
        if (strcmp(rt.el[i].name,name)==0)
            return i+1;
    }
    return -1;
}
node getElem(const List & rt,int cur){//获取
    return rt.el[cur-1];
}
void listInsert(List &rt,int cur){
    char name[20];
    int num,score;
    cout<<"请依次输入学生姓名，学号，成绩:\n";
    cin>>name>>num>>score;
    for (int i=rt.len;i>cur;i--)
        rt.el[i]=rt.el[i-1];
    strcpy(rt.el[cur].name,name);
    rt.el[cur].num=num;
    rt.el[cur].score=score;
    rt.len++;
}
void listDelete(List & rt,int cur){
    for (int i=cur;i<rt.len-1;i++)
        rt.el[i]=rt.el[i+1];
    rt.len--;
}
int listLength(List &rt){
    return rt.len;
}
void destroyList(List &rt){
    if (rt.el)
        delete []rt.el;
    rt.len=0;
    cout<<"销毁成功.\n";
}
int main(){
    int c;
    List rt;
    note();
    cout<<"请选择:\n";
    int flag=1;
    while(flag&&cin>>c){
        switch (c){
            case 0:{
                flag=0;
                cout<<"再见.\n";
                break;
            }
            case 1:{
                if (initList(rt))
                    cout<<"初始化成功.\n";
                else{
                    cout<<"初始化失败,程序即将销毁.\n";
                    return 0;
                }
                break;
            }
            case 2:{
                createList(rt);
                break;
            }
            case 3:{
                cout<<"当前表长为"<<listLength(rt)<<".\n";
                break;
            }
            case 4:{
                traverseList(rt);
                break;
            }
            case 5:{
                cout<<"请输入要查找的学生姓名:\n";
                char name[20];
                cin>>name;
                int cur=locateElem(rt,name);
                if (~cur)
                    cout<<"|该同学同学信息如下:\n"<<"学号: "<<rt.el[cur-1].num<<" 成绩: "<<rt.el[cur-1].score<<"\n";
                else
                    cout<<"没有查找到任何信息,请检查名字是否正确.\n";
                break;
            }
            case 6:{
                cout<<"请输入要获取的学生index:\n";
                int num;
                cin>>num;
                node now=getElem(rt,num);
                cout<<"该学生信息如下:\n";
                cout<<"|姓名:"<<now.name<<" 学号:"<<now.num<<" 成绩:"<<now.score<<"\n";
                break;
            }
            case 7:{
                cout<<"请输入要插入的顺序表位置:\n";
                int cur;
                cin>>cur;
                listInsert(rt,cur-1);
                break;
            }
            case 8:{
                cout<<"请输入要删除的顺序表位置:\n";
                int cur;
                cin>>cur;
                listDelete(rt,cur-1);
                break;
            }
            case 9:{
                destroyList(rt);
                break;
            }
        }
        if (flag){
            note();
            cout<<"请选择:\n";
        }
    }
    return 0;
}
