/*
2018.09.25 20.35
201713160220 lcl
data structure ex1
˳������ɾ�Ĳ�
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
    cout<<"|1-��ʼ��˳���\n";
    cout<<"|2-����˳���\n";
    cout<<"|3-��ʾ��\n";
    cout<<"|4-��ʾ˳�������\n";
    cout<<"|5-����ѧ����Ϣ\n";
    cout<<"|6-��ȡѧ����Ϣ\n";
    cout<<"|7-����ѧ����Ϣ\n";
    cout<<"|8-ɾ��ѧ����Ϣ\n";
    cout<<"|9-����˳���\n";
    cout<<"|0-�˳�\n";
    cout<<"-----------------\n";
}
int initList(List &rt){//��ʼ��
    rt.el=new node();
    rt.len=0;
    if (rt.el==NULL)
        return 0;
    return 1;
}
void createList(List &rt){//����
    char *name=new char[20];
    int num,score;
    int len;
    cout<<"����������ѧ��������ѧ�ţ��ɼ�(��* 0 0����:\n";
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
void traverseList(List &rt){//��ʾ
    for (int i=0;i<rt.len;i++){
        cout<<"| ��"<<i+1<<"��ѧ����Ϣ:\n";
        cout<<"|    ����:"<<rt.el[i].name<<" ѧ��:"<<rt.el[i].num<<" �ɼ�:"<<rt.el[i].score<<"\n";
    }
}
int locateElem(const List & rt,char name[]){//����
    for (int i=0;i<rt.len;i++){
        if (strcmp(rt.el[i].name,name)==0)
            return i+1;
    }
    return -1;
}
node getElem(const List & rt,int cur){//��ȡ
    return rt.el[cur-1];
}
void listInsert(List &rt,int cur){
    char name[20];
    int num,score;
    cout<<"����������ѧ��������ѧ�ţ��ɼ�:\n";
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
    cout<<"���ٳɹ�.\n";
}
int main(){
    int c;
    List rt;
    note();
    cout<<"��ѡ��:\n";
    int flag=1;
    while(flag&&cin>>c){
        switch (c){
            case 0:{
                flag=0;
                cout<<"�ټ�.\n";
                break;
            }
            case 1:{
                if (initList(rt))
                    cout<<"��ʼ���ɹ�.\n";
                else{
                    cout<<"��ʼ��ʧ��,���򼴽�����.\n";
                    return 0;
                }
                break;
            }
            case 2:{
                createList(rt);
                break;
            }
            case 3:{
                cout<<"��ǰ��Ϊ"<<listLength(rt)<<".\n";
                break;
            }
            case 4:{
                traverseList(rt);
                break;
            }
            case 5:{
                cout<<"������Ҫ���ҵ�ѧ������:\n";
                char name[20];
                cin>>name;
                int cur=locateElem(rt,name);
                if (~cur)
                    cout<<"|��ͬѧͬѧ��Ϣ����:\n"<<"ѧ��: "<<rt.el[cur-1].num<<" �ɼ�: "<<rt.el[cur-1].score<<"\n";
                else
                    cout<<"û�в��ҵ��κ���Ϣ,���������Ƿ���ȷ.\n";
                break;
            }
            case 6:{
                cout<<"������Ҫ��ȡ��ѧ��index:\n";
                int num;
                cin>>num;
                node now=getElem(rt,num);
                cout<<"��ѧ����Ϣ����:\n";
                cout<<"|����:"<<now.name<<" ѧ��:"<<now.num<<" �ɼ�:"<<now.score<<"\n";
                break;
            }
            case 7:{
                cout<<"������Ҫ�����˳���λ��:\n";
                int cur;
                cin>>cur;
                listInsert(rt,cur-1);
                break;
            }
            case 8:{
                cout<<"������Ҫɾ����˳���λ��:\n";
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
            cout<<"��ѡ��:\n";
        }
    }
    return 0;
}
