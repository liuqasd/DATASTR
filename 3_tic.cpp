#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

typedef struct
{
	char ch[10];
} string;
typedef struct
{
	string *s;
	int max_size;
	int f;
	int r;
} SqQueue;

int main()
{
	void init(SqQueue & q, int n);
	int empty(SqQueue & q);
	int full(SqQueue & q);
	void enQueue(SqQueue & q);
	void dlQueue(SqQueue & q);
	int n, cord;
	SqQueue q;
	printf("请输入队列容量：");
	scanf("%d", &n);
	init(q, n);
	printf("/**************主菜单*************/\n");
	printf("1. 排队——输入新到达的买票人姓名，加入买票队列中\n");
	printf("2. 售票——排队队列中最前面的人购票成功，显示信息并将其从队列中删除\n");
	printf("3. 查看队列——从队首到队尾依次列出所有正在排队买票人的姓名\n");
	printf("4. 结束——退出系统\n");
	printf("/*********************************/\n");
	printf("请选择菜单<1,2,3,4>：");
	scanf("%d", &cord);
	do
	{
		switch (cord)
		{
		case 1:
			enQueue(q);
			break;
			continue;
		case 2:
			dlQueue(q);
			break;
		case 3:
			while (!empty(q))
			{
				dlQueue(q);
			}
			break;
		case 4:
			exit(-1);
		default:
			printf("ERROR!输入错误!系统将退出\n");
			exit(-1);
			break;
		}
		printf("请选择菜单<1,2,3,4>：");
		scanf("%d", &cord);
	} while (cord >= 1 && cord <= 4);
	system("pause");
	return 0;
}

void init(SqQueue &q, int n)
{
	q.f = q.r = 0;
	q.max_size = n + 1;
	if (!(q.s = (string *)malloc(sizeof(string) * (n + 1))))
		exit(-1);
}

int empty(SqQueue &q)
{
	return q.f == q.r;
}

int full(SqQueue &q)
{
	return (q.r + 1) % q.max_size == q.f;
}

void enQueue(SqQueue &q)
{
	string e;
	int full(SqQueue & q);
	if (full(q))
		printf("队满，请等待！\n");
	else
	{
		printf("请输入买票人姓名:");
		scanf("%s", &e.ch);
		q.r = (q.r + 1) % q.max_size;
		q.s[q.r] = e;
		printf("入队成功！\n");
	}
}

void dlQueue(SqQueue &q)
{
	string e;
	int empty(SqQueue & q);
	if (empty(q))
		printf("队空，无人排队！\n");
	else
	{
		q.f = (q.f + 1) % q.max_size;
		e = q.s[q.f];
		printf("出队人姓名为：%s\n", e.ch);
	}
}
