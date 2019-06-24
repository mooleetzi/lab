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
const int vsize=6;     //��������ĳ��ȣ�����Ԫ������
char  varList[vsize];   //���ڴ�������Ԫ��
int  vNum;            //��ŵ�ǰ���⹫ʽ�б�Ԫ�ĸ���
map<char,int> opt;
vector<int> dnf,cnf;//��ȡ��ʽ����ȡ��ʽ
//ɨ����ʽ�������ַ��������б�Ԫ����varList�����У�ÿ����Ԫֻ���һ�Σ������Ұ�����������
//ע���޸�vNum��ֵ����ǰ��Ԫ������
void createVarList(string source)//ok
{
	char ch;
	for(unsigned int i=0;i<source.size()&&(ch=source[i])!='@';i++)//ɨ�����⹫ʽ�������ַ�
		if(!strchr("+-|&!()@",ch))		//��ch�������������Ϊ�����Ԫ
		{
			int j;
			for(j=vNum-1;j>=0&&varList[j]>ch;j--)//�ڱ�Ԫ��varList�����в���ch�Ĳ���λ�ã�ʹ֮��������
				varList[j+1]=varList[j];
			if(varList[j]<ch)       //��varList[j]==ch�����ʾ�ñ�Ԫ�Ѿ������varList�����У������ٴβ���
			{
			    varList[j+1]=ch;
			    vNum++;
				//���в�������
			}
		}
    //cout<<varList<<"\n";
}

int ComparePriority(char op1,char op2)
{
    if (!strchr("!+-&|@",op1)||!strchr("!+-&|@",op2))
        return 0;//�������򷵻�0
    else if (opt[op1]>opt[op2])
        return 1;//op1���ȼ�����op2
    else if (opt[op1]<opt[op2])
        return -1;
    else if (op1==op2)
        return 2;
	//�Ƚ������op1��op2�����ȼ��𣬷���ֵΪ-1��0��1
}

//����ָ����Ԫp�ڱ�Ԫ��varList[]�����еĴ��λ�ã��±꣩��������
int locOfProp(char p)
{
	int loc ;
	for(loc=0;varList[loc]!=p&&loc<vNum;loc++);
	return loc;
}

//������v�еĵ�ǰ��ֵȡֵ+1,������v�д�ŵ���000,�򱾺���ִ�������001
void IncreaseVarValue(int *v)
{
    v[vNum-1]++;
    for (int i=vNum-2;i>-1;i--)
    if (v[i+1]>1){
        v[i]++;
        v[i+1]=0;
    }
	//���в�������
}


//����op1��op2��op����������㣬���ѽ������.
bool Caculate(bool op1,bool op2,char op)
{
	bool result;
	/*switch (op)
	{
		//���в�������
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
//�����⹫ʽ��һ�鸳ֵ(�����varValue[]�����У��µ���ֵȡֵ�������������ֵ����
bool InfixValue(string source,int* varValue)
{
	stack<char> stOPR;  //���������ջ
	stack<bool> stOPD;  //���������ջ

	char op,ch='@';
	int i=0;
	source+="@@@@@@";
	stOPR.push(ch);
	while((ch=source[i])!='@'||stOPR.top()!='@')	{
		if(!strchr("+-|&!()@",ch)){ //�Ǳ�Ԫ����Ϊ������������ȡ��Ԫ�ĵ�ǰ��ֵѹ���ջ��
			stOPD.push(varValue[locOfProp(ch)]);
			++i;
			//cout<<varValue[locOfProp(ch)]<<"\n";
		}
		else{
            i++;
            op=stOPR.top();
            switch(ComparePriority(op,ch)){
                case 1://ǰһ���������ȼ���
                    stOPR.pop();//��һ��������ջ
                    if(ch!='@')
                        stOPR.push(ch);//�ڶ���������ջ
                    if (op=='!'){
                        int now=stOPD.top();
                        stOPD.pop();
                        stOPD.push(!now);
                    }
                    else{
                        int o2=stOPD.top();//�ڶ�������
                        stOPD.pop();
                        int o1=stOPD.top();//��һ������
                        stOPD.pop();
                        stOPD.push(Caculate(o1,o2,op));
                        //cout<<stOPD.top()<<"\n";
                    }
                    break;
                case -1://�ڶ�����������
                    stOPR.push(ch);
                    break;
                case 0://������
                    if (ch=='(')
                        stOPR.push(ch);
                    else if (op=='('){
                        stOPR.pop();//������
                        stOPR.push(ch);//��ջ������
                    }
                    else if (ch==')'){
                        stOPR.pop();
                        if (op=='!'){
                            int now=stOPD.top();
                            stOPD.pop();
                            stOPD.push(!now);
                        }
                        else{
                            int o2=stOPD.top();//�ڶ�������
                            stOPD.pop();
                            int o1=stOPD.top();//��һ������
                            stOPD.pop();
                            stOPD.push(Caculate(o1,o2,op));
                            //cout<<stOPD.top()<<"\n";
                        }
                    }
                    break;
                case 2://����������ͬ
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
	string exp;      //���⹫ʽ�����exp��
	cout<<"Enter the Proposition Formulae  ,ended by @:"<<endl;
	getline(cin,exp);//�Ӽ��̶����ʽ��ʽ����@��Ϊ������
	//==========������׺ʽ��ֵ====
	createVarList(exp);
	int *v1=new int[vNum];        //��ű�Ԫÿһ�ָ�ֵȡֵ���
	for(unsigned  int i=0;i<vNum;i++)  v1[i]=0;//��ʽ�ĵ�һ�и�ֵ

	for(int i=0;i<vNum;i++)           //�����ͷ
		cout<<setw(4)<<varList[i];
	cout<<'|'<<setw(10)<<exp<<endl;
	int n=int(pow(2,vNum));          //��ֵ������
	for(int i=0;i<n;i++)
	{
		result=InfixValue(exp,v1);  //���㵱ǰ��ֵ����µ���ֵ
		for(unsigned  int j=0;j<vNum;j++)//�����ǰ��
			cout<<setw(4)<<v1[j];
        if (result)
            dnf.push_back(i);
        else
            cnf.push_back(i);
		cout<<'|'<<setw(10)<<result<<endl;
		IncreaseVarValue(v1);		//��ʽ��ÿ�и�ֵ����һ�л�����+1��
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

