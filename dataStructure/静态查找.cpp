#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
#define MAXSIZE 101
#define OK 1;
typedef struct {
	int key;//�ؼ�����
}ElemType;

typedef struct {
	ElemType *R;
	int length;
}SSTable;
struct block{
    int r[MAXSIZE];
    int minx;
    int operator<(const block&a){
        return minx<a.minx;
    }
}a[MAXSIZE];
int InitList_SSTable(SSTable &L)
{
	L.R = new ElemType[MAXSIZE];
	if (!L.R)
	{
		cout << "��ʼ������";
		return 0;
	}
	L.length = 0;
	return OK;
}

int Insert_SSTable1(SSTable &L)
{
	int j = 0;
	for (int i = 0; i < MAXSIZE; i++)
	{
		L.R[i].key = j;
		L.length++;
		j++;
	}
	return 1;
}

int Insert_SSTable2(SSTable &L)
{
	int j = 1;//�ճ�ST.R[0]��λ��
	for (int i = 1; i < MAXSIZE; i++)
	{
		L.R[i].key = j;
		L.length++;
		j++;
	}
	return 1;
}

int Search_Seq1(SSTable ST, int key) {
	//��˳���ST��˳�������ؼ��ֵ���key������Ԫ�ء����ҵ�������ֵΪ
	//��Ԫ���ڱ��е�λ�ã�����Ϊ0
	for (int i = ST.length; i>0/*________[1]________*/; --i) {
		if (ST.R[i].key==key /*________[2]________*/)
			return i;		//�Ӻ���ǰ��
	}
	return 0;
}// Search_Seq

int Search_Seq2(SSTable ST, int key) {
	//��˳���ST��˳�������ؼ��ֵ���key������Ԫ�ء����ҵ�������ֵΪ
	//��Ԫ���ڱ��е�λ�ã�����Ϊ0
	ST.R[0].key=key /*________[3]________*/;  //���ڱ���
	int i = 0;
	for (i=ST.length;ST.R[i].key!=ST.R[0].key;i-- /*________[3]________*/);		//�Ӻ���ǰ��
	return i;
}// Search_Seq2

int Search_Bin(SSTable ST, int key) {
	// �������ST���۰������ؼ��ֵ���key������Ԫ�ء����ҵ�������ֵΪ
	// ��Ԫ���ڱ��е�λ�ã�����Ϊ0
	int low = 1, high = ST.length;							//�ò��������ֵ
	int  mid;
	while (low<=high/*________[4]________*/)
	{
		mid=(low+high)>>1 /*________[5]________*/;
		if (ST.R[mid].key==key /*________[6]________*/)
			return mid;      						//�ҵ�����Ԫ��
		else if (ST.R[mid].key>key /*________[7]________*/)
			high=mid-1 /*________[8]________*/;							//������ǰһ�ӱ���в���
		else
			low=mid+1 /*________[9]________*/;                       	//�����ں�һ�ӱ���в���
	}//while
	return 0;										//���в����ڴ���Ԫ��
}// Search_Bin
int Search_Block(SSTable ST ,int key){
    int block_size=sqrt(ST.length);
    for (int i=1;i<=block_size;i++){
        int mix=0x3f3f3f3f;
        for (int j=1;j<=block_size;j++){
            a[i].r[j]=ST.R[(i-1)*block_size+j].key;
            if (a[i].r[j]<mix)
                mix=a[i].r[j];
        }
        a[i].minx=mix;
    }
    sort(a+1,a+block_size+1);
    int l=1,r=block_size;
    while(l<=r){
        int mid=(l+r)>>1;
        if (a[mid].minx<=key){
            for (int i=1;i<=block_size;i++)
                if (a[mid].r[i]==key)
                    return (mid-1)*block_size+i;
            l=mid+1;
        }
        else
            r=mid-1;
    }
    return 0;
}
void Show(int result, int testkey)
{
	if (result == 0)
		cout << "δ�ҵ�" << testkey << endl;
	else
		cout << "�ҵ�" << testkey << "λ��Ϊ" << result << endl;
	return;
}
int main()
{
	SSTable ST;
	int testkey1 = 7, testkey2 = 200;
	int result;

	InitList_SSTable(ST);      //��ʹ������ 1~ MAXSIZE �Ĳ��ұ�
	printf("-------------------1.˳�����-------------------\n");
	Insert_SSTable1(ST);
	result = Search_Seq1(ST, testkey1);
	Show(result, testkey1);     //��ʾ���ҽ��
	result = Search_Seq1(ST, testkey2);
	Show(result, testkey2);

	printf("-------------------2.�������ڵ�˳�����-------------------\n");
	InitList_SSTable(ST);
	Insert_SSTable2(ST); //���� 1~ MAXSIZE �Ĳ��ұ�
	result = Search_Seq2(ST, testkey1);
	Show(result, testkey1); //��ʾ���ҽ��
	result = Search_Seq2(ST, testkey2);
	Show(result, testkey2); //��ʾ���ҽ��

	printf("-------------------3.�۰����-------------------\n");
	InitList_SSTable(ST);
	Insert_SSTable2(ST); //���� 1~ MAXSIZE �Ĳ��ұ�
	result = Search_Bin(ST, testkey1);
	Show(result, testkey1); //��ʾ���ҽ��
	result = Search_Bin(ST, testkey2);
	Show(result, testkey2); //��ʾ���ҽ��

	/////////////////���º�������ѧ��ɣ�����Ҫ��//////////////////////////////
	printf("-------------------4.�ֿ����-------------------\n");
	InitList_SSTable(ST);
	Insert_SSTable1(ST);
	result = Search_Block(ST, testkey1);
	Show(result, testkey1);     //��ʾ���ҽ��
	result = Search_Block(ST, testkey2);
	Show(result, testkey2);
	getchar();
}
