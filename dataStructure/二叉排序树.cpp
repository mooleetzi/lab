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
        //在删除之前需要找到它的父亲
        binSearchTree *parent = searchParent(data);
        if (parent==nullptr)          //如果父节点为空，说明这个树是空树，没法删
            return;
        //接下来该找要删除的节点了
        binSearchTree *deleteNode = find(data);
        if (deleteNode==nullptr)      //树中找不到要删除的节点
            return;
        //删除节点有 4 种情况
        //1.左右子树都为空，说明是叶子节点，直接删除
        if (deleteNode->left==nullptr&&deleteNode->right==nullptr){
            //删除节点
            delete deleteNode;
            deleteNode = nullptr;
            //重置父节点的孩子状态，告诉他你以后没有这个儿子了
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
            //2.要删除的节点只有左子树，左子树要继承位置
            if (parent->left!=nullptr&&parent->left->val==data)
                parent->left=deleteNode->left;
            else
                parent->right=deleteNode->left;
            deleteNode = nullptr;
            return;
        }
        else if (deleteNode->right!=nullptr&&deleteNode->left==nullptr){
            //3.要删除的节点只有右子树，右子树要继承位置
            if (parent->right!=nullptr&&parent->left->val==data)
                parent->left=deleteNode->right;
            else
                parent->right=deleteNode->right;
            deleteNode=nullptr;
        }
        else
        {
            //4.要删除的节点儿女双全，既有左子树又有右子树，需要选一个合适的节点继承，这里使用右子树中最左节点
            binSearchTree *copyOfDeleteNode=deleteNode;   //要删除节点的副本，指向继承节点的父节点
            binSearchTree *heresNode=deleteNode->right; //要继承位置的节点，初始为要删除节点的右子树的树根
            //右子树没有左孩子了，他就是最小的，直接上位
            if (heresNode->left==nullptr){
                //上位后，兄弟变成了孩子
                heresNode->left=deleteNode->left;
            }
            else{
                //右子树有左孩子，循环找到最左的，即最小的
                while (heresNode->left!= nullptr){
                    copyOfDeleteNode = heresNode;       //copyOfDeleteNode 指向继承节点的父节点
                    heresNode = heresNode->left;
                }
                //找到了继承节点，继承节点的右子树（如果有的话）要上移一位
                copyOfDeleteNode->left=heresNode->right;
                //继承节点先继承家业，把自己的左右孩子变成要删除节点的孩子
                heresNode->left=deleteNode->left;
                heresNode->right=deleteNode->right;
            }
            //最后就是确认位置，让要删除节点的父节点认识新儿子
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
