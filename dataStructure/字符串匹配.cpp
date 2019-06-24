#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
struct Ch{
    char *data=new char[110];
    Ch(){}
    Ch(char s[]){
        strcpy(data,s);
    }
    int Chlen(){
        return strlen(data);
    }
    void printCh(){
        cout<<data<<"\n";
    }
    void concat(Ch s1,Ch s2){
        data=strcat(s1.data,s2.data);
    }
};
void getNext(Ch t,int next[]){
    int len=t.Chlen();
    int i=-1,j=0;
    next[0]=-1;
    int nxt[len+1];
    nxt[0]=0;
    while(j<len){
        if (i==-1||t.data[i]==t.data[j]){
            i++;j++;
            if (t.data[i]==t.data[j])
                next[j]=next[i];
            else
                next[j]=i;
            nxt[j]=i;
        }
        else
            i=next[i];
    }
    cout<<"�ִ�next����Ϊ��\n";
    for (int i=0;i<len;i++)
        cout<<nxt[i]<<" ";
    cout<<"\n�ִ�nextval����Ϊ:\n";
    for (int i=0;i<len;i++)
        cout<<next[i]<<" ";
    cout<<"\n";
}
int kmp(Ch s,Ch t){
    int len1=s.Chlen();
    int len2=t.Chlen();
    int next[len2+1];
    getNext(t,next);
    int i=0,j=0;
    while(i<len1){
        if (j==-1||s.data[i]==t.data[j]){
            i++,j++;
            if (j>=len2)
                return i-j;
        }
        else
            j=next[j];
    }
    return -1;
}
int BF(Ch s,Ch t){
    int i=0,j=0;
    while(i<s.Chlen()){
        if (t.data[j]==s.data[i])
            i++,j++;
        else
            j=0,i=i-j+1;
        if (j>=t.Chlen())
            return i-j;
    }
    return -1;
}
int main(){
    int a,b,c;
    c=a+ +b;
    char *s1=new char[110];
    char *s2=new char[20];
    cout<<"�������һ����:\n";
    cin>>s1;
    Ch s(s1);
    cout<<"��һ��������Ϊ: "<<s.Chlen()<<"\n";
    cout<<"������ڶ�����:\n";
    cin>>s2;
    Ch t(s2);
    cout<<"�ڶ���������Ϊ: "<<t.Chlen()<<"\n";
    Ch newCh;
    cout<<"==============�������������ַ�����Ϊ����=================\n";
    newCh.concat(s,t);
    cout<<"��������Ϊ: "<<newCh.Chlen()<<"\n";
    cout<<"�������ִ�(ģʽ��:\n";
    cin>>s1;
    t=Ch(s1);
    int k=kmp(newCh,t);
    cout<<"kmp�㷨ƥ��:\n";
    if (k>=0)
        cout<<"�ִ�զ�����е�һ�γ���λ��Ϊ: "<<k<<"\n";
    else
        cout<<"ƥ��ʧ��.\n";
    cout<<"BF�㷨ƥ��:\n";
    k=BF(newCh,t);
    if (k>=0)
        cout<<"�ִ�զ�����е�һ�γ���λ��Ϊ: "<<k<<"\n";
    else
        cout<<"ƥ��ʧ��.\n";
    return 0;
}
