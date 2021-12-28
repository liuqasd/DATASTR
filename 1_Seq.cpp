//顺序存储
#include <stdio.h>
#include <windows.h>

using namespace std;

#define LIST_INIT_SIZE 100 //线性表存储空间的初始分配量
#define LISTINCREMENT 10   //线性表存储结构的分配增量
#define OVERFLOW -1
typedef int ElemType;
typedef int Status;
typedef struct
{
	ElemType *elem; //存储空间基址
	int length;		//当前长度
	int listsize;	//当前分配的存储容量（以sizeof(ElemType)为单位)
} SqList;

Status InitList_Sq(SqList &L)
{ //构造一个空的线性表L
	L.elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
	if (!L.elem)
		exit(OVERFLOW);			 //存储分配失败
	L.length = 0;				 //空表长度为0
	L.listsize = LIST_INIT_SIZE; //初始存储容量
	return 0;
} //InitList_Sq函数体

void CreatList(SqList &L, int x)
{
	int y, Li;
	for (y = 0; y < x; y++)
	{
		scanf("%d", &Li);
		L.elem[y] = Li;
		L.length++;
	}
}

void PrintList(SqList &L)
{
	int m;
	for (m = 0; m < L.length; m++)
	{
		if (m != L.length - 1)
			printf("%d  ", L.elem[m]);
		else
			printf("%d\n", L.elem[m]);
	}
}

void MergeList_Sq(SqList La, SqList Lb, SqList &Lc)
{
	int *pa, *pb, *pc, *pa_last, *pb_last;
	pa = La.elem;
	pb = Lb.elem;
	Lc.listsize = Lc.length = La.length + Lb.length;
	pc = Lc.elem = (ElemType *)malloc(Lc.listsize * sizeof(ElemType));
	if (!Lc.elem)
		exit(OVERFLOW); //存储分配失败
	pa_last = La.elem + La.length - 1;
	pb_last = Lb.elem + Lb.length - 1;
	while (pa <= pa_last && pb <= pb_last)
	{ //归并
		if (*pa <= *pb)
			*pc++ = *pa++;
		else
			*pc++ = *pb++;
	}
	while (pa <= pa_last) //插入La的剩余元素
		*pc++ = *pa++;
	while (pb <= pb_last) //插入Lb的剩余元素
		*pc++ = *pb++;
} //MergeList_Sq函数体

int main()
{
	int i, j;
	SqList La, Lb, Lc;
	InitList_Sq(La);
	InitList_Sq(Lb);
	InitList_Sq(Lc);
	printf("请输入线性表L1待输入元素的个数：");
	scanf("%d", &i);
	printf("请输入线性表L1的元素：");
	CreatList(La, i);
	printf("请输入线性表L2待输入元素的个数：");
	scanf("%d", &j);
	printf("请输入线性表L2的元素：");
	CreatList(Lb, j);
	printf("两个线性表分别为：\n");
	PrintList(La);
	PrintList(Lb);
	/***归并***/
	MergeList_Sq(La, Lb, Lc);
	printf("归并后的元素序列：");
	PrintList(Lc);
	system("pause");
	return 0;
}
