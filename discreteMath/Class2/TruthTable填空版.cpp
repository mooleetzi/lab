#include <iostream>
#include <iomanip>
#include <stack>
#include <cstring>
#include <string>
#include <cmath>
#include<map>
#include<vector>
using namespace std;
typedef vector<int>::iterator vi;
const int vsize=6;     //定义数组的长度，即变元最大个数
char  varList[vsize];   //用于存放命题变元表
int  vNum;            //存放当前命题公式中变元的个数
map<char,int> opt;
vector<int> dnf,cnf;//析取范式，合取范式
//扫描表达式中所有字符，将所有变元存在varList数组中（每个变元只存放一次），并且按递增有序存放
//注意修改vNum的值（当前变元个数）
void createVarList(string source)//ok
{
	char ch;
	for(unsigned int i=0;i<source.size()&&(ch=source[i])!='@';i++)//扫描命题公式中所有字符
		if(!strchr("+-|&!()@",ch))		//若ch不是运算符，则为命题变元
		{
			int j;
			for(j=vNum-1;j>=0&&varList[j]>ch;j--)//在变元表varList数组中查找ch的插入位置，使之保持有序
				varList[j+1]=varList[j];
			if(varList[j]<ch)       //若varList[j]==ch，则表示该变元已经存放在varList数组中，无需再次插入
			{
			    varList[j+1]=ch;
			    vNum++;
				//自行补充完整
			}
		}
    //cout<<varList<<"\n";
}

int ComparePriority(char op1,char op2)
{
    if (!strchr("!+-&|@",op1)||!strchr("!+-&|@",op2))
        return 0;//有括号则返回0
    else if (opt[op1]>opt[op2])
        return 1;//op1优先级大于op2
    else if (opt[op1]<opt[op2])
        return -1;
    else if (op1==op2)
        return 2;
	//比较运算符op1、op2的优先级别，返回值为-1，0，1
}

//查找指定变元p在变元表varList[]数组中的存放位置（下标），并返回
int locOfProp(char p)
{
	int loc ;
	for(loc=0;varList[loc]!=p&&loc<vNum;loc++);
	return loc;
}

//将数组v中的当前赋值取值+1,若数组v中存放的是000,则本函数执行完后变成001
void IncreaseVarValue(int *v)
{
    v[vNum-1]++;
    for (int i=vNum-2;i>-1;i--)
    if (v[i+1]>1){
        v[i]++;
        v[i+1]=0;
    }
	//自行补充完整
}


//计算op1与op2做op运算符的运算，并把结果返回.
bool Caculate(bool op1,bool op2,char op)
{
	bool result;
	/*switch (op)
	{
		//自行补充完整
	}*/
	switch (op){
        case '&':
            if (op1&&op2)
                result=1;
            else
                result=0;
            break;
        case '|':
            if (op1||op2)
                result=1;
            else
                result=0;
            break;
        case '-':
            if (op1&&!op2)
                result=0;
            else
                result=1;
            break;
        case '+':
            if (op1==op2)
                result=1;
            else
                result=0;
            break;
	}
	return result;
}
//求命题公式在一组赋值(存放在varValue[]数组中）下的真值取值情况，并将其真值返回
bool InfixValue(string source,int* varValue)
{
	stack<char> stOPR;  //定义运算符栈
	stack<bool> stOPD;  //定义操作数栈

	char op,ch='@';
	int i=0;
	source+="@@@@@@";
	stOPR.push(ch);
	while((ch=source[i])!='@'||stOPR.top()!='@')	{
		if(!strchr("+-|&!()@",ch)){ //是变元（即为操作数），则取变元的当前赋值压入堆栈中
			stOPD.push(varValue[locOfProp(ch)]);
			++i;
			//cout<<varValue[locOfProp(ch)]<<"\n";
		}
		else{
            i++;
            op=stOPR.top();
            switch(ComparePriority(op,ch)){
                case 1://前一个操作符先计算
                    stOPR.pop();//第一操作符退栈
                    if(ch!='@')
                        stOPR.push(ch);//第二操作符入栈
                    if (op=='!'){
                        int now=stOPD.top();
                        stOPD.pop();
                        stOPD.push(!now);
                    }
                    else{
                        int o2=stOPD.top();//第二操作数
                        stOPD.pop();
                        int o1=stOPD.top();//第一操作数
                        stOPD.pop();
                        stOPD.push(Caculate(o1,o2,op));
                        //cout<<stOPD.top()<<"\n";
                    }
                    break;
                case -1://第二操作符计算
                    stOPR.push(ch);
                    break;
                case 0://有括号
                    if (ch=='(')
                        stOPR.push(ch);
                    else if (op=='('){
                        stOPR.pop();//弹出（
                        stOPR.push(ch);//入栈操作符
                    }
                    else if (ch==')'){
                        stOPR.pop();
                        if (op=='!'){
                            int now=stOPD.top();
                            stOPD.pop();
                            stOPD.push(!now);
                        }
                        else{
                            int o2=stOPD.top();//第二操作数
                            stOPD.pop();
                            int o1=stOPD.top();//第一操作数
                            stOPD.pop();
                            stOPD.push(Caculate(o1,o2,op));
                            //cout<<stOPD.top()<<"\n";
                        }
                    }
                    break;
                case 2://两操作符相同
                    if (op=='!'){
                        int now=stOPD.top();
                        stOPD.pop();
                        stOPD.push(!now);
                    }
                    else{
                        int o2=stOPD.top();
                        stOPD.pop();
                        int o1=stOPD.top();
                        stOPD.pop();
                        stOPD.push(Caculate(o1,o2,op));
                        //cout<<stOPD.top()<<"\n";
                    }
                    break;
            }
		}
	}
	while(!stOPR.empty()&&stOPR.top()!='@'){
        //cout<<stOPR.top()<<" ";
		stOPR.pop();
	}
	return stOPD.top();
}
int main()
{

    opt['!']=5;
    opt['&']=4;
    opt['|']=3;
    opt['-']=2;
    opt['+']=1;
    opt['(']=opt[')']=0;
    opt['@']=-1;
	int result;
	string exp;      //命题公式存放在exp中
	cout<<"Enter the Proposition Formulae  ,ended by @:"<<endl;
	getline(cin,exp);//从键盘读入合式公式，以@作为结束符
	//==========测试中缀式求值====
	createVarList(exp);
	int *v1=new int[vNum];        //存放变元每一种赋值取值情况
	for(unsigned  int i=0;i<vNum;i++)  v1[i]=0;//公式的第一行赋值

	for(int i=0;i<vNum;i++)           //输出表头
		cout<<setw(4)<<varList[i];
	cout<<'|'<<setw(10)<<exp<<endl;
	int n=int(pow(2,vNum));          //真值表行数
	for(int i=0;i<n;i++)
	{
		result=InfixValue(exp,v1);  //计算当前赋值情况下的真值
		for(unsigned  int j=0;j<vNum;j++)//输出当前行
			cout<<setw(4)<<v1[j];
        if (result)
            dnf.push_back(i);
        else
            cnf.push_back(i);
		cout<<'|'<<setw(10)<<result<<endl;
		IncreaseVarValue(v1);		//公式的每行赋值（上一行基础上+1）
	}
	cout<<exp<<"'s principal disjunctive normal form is:";
	for (vi t=dnf.begin();t!=dnf.end();t++)
        cout<<"m"<<*t<<" ";
    cout<<"\n";
    cout<<exp<<"'s principal conjunctive normal form is:";
	for (vi t=cnf.begin();t!=cnf.end();t++)
        cout<<"M"<<*t<<" ";
    cout<<"\n=========================="<<endl;
	delete []v1;
	return 0;
}

