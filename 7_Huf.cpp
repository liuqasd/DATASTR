#include <fstream>
#include <iostream>
#include <string.h>
#include <string>
using namespace std;

//霍夫曼树的存储结构
typedef struct
{
    char data;                  //存储数据
    int weight;                 //结点的权重
    string num;                 //存放哈夫曼码
    int parent, lchild, rchild; //结点的双亲、左孩子、右孩子的下标
} HTNode, *HuffmanTree;

//两个最小结点
typedef struct
{
    int s1;
    int s2;
} MIN;

//选择结点权值最小的两个结点
MIN Select(HuffmanTree HT, int n)
{
    int min, secmin, s1, s2;
    min = 10000;
    secmin = 10000;
    MIN code;
    s1 = 0;
    s2 = 0;
    for (int i = 0; i < n; i++)
    {
        if (HT[i].parent == 0 && (HT[i].weight < min))
        {
            min = HT[i].weight;
            s1 = i;
        }
    }
    for (int i = 0; i < n; i++)
    {
        if (HT[i].parent == 0 && (HT[i].weight < secmin) && (i != s1))
        {
            secmin = HT[i].weight;
            s2 = i;
        }
    }
    code.s1 = s1;
    code.s2 = s2;
    return code;
}

//霍夫曼码存储
void putlorinnum(HuffmanTree &hft, int num)
{
    for (int i = num - 1; i >= 0; i--)
    {
        if (hft[hft[i].parent].parent)
            hft[i].num = hft[hft[i].parent].num + hft[i].num;
    }
}

//创造霍夫曼树
void CreateHuffmanTree(HuffmanTree &HT, int num, char p[])
{
    int m;
    m = 2 * num - 1;
    HT = new HTNode[m];         //分配空间
    for (int i = 0; i < m; i++) //初始化
    {
        HT[i].parent = 0;
        HT[i].lchild = 0;
        HT[i].rchild = 0;
    }
    cout << "输入数据的权值：" << endl;
    for (int i = 0; i < num; i++)
    {
        HT[i].data = p[i];
        cout << HT[i].data << ":";
        cin >> HT[i].weight;
    }

    for (int i = num; i < m; i++) //构建哈夫曼树
    {
        MIN min;
        min = Select(HT, i); //选择二叉树
        HT[min.s1].parent = i;
        HT[min.s2].parent = i;
        HT[i].lchild = min.s1;
        HT[min.s1].num = "0";
        HT[i].rchild = min.s2;
        HT[min.s2].num = "1";
        HT[i].weight = HT[min.s1].weight + HT[min.s2].weight;
        HT[i].data = -1;
    }
    putlorinnum(HT, m);
    fstream infile;
    infile.open("D:\\huf.txt");
    for (int i = 0; i < m; i++) //输出每个字符的霍夫曼码
    {
        if (HT[i].data != -1)
        {
            infile << HT[i].data << ":" << HT[i].num << endl;
            cout << HT[i].data << " 权重为" << HT[i].weight << "  ，霍夫曼码为：" << HT[i].num << endl;
            cout << endl;
        }
    }
}

//编译
void changchartohft(HuffmanTree hft, string s, int m)
{
    string estring;
    for (int i = 0; i <= s.size(); i++)
    {
        for (int x = 0; x < m; x++)
        {
            if (hft[x].data == s[i]) //查找霍夫曼树中相应的字符
            {
                estring = estring + hft[x].num; 
                x = m;
            }
        }
    }
    cout << estring << endl;
    return;
}

//解译
void changhfttochar(HuffmanTree hft, string s, int m)
{
    string estring;
    int pos = 0, first = 0;
    for (int x = 0; x < s.size(); x++)
    {
        pos++;
        for (int i = 0; i < m; i++)
        {
            if (hft[i].num == s.substr(first, pos)) //将截取的字符串和霍夫曼码对比
            {
                cout << hft[i].data;
                first = pos + first;
                pos = 0;
            }
        }
    }
    cout << endl;
}
int findelementNum(char code[], char p[]) //找出字符串中的不同字符
{
    if (strlen(code) == 0)
        return 0;
    int num = 1; //记录不同的字符个数
    p[0] = code[0];

    for (int i = 1; i < strlen(code); i++)
    {
        for (int j = 0; j < num; j++)
        {
            if (code[i] == p[j]) // code[i]已经出现过，则其权值加1，并退出内循环
                break;
            if (j == num - 1) // code[i]未出现过，则录入p中，其权值变为1
            {
                p[num] = code[i];
                num++;
                break;
            }
        }
    }
    return num;
}

int main()
{
    int num; //结点的个数
    char maxa[100];
    char p[100];
    string s1, s2;
    cout << "输入字符串：" << endl;
    cin >> maxa;
    num = findelementNum(maxa, p);
    //创造霍夫曼树
    HuffmanTree HT;
    CreateHuffmanTree(HT, num, p);

    while (1) //设置循环，可以选择性进行
    {
        int q;
        cout << "---------------------" << endl;
        cout << "编译：0" << endl;
        cout << "解码：1" << endl;
        cout << "输入要进行的操作：" << endl;
        cin >> q;

        if (q == 0)
        {
            cout << "输入要编译的字符串" << endl;
            cin >> s1;
            changchartohft(HT, s1, num);
        }
        else if (q == 1)
        {
            cout << "输入要解码的数字串" << endl;
            cin >> s2;
            changhfttochar(HT, s2, num);
        }
        else
            break;
    }
    system("pause");
    return 0;
}