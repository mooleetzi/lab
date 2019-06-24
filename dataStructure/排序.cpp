#include<iostream>
#include<cstring>
#include<cmath>
#include<ctime>
#include<cstdlib>
#include<algorithm>
using namespace std;
template<class T>
void copy(T a[],const T b[],int len){//¸´ÖÆbÊý×é
    for (int i=0;i<len;i++)
        a[i]=b[i];
}
template<class T>
void swab(T &a,T &b){
    T tmp=a;
    a=b;
    b=tmp;
}
template<class T>
void bubbleSort(T a[],int len){
    cout<<"bubble sort:\n";
    for (int i=0;i<len-1;i++)
        for (int j=0;j<len-i-1;j++)
            if (a[j]>a[j+1])
                swap(a[j],a[j+1]);
    for (int i=0;i<len;i++)
        cout<<a[i]<<" ";
    cout<<"\n";
}
template<class T>
void selectSort(T a[],int len){
    cout<<"select sort:\n";
    for (int i=0;i<len-1;i++){
        T minx=a[i];
        for (int j=i+1;j<len;j++)
        if (a[j]<minx)
            minx=a[j];
        a[i]=minx;
    }
    for (int i=0;i<len;i++)
        cout<<a[i]<<" ";
    cout<<"\n";
}
template<class T>
void dinsertSort(T a[],int len){
    cout<<"direct insert sort:\n";
    for (int i=1;i<len;i++){
        int j=i;
        T tmp=a[j];
        while(j>0&&a[j-1]>tmp){
            a[j]=a[j-1];
            j--;
        }
        a[j]=tmp;
    }
    for (int i=0;i<len;i++)
        cout<<a[i]<<" ";
    cout<<"\n";
}
template<class T>
void binsertSort(T a[],int len){
    cout<<"binary insert sort:\n";
    for (int i=1;i<len;i++){
        int mid=upper_bound(a,a+i,a[i])-a;
        int tmp=a[i];
        for (int k=i;k>mid;k--)
            a[k]=a[k-1];
        a[mid]=tmp;
    }
    for (int i=0;i<len;i++)
        cout<<a[i]<<" ";
    cout<<"\n";
}
template<class T>
void shellSort(T a[],int len){
    cout<<"shell sort:\n";
    int block=len;
    while(block>1){
        block=block/2;
        for (int i=block;i<len;i++){
            int j=i;
            T tmp=a[i];
            while(j-block>-1&&a[j-block]>tmp){
                a[j]=a[j-block];
                j-=block;
            }
            a[j]=tmp;
        }
    }
    for (int i=0;i<len;i++)
        cout<<a[i]<<" ";
    cout<<"\n";
}
template<class T>
void Qsort(T a[],int l,int r){
    if (l>=r)
        return;
    int i=l,j=r;
    T key=a[l];
    while(i<j){
        while(i<j&&key<=a[j]) j--;
        a[i]=a[j];
        while(i<j&&key>=a[i]) i++;
        a[j]=a[i];
    }
    a[i]=key;
    Qsort(a,l,i-1);
    Qsort(a,i+1,r);
}
template<class T>
void quickSort(T a[],int len){
    cout<<"quick sort:\n";
    Qsort(a,0,len-1);
    for (int i=0;i<len;i++)
        cout<<a[i]<<" ";
    cout<<"\n";

}
int main(){
    int a[10],b[10];
    srand(time(0));
    for (int i=0;i<10;i++)
        a[i]=rand()%1000+1;
    copy(b,a,10);
    bubbleSort(b,10);
    copy(b,a,10);
    selectSort(b,10);
    copy(b,a,10);
    dinsertSort(c,10);
    copy(b,a,10);
    binsertSort(d,10);
    copy(b,a,10);
    shellSort(e,10);
    copy(b,a,10);
    quickSort(f,10);
    return 0;
}

