#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<ctime>
using std::cin;
using std::cout;
struct binSearchTree{
    int val;
    binSearchTree *left,*right;
    binSearchTree(){
        val=int();
        left=right=nullptr;
    }
    void insert(int v){
        if (val==int())
            val=v;
        if (v==val)
            return;
        if (left==nullptr&&v<val){
            left=new binSearchTree();
            left->insert(v);
            return;
        }
        else if (right==nullptr&&v>val){
            right=new binSearchTree();
            right->insert(v);
            return;
        }
        if (v>val)
            right->insert(v);
        else if (v<val)
            left->insert(v);
    }
    void printInorder(){
        if (left)
            left->printInorder();
        cout<<val<<" ";
        if (right)
            right->printInorder();
    }
    binSearchTree* find(int v){
        if (v==val)
            return this;
        if (v<val){
            if (left)
                left->find(v);
            else
                return nullptr;
        }
        else{
            if (right)
                right->find(v);
            else
                return nullptr;
        }
    }
    binSearchTree *searchParent(int data){
        if ((left&&left->val==data)||(right&&right->val==data))
            return this;
        if (data>val){
            if (right==nullptr)
                return nullptr;
            right->searchParent(data);
        }
        else if (data<val){
            if (left==nullptr)
                return nullptr;
            left->searchParent(data);
        }
        return nullptr;
    }
    void del(int data){
        //��ɾ��֮ǰ��Ҫ�ҵ����ĸ���
        binSearchTree *parent = searchParent(data);
        if (parent==nullptr)          //������ڵ�Ϊ�գ�˵��������ǿ�����û��ɾ
            return;
        //����������Ҫɾ���Ľڵ���
        binSearchTree *deleteNode = find(data);
        if (deleteNode==nullptr)      //�����Ҳ���Ҫɾ���Ľڵ�
            return;
        //ɾ���ڵ��� 4 �����
        //1.����������Ϊ�գ�˵����Ҷ�ӽڵ㣬ֱ��ɾ��
        if (deleteNode->left==nullptr&&deleteNode->right==nullptr){
            //ɾ���ڵ�
            delete deleteNode;
            deleteNode = nullptr;
            //���ø��ڵ�ĺ���״̬�����������Ժ�û�����������
            if (parent->left!= nullptr&&parent->left->val== data){
                delete parent->left;
                parent->left=nullptr;
            }
            else{
                delete parent->right;
                parent->right=nullptr;
            }
            return;
        }
        else if (deleteNode->left!=nullptr&&deleteNode->right==nullptr){
            //2.Ҫɾ���Ľڵ�ֻ����������������Ҫ�̳�λ��
            if (parent->left!=nullptr&&parent->left->val==data)
                parent->left=deleteNode->left;
            else
                parent->right=deleteNode->left;
            deleteNode = nullptr;
            return;
        }
        else if (deleteNode->right!=nullptr&&deleteNode->left==nullptr){
            //3.Ҫɾ���Ľڵ�ֻ����������������Ҫ�̳�λ��
            if (parent->right!=nullptr&&parent->left->val==data)
                parent->left=deleteNode->right;
            else
                parent->right=deleteNode->right;
            deleteNode=nullptr;
        }
        else
        {
            //4.Ҫɾ���Ľڵ��Ů˫ȫ��������������������������Ҫѡһ�����ʵĽڵ�̳У�����ʹ��������������ڵ�
            binSearchTree *copyOfDeleteNode=deleteNode;   //Ҫɾ���ڵ�ĸ�����ָ��̳нڵ�ĸ��ڵ�
            binSearchTree *heresNode=deleteNode->right; //Ҫ�̳�λ�õĽڵ㣬��ʼΪҪɾ���ڵ��������������
            //������û�������ˣ���������С�ģ�ֱ����λ
            if (heresNode->left==nullptr){
                //��λ���ֵܱ���˺���
                heresNode->left=deleteNode->left;
            }
            else{
                //�����������ӣ�ѭ���ҵ�����ģ�����С��
                while (heresNode->left!= nullptr){
                    copyOfDeleteNode = heresNode;       //copyOfDeleteNode ָ��̳нڵ�ĸ��ڵ�
                    heresNode = heresNode->left;
                }
                //�ҵ��˼̳нڵ㣬�̳нڵ��������������еĻ���Ҫ����һλ
                copyOfDeleteNode->left=heresNode->right;
                //�̳нڵ��ȼ̳м�ҵ�����Լ������Һ��ӱ��Ҫɾ���ڵ�ĺ���
                heresNode->left=deleteNode->left;
                heresNode->right=deleteNode->right;
            }
            //������ȷ��λ�ã���Ҫɾ���ڵ�ĸ��ڵ���ʶ�¶���
            if (parent->left!=nullptr&&parent->left->val== data)
            {
                parent->left=heresNode;
            }
            else
            {
                parent->right=heresNode;
            }
        }
    }
};
int main(){
    binSearchTree a;
    int info[]={22,55,33,56,77,84,62,89,94,76};
    for (int i=0;i<10;i++)
        a.insert(info[i]);
    if (a.find(33))
        cout<<"search successfully\n";
    else
        cout<<"search failed\n";
    a.printInorder();
    cout<<"\n";
    a.del(55);
    a.printInorder();
    return 0;
}
