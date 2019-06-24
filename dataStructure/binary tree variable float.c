/*
    可更新变量的表达式求值
    支持加减乘除浮点数
*/
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<math.h>
#define maxn 110
#define eps 0.000001
char expression[maxn][maxn];
int expLength;
char str[maxn];
typedef struct node{
    float num;
    char var[4];
    char op;
    struct node *left;
    struct node *right;
}node;

typedef struct{//操作符
    char op[maxn];
    int top;
}st1;
typedef struct{
    float num[maxn];
    int top;
}st2;
/*字符串替换函数*/
char *replace(char *src, char *sub, char *dst){

    int pos = 0;

    int offset = 0;

    int srcLen, subLen, dstLen;

    char *pRet = NULL;



    srcLen = strlen(src);

    subLen = strlen(sub);

    dstLen = strlen(dst);

    pRet = (char *)malloc(srcLen + dstLen - subLen + 1);//(外部是否该空间)

    if (NULL != pRet)

    {

        pos = strstr(src, sub) - src;

        memcpy(pRet, src, pos);

        offset += pos;

        memcpy(pRet + offset, dst, dstLen);

        offset += dstLen;

        memcpy(pRet + offset, src + pos + subLen, srcLen - pos - subLen);

        offset += srcLen - pos - subLen;

        *(pRet + offset) = '\0';

    }

    return pRet;
}
int isOp(char now){//判断是否是操作符
    if (strchr("+-*/()",now)!=NULL)
        return 1;
    return 0;
}
void update(node *rt,char *now,float num){
    if (!rt)
        return;
    if (strcmp(now,rt->var)==0){
        rt->num=num;
        return;
    }
    else{
        update(rt->left,now,num);
        update(rt->right,now,num);
    }
}
float cal(float a,char c,float b){
    switch(c){
        case '+':
            return a+b;
        case '-':
            return a-b;
        case '*':
            return a*b;
        case '/':{
            if (abs(b)<eps){
                printf("divide zero error,please check the input.\n");
                exit(0);
            }
            return a/b;
            break;
        }
    }
}
float getAns(node *rt){
    if (abs(rt->num)<eps&&rt->op!=' ')
        return cal(getAns(rt->left),rt->op,getAns(rt->right));
    return rt->num;
}
void inorder(node *rt){
    if (!rt)
        return;
    inorder(rt->left);
    if (rt->op==' '){
        if (strcmp(rt->var," ")==0)//不是变量则为空格
            printf("%f",rt->num);
        else
            printf("%s",rt->var);
    }
    else
        printf("%c",rt->op);
    inorder(rt->right);
}
void preorder(node *rt){
    if (!rt)
        return;
    if (rt->op==' '){
        if (strcmp(rt->var," ")==0)//不是变量则为空格
            printf("%f",rt->num);
        else
            printf("%s",rt->var);
    }
    else
        printf("%c",rt->op);
    preorder(rt->left);
    preorder(rt->right);
}
void postorder(node *rt){
    if (!rt)
        return;
    postorder(rt->left);
    postorder(rt->right);
    if (rt->op==' '){
        if (strcmp(rt->var," ")==0)//不是变量则为空格
            printf("%f",rt->num);
        else
            printf("%s",rt->var);
    }
    else
        printf("%c",rt->op);
}
void getExpression(char exp[maxn][maxn],char *str){
    expLength=0;
    for (int i=0;i<strlen(str);i++){
        if (isOp(str[i])){
            exp[expLength][0]=str[i];
            exp[expLength++][1]='\0';
        }
        else{//变量||操作数
            int j;
            for (j=i;;j++)
                if (isOp(str[j]))//遇到操作符
                    break;
            for (int k=i;k<j;k++)
                exp[expLength][k-i]=str[k];
            exp[expLength][j-i]='\0';
            expLength++;
            i=j-1;
        }
    }
}
node* createNode(char s[]){
    node * temp=(node*)malloc(sizeof(node));
    temp->left=NULL;
    temp->right=NULL;
    if (strchr("+-*/()",s[0])!=NULL){
        temp->op=s[0];
        temp->var[0]=' ';
        temp->var[1]='\0';
        temp->num=0;
    }
    else{
        strcpy(temp->var,s);
        temp->num=atof(s);
        temp->op=' ';
    }
    //printf("%s %c %f %s\n",temp->var,temp->op,temp->num,s);
    return temp;
}
node* create(char data[][maxn]){
    node * s1[maxn];
    node * s2[maxn];
    int top1=-1;
    int top2=-1;
    for (int i=0;strcmp(data[i],"\0")!=0;i++){
        if (data[i][0]=='('){
                node *temp;
                temp=createNode(data[i]);
                s2[++top2]=temp;
        }
        else if (data[i][0]==')'){
            while(s2[top2]->op!='('){
                node *temp=s2[top2];
                node *t1=s1[top1--];
                node *t2=s1[top1--];
                temp->left=t2;
                temp->right=t1;
                s1[++top1]=temp;
                top2--;
            }
            top2--;
        }
        else if (strchr("+-*/",data[i][0])!=NULL){
            if (data[i][0]=='+'||data[i][0]=='-'){
                while(top2>=0&&s2[top2]->op!='('){
                    node *temp=s2[top2];
                    node *t1=s1[top1--];
                    node *t2=s1[top1--];
                    temp->left=t2;
                    temp->right=t1;
                    s1[++top1]=temp;
                    top2--;
                }
            }
            else if (data[i][0]=='*'||data[i][0]=='/'){
                while(top2>=0&&s2[top2]->op!='('&&s2[top2]->op!='+'&&s2[top2]->op!='-'){
                    node *temp=s2[top2];
                    node *t1=s1[top1--];
                    node *t2=s1[top1--];
                    temp->left=t2;
                    temp->right=t1;
                    s1[++top1]=temp;
                    top2--;
                }
            }
            node *temp=createNode(data[i]);
            s2[++top2]=temp;
        }
        else{
            node *temp=createNode(data[i]);
            s1[++top1]=temp;
        }
    }
    while(top2>=0){
        node *temp=s2[top2];
        node *t1=s1[top1--];
        node *t2=s1[top1--];
        temp->left=t2;
        temp->right=t1;
        s1[++top1]=temp;
        top2--;
    }
    return s1[top1];
}
int main(){
    node *rt;
    printf("please input the expression:\n");
    scanf("%s",str);
    getExpression(expression,str);
//    for (int i=0;i<expLength;i++)
//        printf("%s",expression[i]);
    printf("\n");
    rt=create(expression);
    int flag=1;
    while(flag){
        printf("please select a choice:\n");
        printf("1.Display.\n");
        printf("2.Preorder.\n");
        printf("3.Inorder.\n");
        printf("4.Postorder.\n");
        printf("5.Update.\n");
        printf("6.Calculate.\n");
        printf("7.Exit.\n");
        int c;
        scanf("%d",&c);
        switch(c){
            case 1:{
                for (int i=0;i<expLength;i++)
                    printf("%s",expression[i]);
                printf("\n");
                break;
            }
            case 2:{//preOrder
                preorder(rt);
                printf("\n");
                break;
            }
            case 3:{
                inorder(rt);
                printf("\n");
                break;
            }
            case 4:{
                postorder(rt);
                printf("\n");
                break;
            }
            case 5:{
                printf("please input the variable and the num（# -1 to exit):\n");
                while(1){
                    char now[5];
                    float num;
                    scanf("%s%f",now,&num);
                    if (strcmp(now,"#")==0)
                        break;
                    update(rt,now,num);
                }
                break;
            }
            case 6:{
                float ans=getAns(rt);
                printf("the ans is %f\n",ans);
                break;
            }
            case 7:{
                flag=0;
                break;
            }
        }
    }
}
