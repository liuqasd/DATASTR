#include <iostream>
#include <windows.h>

using namespace std;

void preTraversal(int n, char *T);
void midTraversal(int n, char *T);
void posTraversal(int n, char *T);
void visit(char ch);
int N;

void visit(char ch)
{
    cout << ch;
}
void preTraversal(int n, char *T)
{
    if (n > N)
        return;
    visit(T[n]);
    preTraversal(2 * n, T);
    preTraversal(2 * n + 1, T);
    return;
}
void midTraversal(int n, char *T)
{
    if (n > N)
        return;
    midTraversal(2 * n, T);
    visit(T[n]);
    midTraversal(2 * n + 1, T);
    return;
}
void posTraversal(int n, char *T)
{
    if (n > N)
        return;
    posTraversal(2 * n, T);
    posTraversal(2 * n + 1, T);
    visit(T[n]);
    return;
}

int main()
{
    cout << "请输入N:" << endl;
    cin >> N;
    char *T = new char[N + 1];
    cout << "请输入数据：" << endl;
    for (int i = 1; i <= N; i++)
        cin >> T[i];
    cout << endl
         << "前序遍历为：" << endl;
    preTraversal(1, T);
    cout << endl 
         <<"中序遍历为："<< endl;
    midTraversal(1, T);
    cout << endl
         << "后序遍历为：" << endl;
    posTraversal(1, T);
    cout << endl;
    system("pause");
    return 0;
}