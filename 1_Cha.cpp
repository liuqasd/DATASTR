//链式存储
#include <stdio.h>
#include <windows.h>

using namespace std;

#define OVERFLOW -1
#define OK 1
typedef int ElemType;
typedef int Status;
typedef struct LNode{
	ElemType data;           //该节点数据
	struct LNode *next;	    //指向下一个节点的指针
}LNode, *LinkList;         //结点类型名称与该链表的名称

//初始化链表
Status InitLinkList(LinkList *L)
{
    *L = (LinkList)malloc(sizeof(LNode));
    if (!*L)
        exit(OVERFLOW);
    (*L)->next = NULL;
    return OK;
}

//尾插法建立单链表
Status CreateLinkList_Tail(LinkList L)
{
    int n = 0;
    LNode *q = L;
    printf("请输入链表元素的个数:");
    scanf("%d", &n);
    printf("请输入%d个元素的值:", n);
    for (int i = 0; i < n; i++){
        LNode *p = (LNode *)malloc(sizeof(LNode));
        if (!p)
            exit(OVERFLOW);
        scanf("%d", &p->data);
        p->next = NULL;
        q->next = p;
        q = p;
    }
    return OK;
}

Status PrintList(LinkList &L){
    LinkList p = L->next;
	while (p){
		printf("%d  ", p->data);
		p = p->next;
	}
    return OK;
}

//归并单链表
void Mergelist_L(LinkList &La, LinkList &Lb, LinkList &Lc){
	LinkList pa, pb, pc;
	pa = La->next;
	pb = Lb->next;
	Lc = pc = La;	          //用La的头结点作为Lc的头结点
	while (pa && pb){
		if (pa->data <= pb->data){
			pc->next = pa;
			pc = pa;
			pa = pa->next;
		}
		else{
			pc->next = pb;
			pc = pb;
			pb = pb->next;
		}
	}
	pc->next = pa ? pa : pb;  //插入剩余段
	free(Lb);				  //释放Lb的头结点
}

int main()
{
    LinkList La = NULL;
    LinkList Lb = NULL;
    LinkList Lc = NULL;
    InitLinkList(&La);
    InitLinkList(&Lb);
    InitLinkList(&Lc);
    CreateLinkList_Tail(La);
    CreateLinkList_Tail(Lb);
    printf("表La元素输出\n");
	PrintList(La);
	printf("\n");
	printf("表Lb元素输出\n");
	PrintList(Lb);
	printf("\n");
	Mergelist_L(La, Lb, Lc);
	printf("归并后的链表元素输出\n");
	PrintList(Lc);
    printf("\n");
    system("pause");
	return 0;
}
