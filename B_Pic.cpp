#include <stdio.h>
#include <malloc.h>
#include <math.h>
#include <windows.h>
#define MAXROW 100
#define MAXCOL 100

using namespace std;
typedef char ElemType;

//二叉树的二叉链表存储结构，1个数据域，2个指针域
typedef struct BiTNode
{
    ElemType data;
    BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

//按先序遍历的方式建立二叉树
void CreateBiTree(BiTree *T) //参数为树的头节点
{
    ElemType ch;
    scanf("%c", &ch);
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

//返回二叉树深度
int BiTreeDepth(BiTree T)
{
    int i, j;
    if (!T)
        return 0;
    if (T->lchild)
        i = BiTreeDepth(T->lchild); // 左子树深度
    else
        i = 0;
    if (T->rchild)
        j = BiTreeDepth(T->rchild); // 右子树深度
    else
        j = 0;
    return i > j ? i + 1 : j + 1;
}

char dis_buf[MAXROW][MAXCOL]; //初始化 画布

//初始化画布
void start()
{
    int i, j;
    for (i = 0; i < MAXROW; i++)
    {
        for (j = 0; j < MAXCOL; j++)
            dis_buf[i][j] = ' ';
    }
}

//打印
void print(BiTree T, int x, int y, int layers)  //layers为树深度
{
    int left, right; //左右孩子的x坐标
    layers--;
    int j = pow(2, layers); //孩子坐标偏移量，j为结点数+1
    if (T != NULL)
    {
        left = x - pow(2, layers);  //pow函数功能：计算x的y次幂，x为根结点横坐标
        right = x + pow(2, layers);
        dis_buf[y][x] = T->data;
        if (T->lchild)
        {
            for (int i = j; i > 0; i--)
                dis_buf[y + 1][x - i] = '_';
            dis_buf[y + 1][x] = '|';
            dis_buf[y + 2][x - j] = '|';
        }
        if (T->rchild)
        {
            for (int i = j; i > 0; i--)
                dis_buf[y + 1][x + i] = '_';
            dis_buf[y + 1][x] = '|';
            dis_buf[y + 2][x + j] = '|';
        }
        y += 3;

        print(T->lchild, left, y, layers);  //左子树
        print(T->rchild, right, y, layers); //右子树
    }
}

int main()
{
    printf("请输入：\n");
    BiTree T;
    CreateBiTree(&T);
//    printf("深度: %d\n", BiTreeDepth(T));
    int eff = 3 * (BiTreeDepth(T) - 1) + 1; //计算打印需要的行数,两竖一横所以*3
    int x = 0, y = 0;                       //根节点的xy坐标
    x = pow(2, BiTreeDepth(T));     //结点数+1
    printf("输出为：\n");
    start();                        //初始化画布，全部为' '
    print(T, x, y, BiTreeDepth(T)); //生成
    for (int i = 0; i < eff; ++i)   //打印画布
    {
        for (int j = 0; j < MAXCOL; ++j)
        {
            printf("%c", dis_buf[i][j]);
        }
        printf("\n");
    }
    system("pause");
    return 0;
}
