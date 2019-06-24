#include<stdlib.h>
#include<iomanip>
#include"windows.h"
#include"os.h"
#define n 64//实验中假定主存的长度
#define m 4//实验中假定每个作业分得主存块块数
int p[m];//定义页
 struct
 {
 short int lnumber;//页号
 short int flag;//表示该页是否在主存，“1”表示在主存，“0”表示不在主存
 short int pnumber;//该页所在主存块的块号
 short int write;//该页是否被修改过，“1”表示修改过，“0”表示没有修改过
 short int dnumber;//该页存放在磁盘上的位置，即磁盘块号
 short int times;//被访问的次数，用于LRU算法
}page[n];//定义页表
//各个函数的实现如下：
computer::computer()
{
 int i;
 for(i=0;i<n;i++)
 {
  page[i].lnumber = i;
  page[i].flag = 0;
  page[i].pnumber = 10000;//用10000表示为空
  page[i].write = 0;
  page[i].dnumber = i;
  page[i].times = 0;
 }//初始化页表

 for(i=0;i<m;i++)
 {
  page[i].pnumber = i;
 }

 for(i=0;i<m;i++)
 {
  p[i] = i;
  page[i].flag = 1;
 }//初始化页
}
void computer::showpagelist()
{
    int i;
 cout<<"页号"<<"\t"<<"是否在主存中"<<"\t"<<"块  号"<<"\t"<<"是否被修改过"<<"\t"<<"磁盘块号"<<"\t"<<"访问次数"<<endl;
 for(i=0;i<n;i++)
 {
  cout<<page[i].lnumber<<"\t"<<page[i].flag<<"               "<<page[i].pnumber<<"\t"<<page[i].write<<"                  "<<page[i].dnumber<<"          \t"<<page[i].times<<endl;
 }
}
void computer::showpage()
{
    int i;
 for(i=0;i<m;i++)
 {
  cout<<"\t"<<p[i];
 }
 cout<<endl;
}
 void computer::transformation()
{
   unsigned logicAddress,logicNumber,innerAddress,physicsAddress,physicsNumber;
 int i,head=0,fail = 0;
 int method,temppage=0;
 short int times = 10000;
 cout<<"请输入一个逻辑地址（四位十六进制数）:";
 cin>>hex>>logicAddress;//读入逻辑地址
 logicNumber = logicAddress >> 10;//得到页号
 cout<<"页号为:"<<logicNumber<<endl;
 innerAddress = logicAddress & 0x03ff;//得到页内地址
 cout<<"页内地址为:"<<innerAddress<<endl;
 for(i=0;i<n;i++)
 {
  if(logicNumber==(unsigned)page[i].lnumber)
  {
   if(page[i].flag == 1)
   {
    cout<<"请求的页面在主存中!"<<endl;
    page[i].times++;
    physicsNumber = page[i].pnumber;//由页号得到块号
    cout<<"请求的主存块号为:"<<physicsNumber<<endl;
    physicsAddress = physicsNumber << 10 |innerAddress;//得到物理地址
    cout<<"请求的物理地址为:"<<physicsAddress<<endl;//输出物理地址
    break;
   }
   else
   {

    cout<<"请求的页面不在主存中! 将进行缺页中断处理!"<<endl<<"请选择算法!"<<endl;
    cout<<"1.先进先出"<<endl<<"2.最近最少用"<<endl<<"请选择置换算法:";
    cin>>method;
    if(method == 1) //采用先进先出算法
    {
     cout<<"采用先进先出算法!"<<endl;
     fail = p[head];
     cout<<"第"<<fail<<"页将被替换!"<<endl;
     p[head] = logicNumber;
     head = (head+1) % m;
     if(page[fail].write == 1)
     cout<<"第"<<fail<<"页曾被修改过!"<<endl;
     page[fail].flag = 0;
     page[logicNumber].flag = 1;
     page[logicNumber].write = 0;
     page[logicNumber].pnumber = page[fail].pnumber;
     page[fail].pnumber = 10000;
     page[logicNumber].times++;
     break;
    }
    else if(method == 2) //采用最近最少用算法
    {
     cout<<"采用最近最少用算法!"<<endl;
     for(i=0;i<n;i++)
     {
      if(page[i].flag == 1)
      {
       if(page[i].times<times)
       {
        times = page[i].times;
        temppage = page[i].lnumber;
       }
      }
     }
     cout<<"第"<<temppage<<"页将被替换!"<<endl;
     for(i=0;i<m;i++)
     {
      if(p[i] == temppage)
      {
       p[i] = logicNumber;
      }
     }
     if(page[temppage].write == 1)
     cout<<"第"<<temppage<<"页曾被修改过!"<<endl;
     page[temppage].flag = 0;
     page[logicNumber].flag = 1;
     page[logicNumber].write = 0;
     page[logicNumber].pnumber = page[temppage].pnumber;
     page[temppage].pnumber = 10000;
     page[logicNumber].times++;
     break;
    }
    else
    { cout<<"你输入有误，即将退出!";
      exit(1);
    }
   }
  }
 }
}
void main()
{
 char c,d;
 computer os;
 cout<<"页表正在初始化中...，3秒钟后为你显示页和页表！"<<endl;
 Sleep(3000);
 os.showpage();
 os.showpagelist();
 T:
 os.transformation();
 cout<<"是否显示页和页表？（Y/N）";
 cin>>c;
 switch(c)
 {
 case 'y':
  os.showpage();
  os.showpagelist();
 case 'n':
  cout<<"是否继续进行请求分页？（Y/N）";
  cin>>d;
  if (d=='Y'||d=='y')
     goto T;
  else if (d=='N'||d=='n')
   exit(1);
  else
   cout<<"输入错误！"<<endl;
 default:cout<<"输入错误！"<<endl;
 }

}
