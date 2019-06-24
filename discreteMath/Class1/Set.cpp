#include<bits/stdc++.h>
#include<vector>
using namespace std;
typedef vector<int>::iterator vi;
typedef vector<int>mySSet;
char *array=new char[26];
char temp[26]={0};
bool IsMember(mySSet &a,int x){
	vi it;
	for (it=a.begin();it!=a.end();it++)
		if (x==*it) return true;
	return false;
}
void InitSet(mySSet &a,int arr[],int n){
	sort(arr,arr+n);
	for (int i=0;i<n;i++)
		if (!IsMember(a,arr[i]))
		   a.push_back(arr[i]);
}
void PrintSet(mySSet &a){
	vi it;
	for (it=a.begin();it!=a.end();it++)
		cout<<*it<<" ";
	cout<<endl;
}
void Insert(mySSet &a,int x){//向a集合插入x
	int t=a.size();
	if (a[t-1]<x){
		a.push_back(x);
		return;
	}
	for (int i=0;i<t;i++)
		if (x==a[i]) return;
		else if (a[i]<x&&a[i+1]>x){
			a.insert(a.begin()+i+1,1,x);
		}
}
void Delete(mySSet&a,int x){//在a中删除x
	vi it;
	for (it=a.begin();it!=a.end();it++)
		if (*it==x)
		   a.erase(it);
}
mySSet Union(const mySSet &aa,const mySSet &bb){//并集a,b返回一个新集合
	int n=aa.size();
	int m=bb.size();
	mySSet a=aa,b=bb;
	sort(a.begin(),a.end());
	sort(b.begin(),b.end());
	int i=0,j=0;
	vector<int> ans;
	while(i<n||j<m){
		if (a[i]==b[j]){
		   ans.push_back(a[i]);
		   i++;
		   j++;
		}
		else if (a[i]>b[j]){
			ans.push_back(b[j]);
			j++;
		}
		else{
			ans.push_back(a[i]);
			i++;
		}
		if (j==m){
			for (int t=i;t<n;t++)
				ans.push_back(a[t]);
			return ans;
		}
		if (i==n) {
			for (int t=j;t<m;t++)
				ans.push_back(b[t]);
			return ans;
		}
	}
	return ans;
}
mySSet Intersection(const mySSet &aa,const mySSet &bb){
	int i=0,j=0;
	int n=aa.size(),m=bb.size();
	mySSet a=aa,b=bb;
	sort(a.begin(),a.end());
	sort(b.begin(),b.end());
	mySSet ans;
	while(i<n&&j<m){
		if (a[i]==b[j]){
			ans.push_back(a[i]);
			i++;
			j++;
		}
		else if (a[i]>b[j])
			j++;
		else i++;
	}
	return ans;
}
mySSet Difference(const mySSet&aa,const mySSet &bb){
	vi it;
	mySSet a=aa,b=bb;
	//sort(a.begin(),a.end());
	//sort(b.begin(),b.end());
	int n=a.size();
	for (it=a.begin();it!=a.end();){
		if (IsMember(b,*it)){
			it=a.erase(it);
			continue;
		}
		it++;
	}

	return a;
}
int isIncluded(const mySSet &a,const mySSet &b){
	int i,j;
	int n=a.size(),m=b.size();
	if (n<m) return false;
	for (i=0;i<n;i++){
		if (a[i]!=b[i]) return -1;
	}
	if (n==m)
        return 0;
	return 1;
}
void print_mset(const mySSet&a){//求幂集
    int n=1<<a.size();
    for (int i=1;i<=n;i++){
        if (!(i%8))
            cout<<"\n";
        cout<<" {";
        for (int j=0;j<a.size();j++)
            if ((i-1)&(1<<j))
                cout<<a[j]<<" ";
        cout<<"} ";
    }
    cout<<"\n";
}
mySSet Difference2(mySSet &a,mySSet &b){//求对称差
    mySSet ans;
    for (vi q=a.begin();q!=a.end();q++)
        if (!IsMember(b,*q))
            ans.push_back(*q);
    for (vi q=b.begin();q!=b.end();q++)
        if (!IsMember(a,*q))
            ans.push_back(*q);
    return ans;
}
int main(){
	vector<int> a,b,c,d,e,f;
	int q[]={0,1,5,6,8,6,7,3,2,4};
	int p[]={4,6,5,77,5,2,0,66,98,21};
	InitSet(a,q,10);
	InitSet(b,p,10);
	cout<<"集合初始化。。。\n";
	cout<<"a集合:\n";
	PrintSet(a);
	cout<<"b集合:\n";
	PrintSet(b);
	cout<<"已执行在a中插入数据99\n";
	Insert(a,99);//向a中插入99
	cout<<"已执行在b中删除数据5\n";
	Delete(b,5);//在a中删除5
	cout<<"a集合:\n";
	PrintSet(a);
    cout<<"b集合:\n";
	PrintSet(b);
    c=Union(a,b);//并集
	d=Intersection(a,b);//交集
	e=Difference(a,b);//差集
	f=Difference2(a,b);//对称差
	cout<<"a,b并集:\n";
	PrintSet(c);
	cout<<"a,b交集:\n";
	PrintSet(d);
	cout<<"a,b差集:\n";
	PrintSet(e);
    cout<<"a,b对称差:\n";
	PrintSet(f);
	cout<<"a是否包含b,tips(-1不包含，0包含，1真包含):\n"<<isIncluded(a,b)<<"\n";
	cout<<"a,b交集的幂集:\n";
	print_mset(d);
	cout<<"a,b差集的幂集:\n";
	print_mset(e);
	return 0;
}
