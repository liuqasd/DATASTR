#include <iostream>
#include <windows.h>
#define MIN -9999999

using namespace std;

typedef int ElemType;
//二叉树的二叉链表存储结构，1个数据域，2个指针域
typedef struct BiTNode
{
    ElemType data;
    BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

//按先序遍历的方式建立二叉树
void CreateBiTree(BiTree *T) //参数为树的头节点
{
    ElemType d;
    cin >> d;
    if (d == 0)
        *T = NULL; //读取#为叶结点
    else
    {
        *T = (BiTree)malloc(sizeof(BiTNode));
        (*T)->data = d;
        CreateBiTree(&(*T)->lchild); //递归构造左子树
        CreateBiTree(&(*T)->rchild); //递归构造右子树
    }
}

void preTraversal(BiTree T, int &maxn, int &sum, int &number)
{
    if (T == NULL)
        return;
    if (T->data > maxn)
        maxn = T->data;
    sum += T->data;
    if (T->data < 0)
        number++;
    preTraversal(T->lchild, maxn, sum, number);
    preTraversal(T->rchild, maxn, sum, number);
    return;
}

int main()
{
    int maxn = MIN, sum = 0, number = 0;
    BiTree T=NULL;
    cout << "请逐个输入数据：" << endl;
    CreateBiTree(&T);
    preTraversal(T, maxn, sum, number);
    cout << "最大值为：" 
         << maxn << endl;
    cout << "和为：" 
         << sum << endl;
    cout << "负数个数为：" 
         << number << endl;
    system("pause");
    return 0;
}