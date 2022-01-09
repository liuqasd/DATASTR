#include <iostream>
#include <stdlib.h>
#include <windows.h>
#define MAX_SIZE 100

using namespace std;
typedef char ElemType;
//二叉树的二叉链表存储结构，1个数据域，2个指针域
typedef struct BiTNode
{
    ElemType data;
    BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

//循环队列定义
typedef struct SeqQueue
{
    BiTree data[MAX_SIZE]; //二叉链表类型指针数组
    int front, rear;       //队首指针，队尾指针
} SeqQue, *SeQue;

//按先序遍历的方式建立二叉树
void CreateBiTree(BiTree *T) //参数为树的头节点
{
    ElemType ch;
    cin >> ch;
    if (ch == '#')
        *T = NULL; //读取#为叶结点
    else
    {
        *T = (BiTree)malloc(sizeof(BiTNode));
        (*T)->data = ch;
        CreateBiTree(&(*T)->lchild); //递归构造左子树
        CreateBiTree(&(*T)->rchild); //递归构造右子树
    }
}

//对遍历到的结点数据进行输出
void operate(ElemType ch)
{
    cout << ch << " ";
}

//递归方式先序遍历二叉树
void PreOrderTraverse(BiTree T, int level)
{
    if (T == NULL)
        return;

    operate(T->data);
    PreOrderTraverse(T->lchild, level + 1);
    PreOrderTraverse(T->rchild, level + 1);
}

//递归方式中序遍历二叉树
void InOrderTraverse(BiTree T, int level)
{
    if (T == NULL)
        return;

    InOrderTraverse(T->lchild, level + 1);
    operate(T->data);
    InOrderTraverse(T->rchild, level + 1);
}

//递归方式后序遍历二叉树
void PostOrderTraverse(BiTree T, int level)
{
    if (T == NULL)
        return;

    PostOrderTraverse(T->lchild, level + 1);
    PostOrderTraverse(T->rchild, level + 1);
    operate(T->data);
}
//初始化循环队列
void InitQue(SeQue Q)
{
    Q->front = Q->rear = 0;
}

//判断队列空
int EmptyQue(SeQue Q)
{
    if (Q->front == Q->rear)
        return 1;
    else
        return 0;
}

//入队
int InQue(SeQue Q, BiTree T)
{
    if ((Q->rear + 1) % MAX_SIZE == Q->front)
    {
        cout << "队列已满！" << endl; //队列满，入队失败
        return 0;
    }
    else
    {
        Q->rear = (Q->rear + 1) % MAX_SIZE;
        Q->data[Q->rear] = T;
        return 1; //入队成功
    }
}

//出队
int OutQue(SeQue Q)
{
    if (EmptyQue(Q)) //判断队列是否为空
    {
        cout << "队列空！" << endl;
        return 0;
    }
    else
    {
        Q->front = (Q->front + 1) % MAX_SIZE; //不为空，出队
        return 1;
    }
}

//取队列首元素
BiTree Gethead(SeQue Q)
{
    if (EmptyQue(Q)) //	判断队列是否为空
        return 0;
    else
        return Q->data[(Q->front + 1) % MAX_SIZE];
}

//层序遍历二叉树
void LevelOrderTraverse(BiTree T)
{
    BiTree p=T;
    SeqQue Q;                               //声明一个队列
    InitQue(&Q);                            //初始化队列
    if(p!=NULL)
    {
        InQue(&Q, p);                       //根节点入队
        while(!EmptyQue(&Q))
        {
            p = Gethead(&Q);
            OutQue(&Q);                     //节点出队
            cout << p->data << " ";         //被访问节点
            if(p->lchild!=NULL)
                InQue(&Q, p->lchild);       //左子树入队
            if(p->rchild!=NULL)
                InQue(&Q, p->rchild);       //右子树入队
        }
    }
}

int main()
{
    int level = 1;                          //表示层数
    BiTree T = NULL;
    cout << "请以先序遍历的方式输入扩展二叉树(类似输入AB#D##C##)：";
    CreateBiTree(&T);                       //建立二叉树

    cout << "递归先序遍历输出为：" << endl;
    PreOrderTraverse(T, level);             //前序遍历
    cout << endl;

    cout << "递归中序遍历输出为：" << endl;
    InOrderTraverse(T, level);              //中序遍历
    cout << endl;

    cout << "递归后序遍历输出为：" << endl;
    PostOrderTraverse(T, level);            //后序遍历
    cout << endl;

    cout << "层序遍历输出为：" << endl;
    LevelOrderTraverse(T);                  //层序遍历
    cout << endl;

    system("pause");
    return 0;
}