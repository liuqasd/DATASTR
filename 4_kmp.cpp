#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#define SIZE 1000

int nextval[SIZE]={'\0'};//定义nextval数组并初始化

void get_nextval(char *t,int nextval[]){
    int j=1;
    int k=-1;
    nextval[0]=k;
    while(t[j])
        if((k==-1)||(t[j-1]==t[k]))
            if(t[++k]==t[j])
                nextval[j++]=nextval[k];
            else
                nextval[j++]=k;
        else
            k=nextval[k];
}

int index_kmp(char s[], char t1[], int a[], int nextval[]){
    int c = 0; //成功匹配次数
    int i = 0, j = 0;
    while (1)
    {
        while (s[i] && (j == -1 || t1[j]))    //当主串s【i】不为空且子串t【j】不为空
            if ((j == -1) || (s[i] == t1[j])) //如果主串的第一个元素和子串的第一个匹配上之后，主串和子串下标均向后移一位
            {
                i++;//主串循环到下一个
                j++;//子串循环到下一个
            }
            else
                j=nextval[j];
        if(!t1[j])// 如果子串完成一次成功的匹配
        {
            a[c] = i - (int)strlen(t1);
            c++;//将记录成功匹配的次数的值加一，此时主串下标已经向前移动一位，所以不需要再进行i++
            i = i - j + 1; //每一次主串的下标i回溯到初始位置的下一个，避免匹配漏掉
            j = 0; //将子串下标回溯到初始位置
        }
        if(!s[i])//如果主串到达末尾，遍历完成，退出循环
            break;
    }
    return c;//返回成功匹配的次数
}

void replace(char s[], char t1[], char t2[], int a[], int index, char newString[]){
    int order = 0; //表示newString存储字符的位置
    int begin = 0;
    int i, j, k;
    for (i = 0; i < index; i++)
    {
        //先将替换位置之前的字符完整的复制到新字符串数组中
        for (j = begin; j < a[i]; j++)
        {
            newString[order] = s[j];
            order++;
        }
        //替换字符，用新字符代替
        for (k = 0; k < (int)strlen(t2); k++)
        {
            newString[order] = t2[k];
            order++;
        }
        //代替完成后，计算出原字符串中隔过该字符串的下一个起始位置
        begin = a[i] + (int)strlen(t1);
    }
    //要替换位置全部替换完成后，检测是否还有后续字符，若有直接复制
    while (begin < (int)strlen(s))
    {
        newString[order] = s[begin];
        order++;
        begin++;
    }
}

int main(){
    int index;//成功匹配的次数的值
    int a[SIZE];
    char s[SIZE] = {'\0'}, t1[SIZE] = {'\0'}, t2[SIZE] = {'\0'}, newString[SIZE] = {'\0'}; //定义三个字符串数组，来保存主串和子串
    printf("\n请输入主串，t1字串以及t2字串，主串中的t1字串将被全部替换为t2字串\n");
    scanf("%s", s);          //输入主串
    getchar();               //用于承接缓冲区冲的换行符
    scanf("%s", t1);         //输入t1串
    getchar();               //用于承接缓冲区冲的换行符
    scanf("%s", t2);         //输入t2串
    getchar();               //用于承接缓冲区冲的换行符
    get_nextval(t1, nextval);//得到nextval数组的值
    index = index_kmp(s, t1, a,nextval); //将成功匹配次数的值存储到index中
    if (index == 0)
        printf("未检测到原字符串S中有该字符串！");
    else
    {
        printf("\n成功匹配次数为： %d  次，起始位置依次是：", index);
        int i;
        for (i = 0; i < index; i++)
        {
            printf("%d ", a[i]);
        }
        printf("\n");
        replace(s, t1, t2, a, index, newString);
        printf("新生成的字符串为: %s\n", newString);
    }
    system("pause");
    return 0;
}