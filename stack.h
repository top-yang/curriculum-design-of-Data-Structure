#include<string.h>
#include<ctype.h>
#include<malloc.h> // malloc()等
#include<limits.h> // INT_MAX等
#include<stdio.h> // EOF(=^Z或F6),NULL
#include<stdlib.h> // atoi()
#include<io.h> // eof()
#include<process.h> // exit()
//#include<iostream.h> // cout,cin
#define FALSE -1
#define ERROR -1
#define TRUE 1
#define OK 1
typedef struct LNode{
	int x,y,z,sign;//结点坐标信息
	struct LNode *next;//下一个结点
}Lnode,*Node;
typedef struct LGroup{
        int Xmin,Xmax,Ymin,Ymax,Zmin,Zmax,sign,count,size;//size指团簇数目
        struct LNode *head;//指向本团簇的头指针
        struct LGroup *next;//指向下一个团簇
}Lgroup,*LinkList;
//
typedef int Status;
typedef struct Stack_LNode{
	LinkList  data;
	struct Stack_LNode *next;
}Stack_Lnode,*Stack_LinkList;
#define DestroyList ClearList
void InitList(Stack_LinkList *L)
{
	*L=NULL;
 }
void ClearList(Stack_LinkList *L)
{
	Stack_LinkList p;
	while(*L)
	{
		p=*L;
		*L=(*L)->next;
		free(p);
	}
}
Status ListEmpty(Stack_LinkList L)
{
	if(L)
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}
int ListLength(Stack_LinkList L)
{
	int i=0;
	Stack_LinkList p=L;
	while(p)
	{
		p=p->next;
		i++;
	}
	return i;
}
Status GetElem(Stack_LinkList L,int i,LinkList *e)
{
	int j=1;
	Stack_LinkList p=L;
	if(i<1)
	{
		return ERROR;
	}
	while(j<i&&p)
	{
		j++;
		p=p->next;
	}
	if(j==i)
	{
		(*e)=p->data;
		return OK;
	}
	else
	{
		return ERROR;
	}
 }
 Status ListInsert(Stack_LinkList *L, int i, LinkList e)
 {
 	int j=1;
 	Stack_LinkList p=(*L);
	Stack_LinkList s;
 	if(i<1)
 	{
 		return ERROR;
	}
	s=(Stack_LinkList)malloc(sizeof(Stack_Lnode));
	s->data=e;
	if(i==1)
	{
		s->next=*L;
		(*L)=s;
	}
	else
	{
		while(p&&j<i-1)
		{
			p=p->next;
			j++;
		}
		if(!p)
		{
			return ERROR;
		}
		s->next=p->next;
		p->next=s;
	}
	return OK;
 }
 Status ListDelete(Stack_LinkList *L,int i,LinkList *e)
 {
 	int j=0;
 	Stack_LinkList p=(*L),q;
 	if(i==1)
 	{
 		(*L)=p->next;
 		(*e)=p->data;
 		free(p);
	 }
	 else
	 {
	 	while(p->next&&j<i-1)
	 	{
	 		p=p->next;
	 		j++;
		 }
		 if(!p->next||j>i-1)
		 {
		 	return ERROR;
		 }
		 q=p->next;
		 p->next=q->next;
		 (*e)=q->data;
		 free(q);
	 }
	 return OK;
 }
typedef Stack_LinkList LinkStack;
#define InitStack InitList
#define DestroyStack DestroyList
#define ClearStack ClearList
#define StackEmpty ListEmpty
#define StackLength ListLength
Status GetTop(LinkStack S,LinkList *e)
{
	return GetElem(S,1,e);
}
Status push(LinkStack *S,LinkList e)
{
	return ListInsert(S,1,e);
}
Status pop(LinkStack *S,LinkList *e)
{
	return ListDelete(S,1,e);
}
