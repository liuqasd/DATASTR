#include <cstdio>
#include <cstring>
#include <iostream>
#include <stack>
#include <string>

using namespace std;

/*创建图的邻接表*/
//如果是无向图，那么每条边由两个结点组成，分别代表边的两个端点；
//如果是有向图，那么每条边是一个结点对，分别代表边的始点和终点。
typedef struct ArcNode
{
    int adv;                 //指向顶点的位置
    struct ArcNode *nextArc; //指向下一条边
    int w;                   //表示权值
} ArcNode;

typedef struct VNode
{
    ArcNode *first; //指向该顶点第一条弧的指针
    string data;    //顶点数据，例如名字
} AdVlist;

typedef struct ALGraph
{
    AdVlist vts[500]; //顶点向量
    int v, e;         //顶点数，边数
} ALGraph;

/*查找输入的x顶点位置*/
int Find(ALGraph &g, string x)
{
    for (int i = 0; i < g.v; i++)
    {
        if (x == g.vts[i].data) //如果x为第i个结点，返回i
            return i;
    }
    return -1;
}

int ve[500];  //全局变量，表示事件最早发生的时间
stack<int> t; // t为返回拓扑序列的栈

/*创建图*/
void Creat(ALGraph &g)
{
    int weight, edge = 0;
    string v1, v2;
    cout << "输入图的顶点数:" << endl;
    cin >> g.v;
    cout << "输入图中结点信息:" << endl;
    //输入顶点的信息，并且使指边指向NULL
    for (int i = 0; i < g.v; i++)
    {
        cin >> g.vts[i].data;
        g.vts[i].first = NULL;
    }
    cout << "输入图中两个顶点与其相应的权值，其中以‘0 0 0’结束:" << endl;
    while (1)
    {
        cin >> v1 >> v2 >> weight;
        if (v1 == "0" && v2 == "0" && weight == 0)
            break;
        edge++;
        int j, k;
        j = Find(g, v1);           //起点位置
        k = Find(g, v2);           //终点位置
        ArcNode *p1 = new ArcNode; //图的邻接表
        p1->adv = k;               //使边p的顶点指向第k个顶点，意思就是第k个顶点为指向量，例如边<i,j>，则j就是这里的k
        p1->w = weight;            //使边p的权值赋值
        p1->nextArc = NULL;
        p1->nextArc = g.vts[j].first;
        g.vts[j].first = p1;
    }
    g.e = edge;
}

/*求各顶点的入度，保存在indegree数组中*/
void FindID(ALGraph g, int indegree[500]) //参数为生成的图和indegree数组
{
    int i;
    ArcNode *p;
    for (i = 0; i < g.v; i++) //初始化
        indegree[i] = 0;
    for (i = 0; i < g.v; i++) //图的顶点数g.v
    {
        p = g.vts[i].first; // p是第i个顶点指向的第一条边的指针
        while (p != NULL)   //遍历第i个顶点所有的边，直到指向NULL
        {
            indegree[p->adv]++; //边的顶点，就是此时的顶点入度+1
            p = p->nextArc;     //遍历
        }
    }
}

/*拓扑排序*/
bool TopOrder(ALGraph g)
{
    stack<int> s;       // s为存放入度为0的顶点的栈
    int count, i, j, k; // count做检验工作，因为入度为0的时候可能会有顶点没有进入，这样做更加保险
    ArcNode *p;
    int indegree[500]; //各顶点的入度
    FindID(g, indegree);
    for (i = 0; i < g.v; i++)
    {
        if (indegree[i] == 0)
            s.push(i); //使没有入度的点入栈，就是说在拓扑排序中，先寻找入度为0的顶点
    }
    count = 0;
    for (i = 0; i < g.v; i++)
        ve[i] = 0; //初始化最早发生的时间
    while (!s.empty())
    {
        /*如果栈s非空，那么先出栈并赋值给j，然后使j进入栈t,这样栈t就是拓扑序列，因为s里面的肯定是入度为0的了*/
        j = s.top();
        s.pop();
        t.push(j);
        count++;
        p = g.vts[j].first; //边p指向顶点j的第一条边
        while (p != NULL)
        {
            k = p->adv;
            /*顶点k(就是这条边的指向顶点)度数是否为0，如果不是那么减为0，然后使其入栈*/
            if (!(--indegree[k]))
                s.push(k);
            // j的最早发生事件+权值是否大于这个顶点的ve，注意一开始ve(0)=0
            if (ve[j] + p->w > ve[k])
                ve[k] = ve[j] + p->w;
            p = p->nextArc;
        }
    }
    if (count < g.v)
        return false; //有回路
    else
        return true;
}

/*关键路径算法*/
bool CriticalPath(ALGraph g)
{
    ArcNode *p;
    int i, j, k;
    int dut; //权值
    int vl[500];     // vl为事件，注意不是活动，发生的最晚时间
    if (!TopOrder(g))
        return false;
    for (i = 0; i < g.v; i++)
        vl[i] = ve[g.v - 1]; //初始化
    /*按逆拓扑顺序求各顶点的vl,也即事件发生的最晚时间*/
    while (!t.empty())
    {
        j = t.top();
        t.pop();
        p = g.vts[j].first;
        while (p != NULL)
        {
            k = p->adv;
            dut = p->w;
            if (vl[k] - dut < vl[j])
                vl[j] = vl[k] - dut;
            p = p->nextArc;
        }
    }
    for (i = 0; i < g.v;i++)
        cout << "ve[" << i << "]=" << ve[i] << " "
             << "vl[" << i << "]=" << vl[i] << endl;
    return true;
}

int main()
{
    ALGraph g;
    Creat(g);
    CriticalPath(g);
    system("pause");
    return 0;
}
