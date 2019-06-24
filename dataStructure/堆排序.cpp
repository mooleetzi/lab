#include<iostream>
#include<cstring>
using std::cin;
using std::cout;
template<class T>
void put(T a[], int i, int len){//重构堆
    int child;
    T tmp;
    for (tmp=a[i];2*i+1<len;i = child){
        child = 2*i+1;
        if (child !=len-1&&a[child + 1]>a[child])
            ++child;
        if (tmp<a[child])
            a[i]=a[child];
        else
            break;
    }
    a[i] = tmp;
}
template<class T>
void heapSort(T a[], int len){
    cout<<"heap sort:\n";
    for (int i=len/2;i>=0;--i)
        put(a,i,len);//构造堆
    for(int i=len-1;i>0;--i){
        swap(a[0],a[i]); //将最大元素（根）与数组末尾元素交换，从而实现删除最大元素，重新生成堆
        put(a, 0, i);
    }
    for (int i=0;i<len;i++)
        cout<<a[i]<<" ";
    cout<<"\n";
}
int main(){
    int a[]={1,55,66,44,3,76,89,32,21,65};
    heapSort(a,10);
    return 0;
}
