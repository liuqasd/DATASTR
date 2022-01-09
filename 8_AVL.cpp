#include <stdio.h>
#include <stdlib.h>

typedef struct AVLTNode
{
    int key; //数据
    int bf;  //平衡因子，正为L,负为R
    int num; //输入序号
    struct AVLTNode *lchild;
    struct AVLTNode *rchild;
} AVLTNode, *AVLTree;

/*根据输入的arr数组，按数组中元素的顺序构建一棵平衡二叉排序树*/
void InsertAVLTree(AVLTree &bt, int k, int i) //树，结点数据，第几个结点（arr数组）
{
    AVLTree S; //新结点
    AVLTree a, fa, p, fp, b, c;
    //将k（结点数据）先插入到新节点S,同时使s的左右子树为NULL
    S = new AVLTNode();
    S->key = k;
    S->num = i + 1;
    S->lchild = NULL;
    S->rchild = NULL;
    S->bf = 0;      //平衡因子
    if (bt == NULL) //如果平衡树为空，那么s直接插入
        bt = S;
    else
    {
        /* 首先查找S的插入位置fp，同时记录距S的插入位置最近且
        平衡因子不等于0（等于-1或1）的结点a，a为可能的失衡结点*/
        a = bt;
        fa = NULL;
        p = bt;
        fp = NULL;
        while (p)
        {
            if (p->bf != 0)
            {
                a = p; //记录结点可能失衡结点a
                fa = fp;
            }
            fp = p;         // p的平衡因子为0的时候，（因子为0不代表为叶子，意味着左右平衡）将p赋给fp
            if (k < p->key) //当结点数据k小于p的key，则遍历p的左树
                p = p->lchild;
            else //否则，遍历p的右树
                p = p->rchild;
        }
        if (k < fp->key) // fp为此时被插入的结点
            fp->lchild = S;
        else
            fp->rchild = S;
        // a作为失衡结点
        //此时插入了结点那么相应的因子数也需要增加
        if (k < a->key)
        {
            b = a->lchild;
            a->bf++;
        }
        //在此时的定义中，规定bf正数为左高，负数就是为右高
        else
        {
            b = a->rchild;
            a->bf--;
        }
        //此时b就是a的插入节点，将p节点指向b
        p = b;
        //开始修改节点并且进行旋转，现在已经找到了离插入点最近的失衡节点，开始四种旋转
        while (p != S)
        {
            if (k < p->key)
            {
                p->bf = 1;
                p = p->lchild;
            }
            else
            {
                p->bf = -1;
                p = p->rchild;
            }
            //判断类型进行旋转
            // LL型
            if (a->bf == 2 && b->bf == 1)
            {
                b = a->lchild;
                a->lchild = b->rchild;
                a->bf = 0;
                b->rchild = a;
                b->bf = 0;
                //以下实现*b与原*a的双亲结点连接
                if (!fa)
                    bt = b; // fa为*a的双亲结点地址
                else if (b->key < fa->key)
                    fa->lchild = b;
                else
                    fa->rchild = b;
            }
            // RR型
            else if (a->bf == -2 && b->bf == -1)
            {
                b = a->rchild;
                a->rchild = b->lchild;
                a->bf = 0;
                b->lchild = a;
                b->bf = 0;
                //以下实现*b与原*a的双亲结点连接
                if (!fa)
                    bt = b;
                else if (b->key < fa->key)
                    fa->lchild = b;
                else
                    fa->rchild = b;
            }
            // LR型
            else if (a->bf == 2 && b->bf == -1)
            {
                b = a->lchild;
                c = b->rchild;
                a->lchild = c->rchild;
                b->rchild = c->lchild;
                c->lchild = b;
                c->rchild = a;
                switch (c->bf)
                {
                case 0:
                    a->bf = b->bf = 0;
                    break;
                case 1:
                    a->bf = -1;
                    b->bf = 0;
                    break;
                case -1:
                    a->bf = 0;
                    b->bf = 1;
                    break;
                }
                c->bf = 0;
                //以下实现*c与原*a的双亲结点连接
                if (!fa)
                    bt = c;
                else if (b->key < fa->key)
                    fa->lchild = c;
                else
                    fa->rchild = c;
            }
            // RL型
            else if (a->bf == -2 && b->bf == 1)
            {
                b = a->rchild;
                c = b->lchild;
                a->rchild = c->lchild;
                b->lchild = c->rchild;
                c->lchild = a;
                c->rchild = b;
                switch (c->bf)
                {
                case 0:
                    a->bf = b->bf = 0;
                    break;
                case 1:
                    a->bf = 0;
                    b->bf = -1;
                    break;
                case -1:
                    a->bf = 1;
                    b->bf = 0;
                    break;
                }
                c->bf = 0;
                //以下实现c与原*a的双亲结点连接
                if (!fa)
                    bt = c;
                else if (b->key < fa->key)
                    fa->lchild = c;
                else
                    fa->rchild = c;
            }
        }
    }
}

void CreateAVLT(AVLTree &bst, int a[], int N)
{
    bst = NULL;
    for (int i = 0; i < N; i++)
        InsertAVLTree(bst, a[i], i);
}

//递归先序遍历平衡二叉排序树
void pre_traverse(AVLTree T)
{
    if (T)
    {
        printf("%d ", T->key);
        if (T->lchild)
            pre_traverse(T->lchild);
        if (T->rchild)
            pre_traverse(T->rchild);
    }
}

//递归中序遍历平衡二叉排序树，得到元素从小到大有序排列的序列，以及输出平衡因子
void in_traverse(AVLTree T)
{
    if (T)
    {
        if (T->lchild)
            in_traverse(T->lchild);
        printf("%2d   ", T->key);
        printf("%2d \n", T->bf);
        if (T->rchild)
            in_traverse(T->rchild);
    }
}

int main()
{
    AVLTree T;
    int i = 0, num;
    printf("请输入节点个数:");
    scanf("%d", &num);
    int *arr = (int *)malloc(num * sizeof(int));
    printf("请依次输入这%d个整数（必须互不相等，输入0时停止）:\n", num);
    do
    {
        scanf("%d", arr + i);
        i++;
    } while (*(arr + i - 1) != 0);
    CreateAVLT(T, arr, num);
    printf("先序遍历该平衡二叉排序树的结果:");
    pre_traverse(T);
    printf("\n");
    printf("中序遍历该平衡二叉排序树的结果:\n");
    in_traverse(T);
    system("pause");
    return 0;
}