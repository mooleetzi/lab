#include<iostream>
#include<iomanip>
#include<cstring>
using namespace std;
const int n=64;
const int m=4;
int p[n];//页
struct Page{
    int pageNum;//页号
    int isIn;//是否在主存中
    int blockNum;//主存中块号
}page[n];//页表
void init(){
    for (int i=0;i<n;i++){
        page[i].blockNum=-1;
        page[i].isIn=0;
        page[i].pageNum=i;
    }
    for (int i=0;i<m;i++){
        p[i]=i;
        page[i].blockNum=i;
        page[i].isIn=1;
    }
}
void showPage(){
    cout<<"页号\t"<<"是否在主存中\t"<<"块号\t\n";
    for (int i=0;i<n;i++)
        cout<<page[i].pageNum<<"\t"<<page[i].isIn<<"\t"<<page[i].blockNum<<"\t\n";
}
int main(){
    init();
    showPage();
    int flag=1;
    while(flag){
        cout<<"请输入指令地址:\n";
        int logicAd,logicNum,innerAd,phyNum,phyAd;
        cin>>hex>>logicAd;
        if (logicAd==-1)
            break;
        logicNum=logicAd>>10;
//        cout<<"页号为:"<<logicNum<<"\n";
        innerAd=logicAd&0x3f;
//        cout<<"业内地址:"<<innerAd<<"\n";
        int q=0;
        for (int i=0;i<n;i++)
        if (page[i].pageNum==logicNum&&page[i].isIn){
            q=1;
            phyNum=page[i].pageNum;
//            cout<<"请求的主存块号为:"<<phyNum<<"\n";
            phyAd=phyNum<<10|innerAd;
//            cout<<"请求的物理地址为:"<<phyAd<<"\n";
            cout<<phyAd<<"\n";
            break;
        }
        if (!q)
            cout<<"*\n";
    }
}
