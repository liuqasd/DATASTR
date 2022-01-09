#include <fstream>
#include <iostream>
#define Elemtype int
using namespace std;

struct Matrix{
    int i;
    int j;
    Matrix *down;
    Matrix *right;
    Elemtype e;
};

Matrix *init(int m, int n);                                 //矩阵初始化
bool insertNode(int x, int y, Elemtype ee, Matrix *head);   //节点插入
Matrix *Transpose(Matrix *head);                            //转置
void printMatrix(Matrix *head);                             //文件输出
void swapXY(int &i, int &j);                                //i，j交换

Matrix *init(int m, int n){
    if (n <= 0 || m <= 0)
        return NULL;
    Matrix *head = new Matrix;
    head->i = m;
    head->j = n;
    Matrix *dhead = new Matrix[m];  //行头结点
    Matrix *rhead = new Matrix[n];  //列头结点
    head->down = dhead;
    head->right = rhead;
    for (int i = 0; i < m; i++)
        dhead[i].right = &dhead[i]; //使行头结点的列指针指向本身
    for (int i = 0; i < n; i++)
        rhead[i].down = &rhead[i];
    return head;
}

bool insertNode(int x, int y, Elemtype ee, Matrix *head){
    if (x >= head->i || x < 0 || y >= head->j || y < 0 || head == NULL || ee == 0)  //输入合法检查
        return false;
    Matrix *node = new Matrix;
    node->i = x;
    node->j = y;
    node->e = ee;
    Matrix *pt;
    Matrix *p;

    pt = head->down + x;
    p = pt->right;
    while (p != head->down + x && x > p->j) //节点插入
    {
        pt = p;
        p = p->right;
    }
    pt->right = node;
    node->right = p; 
    pt = &(head->right)[y];
    p = pt->down;
    while (p != &(head->right)[y] && y > p->i)
    {
        pt = p;
        p = p->down;
    }
    pt->down = node;
    node->down = p; 
    return true;
}

Matrix *Transpose(Matrix *head){
    Matrix *pd;
    Matrix *pt;
    Matrix *pr;
    Matrix *temp;
    int i = 0;
    while (i < head->i)
    {
        pd = &(head->down)[i];
        pt = pd->right;
        temp = pd->right;
        pd->right = pd->down;
        pd->down = temp;    //交换
        pd = pt;
        while (pd != &(head->down)[i])
        {
            pt = pd->right;
            temp = pd->right;
            pd->right = pd->down;
            pd->down = temp;
            swapXY(pd->i, pd->j);
            pd = pt;
        }
        i++;
    }
    pr = head->right;
    for (int j = 0; j <= head->j; j++)
    {
        pr = head->right + j;
        temp = pr->right;
        pr->right = pr->down;
        pr->down = temp;    //交换
    }
    temp = head->right;
    head->right = head->down;
    head->down = temp;      //交换
    swapXY(head->i, head->j);
    return head;
}

void printMatrix(Matrix *head){
    ofstream outputFile;
    outputFile.open("D:\\数据结构实验\\out.txt");
    Matrix *p;
    int i = 0;
    while (i < head->i)
    {
        p = &(head->down)[i];
        p = p->right;
        while (p != &(head->down)[i])
        {
            cout << p->i << " " << p->j << " " << p->e << endl;
            outputFile << p->i << " " << p->j << " " << p->e << endl;
            p = p->right;
        }
        i++;
    }
    cout << endl;
    outputFile.close();
}

void swapXY(int &i, int &j){
    int temp = i;
    i = j;
    j = temp;
}

int main(){
    Matrix *head;
    ifstream inputFile;
    int m, n, t;
    inputFile.open("D:\\数据结构实验\\in.txt");
    inputFile >> m >> n >> t;
    head = init(m, n);
    for (int i = 0; i < t; i++)
    {
        int x, y;
        Elemtype ee;
        inputFile >> x >> y >> ee;
        insertNode(x, y, ee, head);
    }
    inputFile.close();
    cout << "原矩阵为：" << endl;
    printMatrix(head);
    head = Transpose(head);
    cout << "转置后矩阵为：" << endl;
    printMatrix(head);
    system("pause");
    return 0;
}