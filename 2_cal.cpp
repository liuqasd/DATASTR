#include <iostream>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXSIZE 100
#define N 100
using namespace std;
//定义顺序栈
typedef struct oprd
{
    int *base;     //用于栈存储的基地址
    int *top;      //指向该基地址的栈顶指针
    int stackSize; //栈的大小
} OPRD;
//定义顺序栈
typedef struct optr
{
    char *base;    //用于栈存储的基地址
    char *top;     //指向该基地址的栈顶指针
    int stackSize; //栈的大小
} OPTR;
//初始化
int InitStack_Int(OPRD &S)
{
    S.base = (int *)malloc(MAXSIZE * sizeof(int)); //给基地址分配一个内存空间
    S.top = S.base;                                //将栈顶指针指向这个基地址
    S.stackSize = MAXSIZE;                         //设置栈的大小
    return 0;
}
int InitStack_Char(OPTR &S)
{
    S.base = (char *)malloc(MAXSIZE * sizeof(char)); //给基地址分配一个内存空间
    S.top = S.base;                                  //将栈顶指针指向这个基地址
    S.stackSize = MAXSIZE;                           //设置栈的大小
    return 0;
}
//进栈
int Push_Int(OPRD &S, int e)
{
    if (S.top - S.base == S.stackSize)
        return -1;
    *S.top = e; //将输入的值压入栈中
    S.top++;    //指针上移一个单位
//    printf("操作数%d进num栈\n", e);
    return 0;
}
int Push_Char(OPTR &S, char e)
{
    if (S.top - S.base == S.stackSize)
        return -1;
    *S.top = e; //将输入的值压入栈中
    S.top++;    //指针上移一个单位
//    printf("操作符%c进sign栈\n", e);
    return 0;
}
//出栈
int Pop_Int(OPRD &S, int &e)
{
    if (S.base == S.top)
        return -1;
    S.top--;    //指针下移一个
    e = *S.top; //将当前指针所指的值赋值给e
    return 0;
}
int Pop_Char(OPTR &S, char &e)
{
    if (S.base == S.top)
        return -1;

    S.top--;    //指针下移一个
    e = *S.top; //将当前指针所指的值赋值给e
    return 0;
}
//获取栈顶元素
int GetTop_Int(OPRD S)
{
    return *(S.top - 1);
}
char GetTop_Char(OPTR S)
{
    return *(S.top - 1);
}
//判断是否是运算符
int isOper(char c)
{
    if (c == '#' || c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')')
    {
        return 1; //是操作符
    }
    else
    {
        return 0; //不是操作符
    }
}
// c1:栈顶操作
// c2:扫描操作符
char getStackTopPriority(char StackTop, char c)
{
    // printf("Priority:%c::%c\n",StackTop,c);
    if (StackTop == '(' && c == ')')
        return '=';
    else if (((StackTop == '+' || StackTop == '-' || StackTop == '*' || StackTop == '/' || StackTop == ')') && (c == '+' || c == '-' || c == ')' || c == '=')) || ((StackTop == '*' || StackTop == '/' || StackTop == ')') && (c == '*' || c == '/')))
        return '>';
    else if ((StackTop == '#' || (StackTop == '(' || StackTop == '=') && c != ')' && c != '=') || ((StackTop == '+' || StackTop == '-') && (c == '*' || c == '/')) || StackTop == '(' || c == '(')
        return '<';
    else
        return '>';
}
int operate(int a, char oper, int b)
{
    switch (oper)
    {
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '*':
        return a * b;
    case '/':
        return a / b;
    }
}
int main()
{
    char arr[N];
    printf("请输入表达式并以#结束：\n");
    scanf("%s", arr);
    OPRD num; //用来存储操作数的栈 int 类型
    OPTR sign;
    //初始化两个栈
    InitStack_Int(num);
    InitStack_Char(sign);
    //操作符栈 进栈一个 # 号作为结束标志
    Push_Char(sign, '#');
    int i = 0; //用于循环遍历 中缀表达式 arr 数组
    while (arr[i] != '#' || GetTop_Char(sign) != '#')
    {

        if (!isOper(arr[i]))
        { //如果不是操作符
            int e = arr[i] - '0';
            Push_Int(num, e); //进操作数 num 栈
            i++;
        }
        else
        { //是操作符等待进入 sign 栈
            char e = arr[i];
            //比较操作符 sign栈  当前栈顶操作符的和当前扫描到的操作符优先级大小
            switch (getStackTopPriority(GetTop_Char(sign), e))
            {

            case '<':
            { //栈顶操作符优先级小-->
                Push_Char(sign, e);
                i++;
                break;
            }

            case '=':
            {
                char x;
                Pop_Char(sign, x);
                i++;
                break;
            }

            case '>':
            {
                int a, b;
                char oper;
                Pop_Int(num, b);
                Pop_Int(num, a);
                Pop_Char(sign, oper);
                int e = operate(a, oper, b);
                Push_Int(num, e);

                break;
            }
            }
        }
    }

    printf("运算结果为：%d\n", GetTop_Int(num));
    system("pause");
    return 0;
}
