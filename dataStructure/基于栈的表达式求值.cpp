#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const char op[]="+-*/()#";
struct dStack{
    double data;
    dStack *next;
    dStack(){
        data=-1;
        next=NULL;
    }
};
struct cStack{
    char opt;
    cStack *next;
    cStack(){
        next=NULL;
    }
};
typedef dStack* ds;
typedef cStack* cs;
void push(dStack *rt,double now){
    dStack *tmp=new dStack();
    tmp->data=now;
    tmp->next=rt->next;
    rt->next=tmp;
}
void pop(dStack *rt){
    dStack *tmp=rt->next;
    rt->next=rt->next->next;
    delete tmp;
}
double top(dStack *rt){
    return rt->next->data;
}
int empty(dStack *rt){
    if (rt->next==NULL)
        return 1;
    return 0;
}
void push(cStack *rt,char now){
    cStack *tmp=new cStack();
    tmp->opt=now;
    tmp->next=rt->next;
    rt->next=tmp;
}
void pop(cStack *rt){
    cStack *tmp=rt->next;
    rt->next=rt->next->next;
    delete tmp;
}
char top(cStack *rt){
    return rt->next->opt;
}
int empty(cStack *rt){
    if (rt->next==NULL)
        return 1;
    return 0;
}
void note(){
    cout<<"-----------------------\n";
    cout<<"��ӭʹ�ñ��ʽ��ֵϵͳ.\n";
    cout<<"��ѡ��\n";
    cout<<"1.������ʽ.\n";
    cout<<"0.�˳�\n";
}
int in(char s){
    for (int i=0;i<7;i++)
        if (s==op[i])
            return 1;
    return 0;
}
int precede(char s1,char s2){
    if (s2=='#')
        return 1;
    if (s1=='+'||s1=='-'){
        if (s2=='+'||s2=='-')
            return 0;
        else
            return -1;//s1���ȼ�����s2
    }
    else{
        if (s2=='*'||s2=='/')
            return 0;
        else
            return 1;//s1���ȼ�����s2
    }
}
double operate(double s1,char op,double s2){
    double ans=0;
    cout<<s1<<op<<s2<<"\n";
    switch(op){
    case '+':
        ans=s1+s2;
        break;
    case '-':
        ans=s1-s2;
        break;
    case '*':
        ans=s1*s2;
        break;
    case '/':
        if (s2==0){
            cout<<"�������,�ټ�.\n";
            ans=0x3f3f3f3f;
        }
        else
            ans=s1/s2;
        break;
    }
    return ans;
}
double getAns(char info[]){
    ds data=new dStack();
    cs opt=new cStack();
    int len=strlen(info);
//    cout<<info;
    for (int i=0;i<len;i++){
        if (in(info[i])){//��ǰ�ַ��ǲ�����
            //cout<<info[i]<<" ";
            if (info[i]=='(')
                push(opt,info[i]);
            else if (info[i]==')'){//�����ţ�����
                char op=top(opt);
                pop(opt);
                double s1=top(data);
                pop(data);
                double s2=top(data);
                pop(data);
                push(data,operate(s2,op,s1));
                pop(opt);
            }
            else{
                if (empty(opt)||top(opt)=='('){
                    push(opt,info[i]);
                    continue;
                }
                char pre=top(opt);
                if (precede(pre,info[i])==1||precede(pre,info[i])==0){
                    double s1=top(data);
                    pop(data);
                    double s2=top(data);
                    pop(data);
                    push(data,operate(s2,pre,s1));
                    pop(opt);
                    push(opt,info[i]);
                }
                else if (precede(pre,info[i]==-1)){//����������ȼ���
                        push(opt,info[i]);
                }
            }
        }
        else
            push(data,info[i]-'0');//cout<<info[i]-'0'<<"\n";
    }
    pop(opt);
    if (!empty(opt)){
        double s1=top(data);
        pop(data);
        double s2=top(data);
        pop(data);
        push(data,operate(s2,top(opt),s1));
        pop(opt);
    }
    return top(data);
}
int main(){
    note();
    int c;
    while(cin>>c&&c){
        cout<<"��������ʽ,��֤����������������0~9(��#��������.\n";
        char *s=new char[50];
        cin>>s;
        cout<<getAns(s)<<"\n";
        note();
    }
    return 0;
}
