#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "stack.h"
#define SElemType LinkList*
#define l 100
#define noview 3000
#define view 3001
int counttime=0;
typedef int* cubez;
typedef cubez* cubey;
typedef cubey* cubex;
cubex initcube(int i,int j,int k)//��ʼ����ά����
{
	int x,y,z;
	cubex Cube;
	Cube=(cubex)malloc(i*sizeof(cubey));
	for(x=0;x<i;x++)
	{
		Cube[x]=(cubey)malloc(j*sizeof(cubez));
		for(y=0;y<j;y++)
		{
			Cube[x][y]=(cubez)malloc(k*sizeof(int));
			for(z=0;z<k;z++)
			{
				Cube[x][y][z]=0;//0��ʾû�е�
			}
		}
	}
	return Cube;
}
void initcube_1(cubex cube)
{
	int x,y,z,count;
	count=0;
	for(x=0;x<l;x++)
		for(y=0;y<l;y++)
			for(z=0;z<l;z++)
				if(cube[x][y][z]>0)
					cube[x][y][z]=noview;
					count++;
}
void initcube_2(cubex cube)
{
	int x,y,z,count;
	count=0;
	for(x=0;x<l;x++)	
		for(y=0;y<l;y++)	
			for(z=0;z<l;z++)		
				if(cube[x][y][z]!=0)		
					cube[x][y][z]=0;
					count++;
}
void ReadFile(cubex Cube,char* filename)//���ļ������ļ���������
{
  int i,x,y,z,c,count;
  count=0;
  FILE *fp;
  if ((fp=fopen(filename,"r"))==NULL)
	{
	printf("Read File failed! ");
	return;
	}
  for(i=0;fscanf(fp,"%d      %d      %d",&x,&y,&z)!=EOF;i++)
  {
     Cube[x][y][z]=noview;
     count++;
  }
  printf("readfile succes!,count:%d\n",count);
  fclose(fp);
}
void View(cubex Cube,int x,int y,int z,LinkList *p)
{
	Cube[x][y][z]=view;
	if(z+1<=l-1)
	{
		if(Cube[x][y][z+1]==noview)
		{
			Node q1=(Node)malloc(sizeof(Lnode));
			q1->x=x;q1->y=y;q1->z=z+1;q1->sign=(*p)->sign;
			q1->next=(*p)->head;(*p)->head=q1;
			View(Cube,x,y,z+1,p);	
		}
	}
	if(z-1>=0)
	{
		if(Cube[x][y][z-1]==noview)
		{
			Node q2;q2=(Node)malloc(sizeof(Lnode));
			q2->x=x;q2->y=y;q2->z=z-1;q2->sign=(*p)->sign;
			q2->next=(*p)->head;(*p)->head=q2;
			View(Cube,x,y,z-1,p);
		}
	}
	if(x-1>=0)
	{
		if(Cube[x-1][y][z]==noview)
		{
			Node q3;q3=(Node)malloc(sizeof(Lnode));
			q3->x=x-1;q3->y=y;q3->z=z;q3->sign=(*p)->sign;
			q3->next=(*p)->head;(*p)->head=q3;
			View(Cube,x-1,y,z,p);
		}
	}
	if(x+1<=l-1)
	{
		if(Cube[x+1][y][z]==noview)
		{
			Node q4;q4=(Node)malloc(sizeof(Lnode));
			q4->x=x+1;q4->y=y;q4->z=z;q4->sign=(*p)->sign;q4->next=(*p)->head;
			(*p)->head=q4;View(Cube,x+1,y,z,p);
		}
	}
	if(y+1<=l-1)
	{
		if(Cube[x][y+1][z]==noview)
		{
			Node q5;q5=(Node)malloc(sizeof(Lnode));
			q5->x=x;q5->y=y+1;q5->z=z;q5->sign=(*p)->sign;
			q5->next=(*p)->head;(*p)->head=q5;
			View(Cube,x,y+1,z,p);		
		}
	}
	if(y-1>=0)
	{
		if(Cube[x][y-1][z]==noview)
		{
			Node q6;q6=(Node)malloc(sizeof(Lnode));
			q6->x=x;q6->y=y-1;q6->z=z;q6->sign=(*p)->sign;
			q6->next=(*p)->head;(*p)->head=q6;
			View(Cube,x,y-1,z,p);
		}
	}
}
void minmax(LinkList *lp)
{
	Node p;
	(*lp)->Xmin=100;(*lp)->Xmax=0;(*lp)->Ymin=100;(*lp)->Ymax=0;(*lp)->Zmin=100;(*lp)->Zmax=0;
	p=(Node)malloc(sizeof(Lnode));p=(*lp)->head;
	while(p)
	{
		if((p->x)<(*lp)->Xmin)
		{
			(*lp)->Xmin=p->x;
		}
		if((p->x)>(*lp)->Xmax)
		{
			(*lp)->Xmax=p->x;
		}
		if((p->y)<(*lp)->Ymin)
		{
			(*lp)->Ymin=p->y;
		}
		if((p->y)>(*lp)->Ymax)
		{
			(*lp)->Ymax=p->y;
		}
		if((p->z)<(*lp)->Zmin)
		{
			(*lp)->Zmin=p->z;
		}
		if((p->z)>(*lp)->Zmax)
		{
			(*lp)->Zmax=p->z;
		}
		p=p->next;
	}
}
void countgroup(cubex Cube,LinkList *L)//����ѭ���иı���x��y��z��ֵ����ѭ������ѭ����ֵӦ�ò�ͬ��
{
	int x,y,z,x1,y1,z1,count,tcount;Node p;LinkList lp;
	tcount=0;
	int n=1;//��ǰ�½��Ŵر��
	for(x=0;x<l;x++)
	{
		for(y=0;y<l;y++)
		{
			for(z=0;z<l;z++)
			{
				if(Cube[x][y][z]==noview)//δ���ʣ������Ŵ�
				{
					count=0;
					lp=(LinkList)malloc(sizeof(Lgroup));
					lp->sign=n;lp->next=NULL;
					p=(Node)malloc(sizeof(Lnode));
					p->x=x;p->y=y;p->z=z;p->sign=n;
					p->next=NULL;
					lp->head=p;
					View(Cube,x,y,z,&lp);//������������ؽ��
					for(x1=0;x1<l;x1++)
					{
						for(y1=0;y1<l;y1++)
							{
							for(z1=0;z1<l;z1++)
								{
									if(Cube[x1][y1][z1]==view)
									{
										Cube[x1][y1][z1]=n;
										count++;
									}
								}
							}
					}
					lp->count=count;
					tcount+=count;
					minmax(&lp);	
					lp->next=(*L)->next;
					(*L)->next=lp;
					n++;
				}
			}
		}
	}
	(*L)->size=n-1;
	printf("n:%d\n",n-1);
 }
int random()//����1-3������� ,����ȷ��������
{
	int i;
	srand((unsigned int)time(NULL));
	i=rand()%3+1;
	return i;
 }
int locate(LinkList L,int k,int *i)//ȷ������λ��.                                            BUG
{
	int spliti,min,max;
	if(k==1)
	{
		min=L->Zmin;max=L->Zmax;
	}
	else if(k==2)
	{
		min=L->Ymin;max=L->Ymax;
	}
	else{
		min=L->Xmin;max=L->Xmax;
	}
	if(max!=min)
	{
		spliti=min+(rand()%(max-min));
		return spliti;
	}
	else
	{
		k=rand()%3+1;
		(*i)=k;
		return locate(L,k,i);
	}
}
int Maxcount(LinkList *L)
{
	LinkList p;
	p=(LinkList)malloc(sizeof(Lgroup));
	int max;
	p=(*L)->next;
	max=p->count;
	while(p!=NULL)
	{
		if((p->count)>max)
		{
			max=p->count;
		}
		p=p->next;
	}
	return max;
}
LinkList choose(LinkList L)
{
	int i=rand()%L->size+1;LinkList p;
	p=(LinkList)malloc(sizeof(Lgroup));p=L;
	while(p)
	{
		if(p->sign==i)
		{
			if(p->count>1)
			{
			return p;
			}
			else
			{
				return choose(L);
			}
		}
		else
		{
			p=p->next;
		}
	}
}
void write_file(cubex Cube,char *filename)
{
  	FILE *fp;
  	if ((fp=fopen(filename,"wt"))==NULL)
	{
	printf("Read File failed! ");
	return;
	}
	int x,y,z;
	for(x=0;x<l;x++)
	{
		for(y=0;y<l;y++)
		{
			for(z=0;z<l;z++)
			{
				if(Cube[x][y][z]>0)//δ���ʣ������Ŵ�
				{
  				fprintf(fp,"%d	%d	%d	%d\n",x,y,z,Cube[x][y][z]);
				}
				}
			}
		}
		fclose(fp);
}
void write_file1(cubex Cube)
{
	char filename[100]="01.txt";FILE *fp;
  	if ((fp=fopen(filename,"wt"))==NULL)
	{
	printf("Read File failed! ");
	return;
	}
	int x,y,z;
	for(x=0;x<l;x++)
	{
		for(y=0;y<l;y++)
		{
			for(z=0;z<l;z++)
			{
				if(Cube[x][y][z]>0)//δ���ʣ������Ŵ�
				{
  				fprintf(fp,"%d	%d	%d\n",x,y,z);
				}
				}
			}
		}
		fclose(fp);
}
int View_1(LinkList *L,LinkList splitp1,cubex cube,Node p,Stack_LinkList *s,int k,int side,int sign)
{
	int x,y,z,peng,signal;
	int i;
	int psign=splitp1->sign;
	LinkList lp,lp1;
	lp=(LinkList)malloc(sizeof(Lgroup));
	Stack_LinkList slp;
	peng=0;
	signal=0;
	if(k==1)
	{
		if(side==1)
		{
			x=p->x;y=p->y;z=p->z+1;
		}
		else {
			x=p->x;y=p->y;z=p->z-1;
		}
		if(x-1>=0)
	{
	if(cube[x-1][y][z]!=psign&&cube[x-1][y][z]!=0&&cube[x-1][y][z]<=2160)
	{
	lp=(*L)->next;
		if(cube[x-1][y][z]==sign)
		{
			return -1;
		}
		while(lp)
		{

			if(lp->sign==cube[x-1][y][z])
			{
				if(signal==0)
				{
					push(s,splitp1);
					signal=1;
				}
				slp=(*s);
					i=1;
				while(slp)
				{

					if(slp->data->sign==lp->sign&&signal==1&&i==2)
					{
						pop(s,&lp1);
						signal=0;
						break;
					}
					else if(slp->data->sign==lp->sign&&signal==1&&i!=2)
					{
							return -1;
							break;
					}
					else
					{
					slp=slp->next;
					i++;
					}
				}
				if(slp==NULL)
				{
				push(s,lp);
				}
				peng=1;
				slp=(*s);
				while(slp)
				{
					slp=slp->next;
				}
				break;
			}
			else
			{
				lp=lp->next;
			}
		}
	}
	}
	if(x+1<=l-1)
	{
	if(cube[x+1][y][z]!=psign&&cube[x+1][y][z]!=0&&cube[x+1][y][z]<=2160)
	{
		lp=(*L)->next;
		if(cube[x+1][y][z]==sign)
		{
			return -1;
		}
		while(lp)
		{
			if(lp->sign==cube[x+1][y][z])
			{
				if(signal==0)
				{
					push(s,splitp1);
					signal=1;
				}
				slp=(*s);
					i=1;
				while(slp)
				{
						if(slp->data->sign==lp->sign&&signal==1&&i==2)
					{
						pop(s,&lp1);
						signal=0;
						break;
					}
					else if(slp->data->sign==lp->sign&&signal==1&&i!=2)
					{
						return -1;
							break;
					}

					else
					{
					slp=slp->next;
					i++;
					}
				}
				if(slp==NULL)
				{
				push(s,lp);
				}
				peng=1;
				slp=(*s);
				while(slp)
				{slp=slp->next;}
				break;
			}
			else
			{
				lp=lp->next;
			}
		}
	}
	}
	if(y-1>=0)
	{
	if(cube[x][y-1][z]!=psign&&cube[x][y-1][z]!=0&&cube[x][y-1][z]<=2160)
	{
		lp=(*L)->next;
		if(cube[x][y-1][z]==sign)
		{
			return -1;
		}
		while(lp)
		{
			if(lp->sign==cube[x][y-1][z])
			{
				if(signal==0)
				{
					push(s,splitp1);
					signal=1;
				}
				slp=(*s);
				i=1;
				while(slp)
				{
						if(slp->data->sign==lp->sign&&signal==1&&i==2)
					{
						pop(s,&lp1);
						signal=0;
						break;
					}
					else if(slp->data->sign==lp->sign&&signal==1&&i!=2)
					{
						return -1;
							break;
					}
					else
					{
					slp=slp->next;
					i++;
					}
				}
				if(slp==NULL)
				{
				push(s,lp);
				}
				peng=1;slp=(*s);
				while(slp)
				{slp=slp->next;}
				break;
			}
			else
			{
				lp=lp->next;
			}
		}
	}
	}
	if(y+1<=l-1)
	{
	if(cube[x][y+1][z]!=psign&&cube[x][y+1][z]!=0&&cube[x][y+1][z]<=2160)
	{
		LinkList lp=(*L)->next;
		if(cube[x][y+1][z]==sign)
		{
			return -1;
		}
		while(lp)
		{
			if(lp->sign==cube[x][y+1][z])
			{
				if(signal==0)
				{
					push(s,splitp1);
					signal=1;
				}

				slp=(*s);
					i=1;
				while(slp)
				{
					if(slp->data->sign==lp->sign&&signal==1&&i==2)
					{
						pop(s,&lp1);
						signal=0;
						break;
					}
					else if(slp->data->sign==lp->sign&&signal==1&&i!=2)
					{
						return -1;
							break;
					}

					else
					{
					slp=slp->next;
					i++;
					}
				}
				if(slp==NULL)
				{
				push(s,lp);
				}
				peng=1;
				slp=(*s);
				while(slp)
				{slp=slp->next;}
				break;
			}
			else
			{
				lp=lp->next;
			}
		}
	}

	}
	if(z-1>=0&&side==2)
	{
	if(cube[x][y][z-1]!=psign&&cube[x][y][z-1]!=0&&cube[x][y][z-1]<=2160)
	{
		lp=(*L)->next;
		if(cube[x][y][z-1]==sign)
		{
			return -1;
		}
		while(lp)
		{
			if(lp->sign==cube[x][y][z-1])
			{
				if(signal==0)
				{
					push(s,splitp1);
					signal=1;
				}
				slp=(*s);
				i=1;
				while(slp)
				{
						if(slp->data->sign==lp->sign&&signal==1&&i==2)
					{
						pop(s,&lp1);
						signal=0;
						break;
					}
					else if(slp->data->sign==lp->sign&&signal==1&&i!=2)
					{
						return -1;
							break;
					}
					else
					{
					slp=slp->next;
					i++;
					}
				}
				if(slp==NULL)
				{
				push(s,lp);
				}
				peng=1;
				slp=(*s);
				while(slp)
				{
					slp=slp->next;
				}
				break;
			}
			else
			{
				lp=lp->next;
			}
		}
	}
	}
	if(z+1<=l-1&&side==1)
	{
		if(cube[x][y][z+1]!=psign&&cube[x][y][z+1]!=0&&cube[x][y][z+1]<=2160)
	{
		lp=(*L)->next;
		if(cube[x][y][z+1]==sign)
		{
			return -1;
		}
		while(lp)
		{
			if(lp->sign==cube[x][y][z+1])
			{
				if(signal==0)
				{
					push(s,splitp1);
					signal=1;
				}

				slp=(*s);
					i=1;
				while(slp)
				{
						if(slp->data->sign==lp->sign&&signal==1&&i==2)
					{
						pop(s,&lp1);
						signal=0;
						break;
					}
					else if(slp->data->sign==lp->sign&&signal==1&&i!=2)
					{
						return -1;
							break;
					}

					else
					{
					slp=slp->next;
					i++;
					}
				}
				if(slp==NULL)
				{
				push(s,lp);
				}
				peng=1;
				slp=(*s);
				while(slp)
				{
					slp=slp->next;
				}
				break;
			}
			else
			{
				lp=lp->next;
			}
		}
	}
	}
	}
	if(k==2)
	{
		if(side==1)
		{
			x=p->x;y=p->y+1;z=p->z;
		}
		else{
			x=p->x;y=p->y-1;z=p->z;
		}
		if(x-1>=0)
	{
	if(cube[x-1][y][z]!=psign&&cube[x-1][y][z]!=0&&cube[x-1][y][z]<=2160)
	{
	lp=(*L)->next;
		if(cube[x-1][y][z]==sign)
		{
			return -1;
		}
		while(lp)
		{
			if(lp->sign==cube[x-1][y][z])
			{
				if(signal==0)
				{
					push(s,splitp1);
					signal=1;
				}
				slp=(*s);
					i=1;
				while(slp)
				{
					if(slp->data->sign==lp->sign&&signal==1&&i==2)
					{
						pop(s,&lp1);
						signal=0;
						break;
					}
					else if(slp->data->sign==lp->sign&&signal==1&&i!=2)
					{
						return -1;
							break;
					}

					else
					{
					slp=slp->next;
					i++;
					}
				}
				if(slp==NULL)
				{
				push(s,lp);
				}
				peng=1;
				slp=(*s);
				while(slp)
				{
					slp=slp->next;
				}
				break;
			}
			else
			{
				lp=lp->next;
			}
		}
	}
	}
	if(x+1<=l-1)
	{
	if(cube[x+1][y][z]!=psign&&cube[x+1][y][z]!=0&&cube[x+1][y][z]<=2160)
	{
		lp=(*L)->next;
		if(cube[x+1][y][z]==sign)
		{
			return -1;
		}
		while(lp)
		{
			if(lp->sign==cube[x+1][y][z])
			{
				if(signal==0)
				{
					push(s,splitp1);
					signal=1;
				}
				slp=(*s);
					i=1;
				while(slp)
				{
					if(slp->data->sign==lp->sign&&signal==1&&i==2)
					{
						pop(s,&lp1);
						signal=0;
						break;
					}
					else if(slp->data->sign==lp->sign&&signal==1&&i!=2)
					{
						return -1;
							break;
					}

					else
					{
					slp=slp->next;
					i++;
					}
				}
				if(slp==NULL)
				{
				push(s,lp);
				}
				peng=1;
				slp=(*s);
				while(slp)
				{
					slp=slp->next;
				}
				break;
			}
			else
			{
				lp=lp->next;
			}
		}
	}
	}

	if(z-1>=0)
	{
		if(cube[x][y][z-1]!=psign&&cube[x][y][z-1]!=0&&cube[x][y][z-1]<=2160)
	{
		lp=(*L)->next;
		if(cube[x][y][z-1]==sign)
		{
			return -1;
		}
		while(lp)
		{
			if(lp->sign==cube[x][y][z-1])
			{
				if(signal==0)
				{
					push(s,splitp1);
					signal=1;
				}

				slp=(*s);
			i=1;
				while(slp)
				{
					if(slp->data->sign==lp->sign&&signal==1&&i==2)
					{
						pop(s,&lp1);
						signal=0;
						break;
					}
					else if(slp->data->sign==lp->sign&&signal==1&&i!=2)
					{
						return -1;
							break;
					}
					else
					{
					slp=slp->next;
					i++;
					}
				}
				if(slp==NULL)
				{
				push(s,lp);
				}
				peng=1;
				slp=(*s);
				while(slp)
				{
					slp=slp->next;
				}
				break;
			}
			else
			{
				lp=lp->next;
			}
		}
	}
	}
	if(z+1<=l-1)
	{
	if(cube[x][y][z+1]!=psign&&cube[x][y][z+1]!=0&&cube[x][y][z+1]<=2160)
	{
		lp=(*L)->next;
		if(cube[x][y][z+1]==sign)
		{
			return -1;
		}
		while(lp)
		{
			if(lp->sign==cube[x][y][z+1])
			{
				if(signal==0)
				{
					push(s,splitp1);
					signal=1;
				}

				slp=(*s);
				i=1;
				while(slp)
				{
						if(slp->data->sign==lp->sign&&signal==1&&i==2)
					{
						pop(s,&lp1);
						signal=0;
						break;
					}
					else if(slp->data->sign==lp->sign&&signal==1&&i!=2)
					{
						return -1;
							break;
					}

					else
					{
					slp=slp->next;
					i++;
					}
				}
				if(slp==NULL)
				{
				push(s,lp);
				}
				peng=1;
				slp=(*s);
				while(slp)
				{
					slp=slp->next;
				}
				break;
			}
			else
			{
				lp=lp->next;
			}
		}
	}
	}
	if(y-1>=0&&side==2)
	{
	if(cube[x][y-1][z]!=psign&&cube[x][y-1][z]!=0&&cube[x][y-1][z]<=2160)
	{
		lp=(*L)->next;
		if(cube[x][y-1][z]==sign)
		{
			return -1;
		}
		while(lp)
		{
			if(lp->sign==cube[x][y-1][z])
			{
				if(signal==0)
				{
					push(s,splitp1);
					signal=1;
				}
				slp=(*s);
					i=1;
				while(slp)
				{
						if(slp->data->sign==lp->sign&&signal==1&&i==2)
					{
						pop(s,&lp1);
						signal=0;
						break;
					}
					else if(slp->data->sign==lp->sign&&signal==1&&i!=2)
					{
						return -1;
							break;
					}
					else
					{
					slp=slp->next;
					i++;
					}
				}
				if(slp==NULL)
				{
				push(s,lp);
				}
				peng=1;
				slp=(*s);
				while(slp)
				{
					slp=slp->next;
				}
				break;
			}
			else
			{
				lp=lp->next;
			}
		}
	}
	}
	if(y+1<=l-1&&side==1)
	{
	if(cube[x][y+1][z]!=psign&&cube[x][y+1][z]!=0&&cube[x][y+1][z]<=2160)
	{
		LinkList lp=(*L)->next;
		if(cube[x][y+1][z]==sign)
		{
			return -1;
		}
		while(lp)
		{
			if(lp->sign==cube[x][y+1][z])
			{
				if(signal==0)
				{
					push(s,splitp1);
					signal=1;
				}
				slp=(*s);
				i=1;
				while(slp)
				{
						if(slp->data->sign==lp->sign&&signal==1&&i==2)
					{
						pop(s,&lp1);
						signal=0;
						break;
					}
					else if(slp->data->sign==lp->sign&&signal==1&&i!=2)
					{
						return -1;
							break;
					}

					else
					{
					slp=slp->next;
					i++;
					}
				}
				if(slp==NULL)
				{
				push(s,lp);
				}
				peng=1;
				slp=(*s);
				while(slp)
				{
					slp=slp->next;
				}
				break;
			}
			else
			{
				lp=lp->next;
			}
		}
	}
	}
	}
	if(k==3)
	{
		if(side==1)
		{
			x=p->x+1;y=p->y;z=p->z;
		}
		else
		{
			x=p->x-1;y=p->y;z=p->z;
		}
	if(y-1>=0)
	{
	if(cube[x][y-1][z]!=psign&&cube[x][y-1][z]!=0&&cube[x][y-1][z]<=2160)
	{
		lp=(*L)->next;
		if(cube[x][y-1][z]==sign)
		{
			return -1;
		}
		while(lp)
		{
			if(lp->sign==cube[x][y-1][z])
			{
				if(signal==0)
				{
					push(s,splitp1);
					signal=1;
				}
				slp=(*s);
				i=1;
				while(slp)
				{
						if(slp->data->sign==lp->sign&&signal==1&&i==2)
					{
						pop(s,&lp1);
						signal=0;
						break;
					}
					else if(slp->data->sign==lp->sign&&signal==1&&i!=2)
					{
						return -1;
							break;
					}
					else
					{
					slp=slp->next;
					i++;
					}
				}
				if(slp==NULL)
				{
				push(s,lp);
				}
				peng=1;
				slp=(*s);
				while(slp)
				{
					slp=slp->next;
				}
				break;
			}
			else
			{
				lp=lp->next;
			}
		}
	}
	}
	if(y+1<=l-1)
	{
	if(cube[x][y+1][z]!=psign&&cube[x][y+1][z]!=0&&cube[x][y+1][z]<=2160)
	{
		LinkList lp=(*L)->next;
		if(cube[x][y+1][z]==sign)
		{
			return -1;
		}
		while(lp)
		{
			if(lp->sign==cube[x][y+1][z])
			{
				if(signal==0)
				{
					push(s,splitp1);
					signal=1;
				}

				slp=(*s);
				i=1;
				while(slp)
				{
						if(slp->data->sign==lp->sign&&signal==1&&i==2)
					{
						pop(s,&lp1);
						signal=0;
						break;
					}
					else if(slp->data->sign==lp->sign&&signal==1&&i!=2)
					{
						return -1;
							break;
					}
					else
					{
					slp=slp->next;
					i++;
					}
				}
				if(slp==NULL)
				{
				push(s,lp);
				}
				peng=1;slp=(*s);
				while(slp)
				{
					slp=slp->next;
				}
				break;
			}
			else
			{
				lp=lp->next;
			}
		}
	}
	}
	if(z-1>=0)
	{
		if(cube[x][y][z-1]!=psign&&cube[x][y][z-1]!=0&&cube[x][y][z-1]<=2160)
	{
		lp=(*L)->next;
		if(cube[x][y][z-1]==sign)
		{
			return -1;
		}
		while(lp)
		{
			if(lp->sign==cube[x][y][z-1])
			{
				if(signal==0)
				{
					push(s,splitp1);
					signal=1;
				}

				slp=(*s);
				i=1;
				while(slp)
				{
						if(slp->data->sign==lp->sign&&signal==1&&i==2)
					{
						pop(s,&lp1);
						signal=0;
						break;
					}
					else if(slp->data->sign==lp->sign&&signal==1&&i!=2)
					{
						return -1;
							break;
					}

					else
					{
					slp=slp->next;
					i++;
					}
				}
				if(slp==NULL)
				{
				push(s,lp);
				}
				peng=1;
				slp=(*s);
				while(slp)
				{
					slp=slp->next;
				}
				break;
			}
			else
			{
				lp=lp->next;
			}
		}
	}
	}
	if(z+1<=l-1)
	{
		if(cube[x][y][z+1]!=psign&&cube[x][y][z+1]!=0&&cube[x][y][z+1]<=2160)
	{
		lp=(*L)->next;
		if(cube[x][y][z+1]==sign)
		{
			return -1;
		}
		while(lp)
		{
			if(lp->sign==cube[x][y][z+1])
			{
				if(signal==0)
				{
					push(s,splitp1);
					signal=1;
				}

				slp=(*s);
				i=1;
				while(slp)
				{
						if(slp->data->sign==lp->sign&&signal==1&&i==2)
					{
						pop(s,&lp1);
						signal=0;
						break;
					}
					else if(slp->data->sign==lp->sign&&signal==1&&i!=2)
					{
						return -1;
							break;
					}
					else
					{
					slp=slp->next;
					i++;
					}
				}
				if(slp==NULL)
				{
				push(s,lp);
				}
				peng=1;
				slp=(*s);
				while(slp)
				{
					slp=slp->next;
				}
				break;
			}
			else
			{
				lp=lp->next;
			}
		}
	}
	}
	if(x-1>=0&&side==2)
	{
	if(cube[x-1][y][z]!=psign&&cube[x-1][y][z]!=0&&cube[x-1][y][z]<=2160)
	{
	lp=(*L)->next;
	if(cube[x-1][y][z]==sign)
		{
			return -1;
		}
		while(lp)
		{
			if(lp->sign==cube[x-1][y][z])
			{
				if(signal==0)
				{
					push(s,splitp1);
					signal=1;
				}
				slp=(*s);
					i=1;
				while(slp)
				{
						if(slp->data->sign==lp->sign&&signal==1&&i==2)
					{
						pop(s,&lp1);
						signal=0;
						break;
					}
					else if(slp->data->sign==lp->sign&&signal==1&&i!=2)
					{
						return -1;
							break;
					}

					else
					{
					slp=slp->next;
					i++;
					}
				}
				if(slp==NULL)
				{
				push(s,lp);
				}
				peng=1;
				slp=(*s);
				while(slp)
				{
					slp=slp->next;
				}
				break;
			}
			else
			{
				lp=lp->next;
			}
		}
	}
	}
	if(x+1<=l-1&&side==1)
	{
	if(cube[x+1][y][z]!=psign&&cube[x+1][y][z]!=0&&cube[x+1][y][z]<=2160)
	{
		lp=(*L)->next;
		if(cube[x+1][y][z]==sign)
		{
			return -1;
		}
		while(lp)
		{
			if(lp->sign==cube[x+1][y][z])
			{
				if(signal==0)
				{
					push(s,splitp1);
					signal=1;
				}
				slp=(*s);
					i=1;
				while(slp)
				{
						if(slp->data->sign==lp->sign&&signal==1&&i==2)
					{
						pop(s,&lp1);
						signal=0;
						break;
					}
					else if(slp->data->sign==lp->sign&&signal==1&&i!=2)
					{
						return -1;
							break;
					}

					else
					{
					slp=slp->next;
					i++;
					}
				}
				if(slp==NULL)
				{
				push(s,lp);
				}
				peng=1;
				slp=(*s);
				while(slp)
				{
					slp=slp->next;
				}
				break;
			}
			else
			{
				lp=lp->next;
			}
		}
	}
	}
	}

	return peng;
}
int split_2(LinkList *L,LinkList *splitp,cubex Cube,int i,int k)
{
	int totalsign=(*splitp)->sign;
	LinkList splitp1,lp;
	lp=(LinkList)malloc(sizeof(Lgroup));
	splitp1=(LinkList)malloc(sizeof(Lgroup));
	int success;//���ѳɹ��ı�־����
	int zhuang;//�Ƿ���ײ
	int splitp_sign;//�Ƿ�Ϊ����ײ���Ŵ�
	int zhuang1;//��ײ���Ŵ��Ƿ��ٱ�ײ
	LinkStack s,moves;
	moves=(Stack_LinkList)malloc(sizeof(Stack_Lnode));
	s=(Stack_LinkList)malloc(sizeof(Stack_Lnode));
	InitStack(&s);
	InitStack(&moves);
	push(&s,*splitp);
	while(ListLength(s)!=0)
	{
	splitp_sign=0;
	zhuang=0;
	zhuang1=0;
	success=1;//���ѳɹ��ı�־����
	GetTop(s,&splitp1);
	pop(&s,&lp);
	Node p=lp->head;
	if(k==1)															
	{
		while(p)
		{
			if(p->z-1>=0)
			{
				if(p->sign==totalsign)
				{
					if(p->z<=i)
					{
						if(View_1(L,splitp1,Cube,p,&s,k,2,lp->sign)==1)//�������Ŵ���ײ
						{
							zhuang=1;//��ײ���Ϊ1
							success=0;//����ʧ��
							break;//�˳�ѭ��
						}
						else if(View_1(L,splitp1,Cube,p,&s,k,2,lp->sign)==-1)
						{
							return -1;
						}
						else
						{
							p=p->next;
						}
					}
					else
					{
						p=p->next;
					}
				}
				else
				{
					splitp_sign=1;//�˴��ƶ����Ǳ����ƶ����Ŵ�
					if(View_1(L,splitp1,Cube,p,&s,k,2,lp->sign)==1)//�������Ŵ���ײ
						{
							zhuang1=1;//��ײ���Ϊ1
							success=0;//����ʧ��
							break;//�˳�ѭ��
						}
						else if(View_1(L,splitp1,Cube,p,&s,k,2,lp->sign)==-1)
						{
							return -1;
						}
					else
					{
						p=p->next;
					}
				}
			}
			else
			{
				while(ListLength(moves)!=0)
				{
					pop(&moves,&lp);
					Node p1=lp->head;
					while(p1)
					{
						Cube[p1->x][p1->y][p1->z]=0;
						p1->z+=1;
						p1=p1->next;

					}
					p1=lp->head;
					while(p1)
					{
						Cube[p1->x][p1->y][p1->z]=lp->sign;
					}

				}
				ClearStack(&s);ClearStack(&moves);
				return 0;
			}
		}
		if(!zhuang)
		{
			if(lp->sign==totalsign)
			{
				Node p1=lp->head;
				while(p1)
				{
					if(p1->z<=i&&p1->z-1>=0)
					{
						Cube[p1->x][p1->y][p1->z]=0; ///////20170605 23:22 ����һ���ַ�����ײ�����ֵ����
						p1->z-=1;
						p1=p1->next;
					}
					else
					{
						p1=p1->next;
					}
				}
			}
		}
		if(!zhuang1&&splitp_sign)
		{
				Node p1=lp->head;
				while(p1)
				{
					if(p1->z-1>=0)
					{
						Cube[p1->x][p1->y][p1->z]=0;
						p1->z-=1;
						p1=p1->next;
					}
					else
					{
						p1=p1->next;
					}
				}
				push(&moves,lp);
		}

	}
	else if(k==2)
	{
		while(p)
		{
			if(p->y-1>=0)
			{
			if(p->sign==totalsign)
			{
				if(p->y<=i)
				{
					if(View_1(L,splitp1,Cube,p,&s,k,2,lp->sign)==1)//�������Ŵ���ײ
						{
							zhuang=1;//��ײ���Ϊ1
							success=0;//����ʧ��
							break;//�˳�ѭ��
						}
						else if(View_1(L,splitp1,Cube,p,&s,k,2,lp->sign)==-1)
						{
							return -1;
						}
					else
					{
						p=p->next;
					}
				}
				else
				{
					p=p->next;
				}
			}
		    else
			{
				splitp_sign=1;
				if(View_1(L,splitp1,Cube,p,&s,k,2,lp->sign)==1)//�������Ŵ���ײ
						{
							zhuang1=1;//��ײ���Ϊ1
							success=0;//����ʧ��
							break;//�˳�ѭ��
						}
						else if(View_1(L,splitp1,Cube,p,&s,k,2,lp->sign)==-1)
						{
							return -1;
						}
				else
				{
					p=p->next;
				}
			}
		}
		else
		{
			while(ListLength(moves)!=0)
			{
				pop(&moves,&lp);
				Node p1=lp->head;
				while(p1)
				{
					Cube[p1->x][p1->y][p1->z]=0;
					p1->y+=1;
					p1=p1->next;

				}
				p1=lp->head;
				while(p1)
				{
					Cube[p1->x][p1->y][p1->z]=lp->sign;
				}

			}
			ClearStack(&s);ClearStack(&moves);
			return 0;
		}
		}
		if(!zhuang)
		{
			if(lp->sign==totalsign)
			{
				Node p1=lp->head;
				while(p1)
				{
					if(p1->y<=i&&p1->y-1>=0)
					{
						Cube[p1->x][p1->y][p1->z]=0; ///////20170605 23:22 ����һ���ַ�����ײ�����ֵ����
						p1->y-=1;
						p1=p1->next;
					}
					else
					{
						p1=p1->next;
					}
				}
			}
		}
		if(!zhuang1&&splitp_sign)
		{
				Node p1=lp->head;
				while(p1)
				{
					if(p1->y-1>=0)
					{
						Cube[p1->x][p1->y][p1->z]=0;
						p1->y-=1;
						p1=p1->next;
					}
					else
					{
						p1=p1->next;
					}
				}
				push(&moves,lp);
		}
	}
	else
	{
		while(p)
		{
			if(p->x-1>=0)
			{
			if(p->sign==totalsign)
			{
				if(p->x<=i)
				{
					if(View_1(L,splitp1,Cube,p,&s,k,2,lp->sign)==1)//�������Ŵ���ײ
						{
							zhuang=1;//��ײ���Ϊ1
							success=0;//����ʧ��
							break;//�˳�ѭ��
						}
						else if(View_1(L,splitp1,Cube,p,&s,k,2,lp->sign)==-1)
						{
							return -1;
						}
					else
					{
						p=p->next;
					}
				}
				else
				{
					p=p->next;
				}
			}
		    else
			{
				splitp_sign=1;
				if(View_1(L,splitp1,Cube,p,&s,k,2,lp->sign)==1)//�������Ŵ���ײ
						{
							zhuang1=1;//��ײ���Ϊ1
							success=0;//����ʧ��
							break;//�˳�ѭ��
						}
						else if(View_1(L,splitp1,Cube,p,&s,k,2,lp->sign)==-1)
						{
							return -1;
						}
				else
				{
					p=p->next;
				}
			}
		}
		else
		{
			while(ListLength(moves)!=0)
			{
				pop(&moves,&lp);
				Node p1=lp->head;
				while(p1)
				{
					Cube[p1->x][p1->y][p1->z]=0;
					p1->x+=1;
					p1=p1->next;

				}
				p1=lp->head;
				while(p1)
				{
					Cube[p1->x][p1->y][p1->z]=lp->sign;
				}
			}
			ClearStack(&s);ClearStack(&moves);
			return 0;
		}
		}
		if(!zhuang)
		{
			if(lp->sign==totalsign)
			{
				Node p1=lp->head;
				while(p1)
				{
					if(p1->x<=i&&p1->x-1>=0)
					{
						Cube[p1->x][p1->y][p1->z]=0; ///////20170605 23:22 ����һ���ַ�����ײ�����ֵ����
						p1->x-=1;
						p1=p1->next;
					}
					else
					{
						p1=p1->next;
					}
				}
			}
		}
		if(!zhuang1&&splitp_sign)
		{
				Node p1=lp->head;
				while(p1)
				{
					if(p1->x-1>=0)
					{
						Cube[p1->x][p1->y][p1->z]=0;
						p1->x-=1;
						p1=p1->next;
					}
					else
					{
						p1=p1->next;
					}
				}
				push(&moves,lp);
		}
	}
	if(success)
	{
	Node p1=lp->head;
	while(p1)
	{
		Cube[p1->x][p1->y][p1->z]=lp->sign;
		p1=p1->next;
	}
	}
	}
	return success;

}
int split(LinkList *L,LinkList *splitp,cubex Cube,int i,int k)				//���Ѻ���֮���� ����ײ��ƽ�ƣ���Ҫ�õ�ջ
{
	LinkList splitp1,lp,*lp2;
	int success;//���ѳɹ��ı�־
	int zhuang;//�Ƿ���ײ
	int nextsign;
	int splitp_sign;//�Ƿ�Ϊ����ײ���Ŵ�
	int zhuang1;//��ײ���Ŵ��Ƿ��ٱ�ײ
	int totalsign=(*splitp)->sign;
	lp=(LinkList)malloc(sizeof(Lgroup));
	lp2=(LinkList*)malloc(sizeof(Lgroup));
	splitp1=(LinkList)malloc(sizeof(Lgroup));
	LinkStack s,moves;
	moves=(Stack_LinkList)malloc(sizeof(Stack_Lnode));
	s=(Stack_LinkList)malloc(sizeof(Stack_Lnode));
	InitStack(&s);
	InitStack(&moves);
	push(&s,*splitp);
	while(ListLength(s)!=0)
	{
	splitp_sign=0;
	zhuang=0;
	zhuang1=0;
	success=1;//���ѳɹ��ı�־����
	pop(&s,&lp);
	if(ListLength(s)!=0)
	{
		GetTop(s,lp2);
		nextsign=(*lp2)->sign;
	}
	else
	{
		nextsign=2163;
	}
	splitp1=lp;
	Node p=lp->head;
	if(k==1)															//�ƶ���֮ǰ���ÿ��ǵ������Ƿ��е㣬��Ϊ�Ŵ��Ѿ���ͳ�ƹ���ֻ������ƶ�������
	{
		while(p)          //Ԥ�ȷ��Ѵ��� �ж��Ƿ���ײ
		{
			if(p->z+1<=99)
			{
				if(p->sign==totalsign)
				{
					if(p->z>i)
					{
						if(View_1(L,splitp1,Cube,p,&s,k,1,nextsign)==1)//�������Ŵ���ײ
						{
							zhuang=1;//��ײ���Ϊ1
							success=0;//����ʧ��
							break;//�˳�ѭ��
						}
						else if(View_1(L,splitp1,Cube,p,&s,k,1,nextsign)==-1)
						{
							return -1;
						}
						else
						{
							p=p->next;
						}
					}
					else
					{
						p=p->next;
					}
				}
				else
				{
					splitp_sign=1;
					if(View_1(L,splitp1,Cube,p,&s,k,1,nextsign)==1)//�������Ŵ���ײ
						{
							zhuang1=1;//��ײ���Ϊ1
							success=0;//����ʧ��
							break;//�˳�ѭ��
						}
						else if(View_1(L,splitp1,Cube,p,&s,k,1,nextsign)==-1)
						{
							return -1;
						}
					else
					{
						p=p->next;
					}
				}
			}
			else
			{
				while(ListLength(moves)!=0)
				{
					pop(&moves,&lp);
					Node p1=lp->head;
					while(p1)
					{
						Cube[p1->x][p1->y][p1->z]=0;
						p1->z-=1;
						p1=p1->next;
					}
					p1=lp->head;
					while(p1)
					{
						Cube[p1->x][p1->y][p1->z]=lp->sign;
						p1=p1->next;
					}

				}
				ClearStack(&s);ClearStack(&moves);
				return 0;
			}
			}
			if(!zhuang)
			{

				if(lp->sign==totalsign)
				{
					Node p1=lp->head;
					while(p1)
					{
						if(p1->z>i&&p1->z+1<=l-1)
						{
							Cube[p1->x][p1->y][p1->z]=0; ///////20170605 23:22 ����һ���ַ�����ײ�����ֵ����
							p1->z+=1;
							p1=p1->next;
						}
						else
						{
							p1=p1->next;
						}
					}
				}
			}
			if(!zhuang1&&splitp_sign)
			{
					Node p1=lp->head;
					while(p1)
					{
						if(p1->z+1<=l-1)
						{
							Cube[p1->x][p1->y][p1->z]=0;
							p1->z+=1;
							p1=p1->next;
						}
						else
						{
							p1=p1->next;
						}
					}
					push(&moves,lp);
			}

	}
	else if(k==2)
	{
		while(p)
		{
			if(p->y+1<=99)
			{
			if(p->sign==totalsign)
			{
				if(p->y>i)
				{
					if(View_1(L,splitp1,Cube,p,&s,k,1,nextsign)==1)//�������Ŵ���ײ
						{
							zhuang=1;//��ײ���Ϊ1
							success=0;//����ʧ��
							break;//�˳�ѭ��
						}
						else if(View_1(L,splitp1,Cube,p,&s,k,1,nextsign)==-1)
						{
							return -1;
						}
					else
					{
						p=p->next;
					}
				}
				else
				{
					p=p->next;
				}
			}
		    else
			{
				splitp_sign=1;
				if(View_1(L,splitp1,Cube,p,&s,k,1,nextsign)==1)//�������Ŵ���ײ
						{
							zhuang1=1;//��ײ���Ϊ1
							success=0;//����ʧ��
							break;//�˳�ѭ��
						}
						else if(View_1(L,splitp1,Cube,p,&s,k,1,nextsign)==-1)
						{
							return -1;
						}
				else
				{
					p=p->next;
				}
			}
		}
		else
		{
			while(ListLength(moves)!=0)
			{
				pop(&moves,&lp);
				Node p1=lp->head;
				while(p1)
				{
					Cube[p1->x][p1->y][p1->z]=0;
					p1->y-=1;
					p1=p1->next;

				}
				p1=lp->head;
				while(p1)
				{
					Cube[p1->x][p1->y][p1->z]=lp->sign;
					p1=p1->next;
				}

			}
			ClearStack(&s);ClearStack(&moves);
			return 0;
		}
		}
		if(!zhuang)
		{
			if(lp->sign==totalsign)
			{
				Node p1=lp->head;
				while(p1)
				{
					if(p1->y>i&&p1->y+1<=l-1)
					{
						Cube[p1->x][p1->y][p1->z]=0; ///////20170605 23:22 ����һ���ַ�����ײ�����ֵ����
						p1->y+=1;
						p1=p1->next;
					}
					else
					{
						p1=p1->next;
					}
				}
			}
		}
		if(!zhuang1&&splitp_sign)
		{
				Node p1=lp->head;
				while(p1)
				{
					if(p1->y+1<=l-1)
					{
						Cube[p1->x][p1->y][p1->z]=0;
						p1->y+=1;
						p1=p1->next;
					}
					else
					{
						p1=p1->next;
					}
				}
				push(&moves,lp);
		}
	}
	else
	{
		while(p)
		{
			if(p->x+1<=99)
			{
			if(p->sign==totalsign)
			{
				if(p->x>i)
				{
					if(View_1(L,splitp1,Cube,p,&s,k,1,nextsign)==1)//�������Ŵ���ײ
						{
							zhuang=1;//��ײ���Ϊ1
							success=0;//����ʧ��
							break;//�˳�ѭ��
						}
						else if(View_1(L,splitp1,Cube,p,&s,k,1,nextsign)==-1)
						{
							return -1;
						}
					else
					{
						p=p->next;
					}
				}
				else
				{
					p=p->next;
				}
			}
		    else
			{
				splitp_sign=1;
				if(View_1(L,splitp1,Cube,p,&s,k,1,nextsign)==1)//�������Ŵ���ײ
						{
							zhuang1=1;//��ײ���Ϊ1
							success=0;//����ʧ��
							break;//�˳�ѭ��
						}
						else if(View_1(L,splitp1,Cube,p,&s,k,1,nextsign)==-1)
						{
							return -1;
						}
				else
				{
					p=p->next;
				}
			}
		}
		else
		{
			while(ListLength(moves)!=0)
			{
				pop(&moves,&lp);
				Node p1=lp->head;
				while(p1)
				{
					Cube[p1->x][p1->y][p1->z]=0;
					p1->x-=1;
					p1=p1->next;

				}
				p1=lp->head;
				while(p1)
				{
					Cube[p1->x][p1->y][p1->z]=lp->sign;
					p1=p1->next;
				}
			}
				ClearStack(&s);ClearStack(&moves);
			return 0;
		}
		}
		if(!zhuang)
		{
			if(lp->sign==totalsign)
			{
				Node p1=lp->head;
				while(p1)
				{
					if(p1->x>i&&p1->x+1<=l-1)
					{
						Cube[p1->x][p1->y][p1->z]=0; ///////20170605 23:22 ����һ���ַ�����ײ�����ֵ����
						p1->x+=1;
						p1=p1->next;
					}
					else
					{
						p1=p1->next;
					}
				}
			}
		}
		if(!zhuang1&&splitp_sign)
		{
				Node p1=lp->head;
				while(p1)
				{
					if(p1->x+1<=l-1)
					{
						Cube[p1->x][p1->y][p1->z]=0;
						p1->x+=1;
						p1=p1->next;
					}
					else
					{
						p1=p1->next;
					}
				}
				push(&moves,lp);
		}
	}
	if(success)
	{
		Node p1=lp->head;
		while(p1)
		{
			Cube[p1->x][p1->y][p1->z]=lp->sign;
			p1=p1->next;
		}
	}

	}
return success;
}
int count_group_by_list_2(LinkList *up,cubex Cube)//�����Ǻ����Ŵ�
{
	int n1;int count;
	Node p,p1;LinkList lp1,ulp;
	p=(*up)->head;
	while(p)
	{
		Cube[p->x][p->y][p->z]=noview;
		p=p->next;
	}
	n1=1;
	(*up)->next=NULL;
	p=(*up)->head;
	while(p)
	{
		if(Cube[p->x][p->y][p->z]==noview)
		{
		count=0;
		lp1=(LinkList)malloc(sizeof(Lgroup));
		lp1->sign=n1;lp1->next=NULL;
		p1=(Node)malloc(sizeof(Lnode));
		p1->x=p->x;p1->y=p->y;p1->z=p->z;p1->sign=lp1->sign;
		p1->next=NULL;
		lp1->head=p1;
		View(Cube,p->x,p->y,p->z,&lp1);//������������ؽ��
		p1=lp1->head;
		while(p1)
		{
			Cube[p1->x][p1->y][p1->z]=n1;
			count++;
			p1=p1->next;
		}
		lp1->count=count;
		minmax(&lp1);
		lp1->next=(*up)->next;
		(*up)->next=lp1;
		n1++;
		}
		p=p->next;
	}//�ҳ��˷��Ѻ��γɵ��������Ŵ�     �ڶ���
	return n1-1;
}
int unionlist(LinkList *up,cubex Cube,int i,int k)				//���Ѻ���֮�ϲ� ����ײ�ͻ�ۣ�
{
	int n=1;int groupNum;
	int ucount;
	int init_sign=(*up)->sign;            //��һ��
	int dots;Node p;												//���ڴ洢����Ŵؽ����
	LinkList lp;
	LinkList ulp,ulp1;
	ulp1=(LinkList)malloc(sizeof(Lgroup));
	int x,y,z,x1,y1,z1;
	groupNum=count_group_by_list_2(up,Cube);
	if(groupNum==2)
	{
		return 1;
	}
	dots=0;
	int lq=0;
	ulp=(*up)->next;//up������Ŵر���
	while(ulp)
	{
		if(k==1)
		{
			if(ulp->Zmin>i)
			{
					if(ulp->count>dots)//�ҳ�����Ŵ�
					{
						dots=ulp->count;
						lq=ulp->sign;
					}
			}
		}
		else if(k==2)
		{
			if(ulp->Ymin>i)
			{
					if(ulp->count>dots)//�ҳ�����Ŵ�
					{
					dots=ulp->count;
					lq=ulp->sign;
					}
			}
		}
		else
		{
			if(ulp->Xmin>i)
			{
					if(ulp->count>dots)//�ҳ�����Ŵ�
					{
					dots=ulp->count;
					lq=ulp->sign;
					}
			}
		}
		ulp=ulp->next;
	}
	ulp=(*up)->next;
	while(ulp)
	{
		if(k==1)
		{
			if(ulp->Zmin>i)
			{
					if(ulp->sign!=lq)//��������Ŵ�
			{
					p=ulp->head;
					while(p)
					{
						Cube[p->x][p->y][p->z]=0;//�ϲ�
						(p->z)-=1;
						p=p->next;
					}
					}
			}
		}
		if(k==2)
		{
			if(ulp->Ymin>i)
			{
					if(ulp->sign!=lq)//��������Ŵ�
					{
					p=ulp->head;
					while(p)
					{
					Cube[p->x][p->y][p->z]=0;//�ϲ�
					(p->y)-=1;
					p=p->next;
					}
					}
			}
		}
		if(k==3)
		{
			if(ulp->Xmin>i)
			{
					if(ulp->sign!=lq)//��������Ŵ�
					{
				    p=ulp->head;
					while(p)
					{
					Cube[p->x][p->y][p->z]=0;//�ϲ�
					//if(View_2(p,k,2,Cube));
					(p->x)-=1;
					p=p->next;
					}
					}
			}
		}
		ulp=ulp->next;
	}//������
	ulp=(*up)->next;
	int t=0;
	while(ulp)
	{
		Node p1=ulp->head;
		while(p1)
		{
		Cube[p1->x][p1->y][p1->z]=noview;
		p1=p1->next;
		t++;
		}
		ulp=ulp->next;
	}
	(*up)->next=NULL;
	countgroup(Cube,up);
	lq=0;//         ������
	dots=0;
	ulp=(*up)->next;
	while(ulp)
	{
		if(k==1)
		{
			if(ulp->Zmin<=i)
			{
					if(ulp->count>dots)//�ҳ�����Ŵ�
					{
						dots=ulp->count;
						lq=ulp->sign;
					}
			}
		}
		if(k==2)
		{
			if(ulp->Ymin<=i)
			{
					if(ulp->count>dots)//�ҳ�����Ŵ�
					{
					dots=ulp->count;
					lq=ulp->sign;
					}
			}
		}
		if(k==3)
		{
			if(ulp->Xmin<=i)
			{
					if(ulp->count>dots)//�ҳ�����Ŵ�
					{
					dots=ulp->count;
					lq=ulp->sign;

					}
			}
		}
		ulp=ulp->next;
	}
	ulp=(*up)->next;//��һ�η��Ѻϲ� ���Ŵز��� С�Ŵ����෴�����ƶ�һ����Ԫ��
	while(ulp)
	{
		if(k==1)
		{
			if(ulp->Zmin<=i)
			{
					if(ulp->sign!=lq)//��������Ŵ�
					{
					p=ulp->head;
					while(p!=NULL)
					{
					Cube[p->x][p->y][p->z]=0;
					(p->z)+=1;//�ϲ�
					p=p->next;
					}
					}
			}
		}
		if(k==2)
		{
			if(ulp->Ymin<=i)
			{

					if(ulp->sign!=lq)//��������Ŵ�
				{
						p=ulp->head;
						while(p)
						{
							Cube[p->x][p->y][p->z]=0;
							(p->y)+=1;//�ϲ�
							p=p->next;
						}
					}
			}
		}
		if(k==3)
		{
			if(ulp->Xmin<=i)
			{
					if(ulp->sign!=lq)//��������Ŵ�
					{
					p=ulp->head;
					while(p)
					{
					Cube[p->x][p->y][p->z]=0;
					(p->x)+=1;//�ϲ�
					p=p->next;
					}
					}
			}
		}
		ulp=ulp->next;
	}

	LinkList ulp2;
	ulp2=(*up)->next;
	while(ulp2)
	{
		Node p2=ulp2->head;
		while(p2)
		{
		Cube[p2->x][p2->y][p2->z]=noview;
		p2=p2->next;
		}
		ulp2=ulp2->next;
	}
	(*up)->next=NULL;
	for(x=0;x<l;x++)
	{
		for(y=0;y<l;y++)
		{
			for(z=0;z<l;z++)
			{
				if(Cube[x][y][z]==noview)//δ���ʣ������Ŵ�
				{
					ucount=0;
					lp=(LinkList)malloc(sizeof(Lgroup));
					lp->sign=n;lp->next=NULL;
					p=(Node)malloc(sizeof(Lnode));
					p->x=x;p->y=y;p->z=z;p->sign=n;
					p->next=NULL;
					lp->head=p;
					View(Cube,x,y,z,&lp);//������������ؽ��
					for(x1=0;x1<l;x1++)
					{
						for(y1=0;y1<l;y1++)
							{
							for(z1=0;z1<l;z1++)
								{
									if(Cube[x1][y1][z1]==view)
									{
										Cube[x1][y1][z1]=n;
										ucount++;
									}
								}
							}
					}
					minmax(&lp);
					lp->count=ucount;
					lp->next=(*up)->next;
					(*up)->next=lp;
					n++;
				}
			}
		}
	}
	if(n-1!=2)
	{
	initcube_2(Cube);
	ReadFile(Cube,"01.txt");
	}
	return 1;
}
int unionlist_2(LinkList *up,cubex Cube,int i,int k)				//���Ѻ���֮�ϲ� ����ײ�ͻ�ۣ�
{
	int ucount,groupNum;
	int init_sign=(*up)->sign;            //��һ��
	(*up)->next=NULL;
	int dots=0;													//���ڴ洢����Ŵؽ����
	int n=1;
	LinkList lp;Node p;
	int x,y,z,x1,y1,z1;
	LinkList ulp1=(*up);
	groupNum=count_group_by_list_2(up,Cube);
	if(groupNum==2)
	{
		return 1;
	}
	LinkList ulp;
	int lq=0;
	ulp=(LinkList)malloc(sizeof(Lgroup));
	ulp=(*up)->next;                 //up������Ŵر���
	while(ulp!=NULL)
	{
		if(k==1)
		{
			if(ulp->Zmax<i)
			{
					if(ulp->count>dots)//�ҳ�����Ŵ�
					{
						dots=ulp->count;
						lq=ulp->sign;
					}
			}
		}
		else if(k==2)
		{
			if(ulp->Ymax<i)
			{
					if(ulp->count>dots)//�ҳ�����Ŵ�
					{
					dots=ulp->count;
					lq=ulp->sign;
					}
			}
		}
		else
		{
			if(ulp->Xmax<i)
			{
					if(ulp->count>dots)//�ҳ�����Ŵ�
					{
					dots=ulp->count;
					lq=ulp->sign;
					}
			}
		}
		ulp=ulp->next;
	}
	ulp=(*up)->next;
	while(ulp!=NULL)
	{
		if(k==1)
		{
			if(ulp->Zmax<i)
			{
					if(ulp->sign!=lq)//��������Ŵ�
					{
					Node p=ulp->head;
					while(p!=NULL)
					{
					Cube[p->x][p->y][p->z]=0;//�ϲ�
					(p->z)+=1;
					p=p->next;
					}
					}
			}
		}
		if(k==2)
		{
			if(ulp->Ymax<i)
			{
					if(ulp->sign!=lq)//��������Ŵ�
					{
					Node p=ulp->head;
					while(p!=NULL)
					{
					Cube[p->x][p->y][p->z]=0;//�ϲ�
					(p->y)+=1;
					p=p->next;
					}
					}
			}
		}
		if(k==3)
		{
			if(ulp->Xmax<i)
			{
					if(ulp->sign!=lq)//��������Ŵ�
					{
					Node p=ulp->head;
					while(p!=NULL)
					{
					Cube[p->x][p->y][p->z]=0;//�ϲ�
					(p->x)+=1;
					p=p->next;
					}
					}
			}
		}
		ulp=ulp->next;
	} 								//������
	ulp=(*up)->next;
	while(ulp!=NULL)
	{
		Node p1=ulp->head;
		while(p1!=NULL)
		{
		Cube[p1->x][p1->y][p1->z]=noview;
		p1=p1->next;
		}
		ulp=ulp->next;
	}								//���Ĳ�
	(*up)->next=NULL;
	countgroup(Cube,up);
	lq=0;//         ������
	dots=0;
	ulp=(*up)->next;
	while(ulp!=NULL)
	{
		if(k==1)
		{
			if(ulp->Zmax>=i)
			{
					if(ulp->count>dots)//�ҳ�����Ŵ�
					{
						dots=ulp->count;
						lq=ulp->sign;
					}
			}
		}
		if(k==2)
		{
			if(ulp->Ymax>=i)
			{
					if(ulp->count>dots)//�ҳ�����Ŵ�
					{
					dots=ulp->count;
					lq=ulp->sign;
					}
			}
		}
		if(k==3)
		{
			if(ulp->Xmax>=i)
			{
					if(ulp->count>dots)//�ҳ�����Ŵ�
					{
					dots=ulp->count;
					lq=ulp->sign;

					}
			}
		}
		ulp=ulp->next;
	}
	ulp=(*up)->next;//��һ�η��Ѻϲ� ���Ŵز��� С�Ŵ����෴�����ƶ�һ����Ԫ��
	while(ulp!=NULL)
	{
		if(k==1)
		{
			if(ulp->Zmax>=i)
			{
					if(ulp->sign!=lq)//��������Ŵ�
					{
					Node p=ulp->head;
					while(p!=NULL)
					{
					Cube[p->x][p->y][p->z]=0;
					(p->z)-=1;//�ϲ�
					p=p->next;
					}
					}
			}
		}
		if(k==2)
		{
			if(ulp->Ymax>=i)
			{

					if(ulp->sign!=lq)//��������Ŵ�
				{
						Node p2;
						p2=ulp->head;
						while(p2)
						{
							Cube[p2->x][p2->y][p2->z]=0;
							(p2->y)-=1;//�ϲ�
							p2=p2->next;
						}
					}
			}
		}
		if(k==3)
		{
			if(ulp->Xmax>=i)
			{
					if(ulp->sign!=lq)//��������Ŵ�
					{
					Node p3=ulp->head;
					while(p3!=NULL)
					{
					Cube[p3->x][p3->y][p3->z]=0;
					(p3->x)-=1;//�ϲ�
					p3=p3->next;
					}
					}
			}
		}
		ulp=ulp->next;
	}
	ulp=(*up)->next;

	while(ulp!=NULL)
	{
		Node p1=ulp->head;
		while(p1!=NULL)
		{
		Cube[p1->x][p1->y][p1->z]=noview;
		p1=p1->next;
		}
		ulp=ulp->next;
	}
	(*up)->next=NULL;
	n=1;
	for(x=0;x<l;x++)
	{
		for(y=0;y<l;y++)
		{
			for(z=0;z<l;z++)
			{
				if(Cube[x][y][z]==noview)//δ���ʣ������Ŵ�
				{
					Node p;
					ucount=0;
					lp=(LinkList)malloc(sizeof(Lgroup));
					lp->sign=n;
					p=(Node)malloc(sizeof(Lnode));
					p->x=x;p->y=y;p->z=z;p->sign=n;
					p->next=NULL;
					lp->head=p;
					View(Cube,x,y,z,&lp);//������������ؽ��
					for(x1=0;x1<l;x1++)
					{
						for(y1=0;y1<l;y1++)
							{
							for(z1=0;z1<l;z1++)
								{
									if(Cube[x1][y1][z1]==view)
									{
										Cube[x1][y1][z1]=n;
										ucount++;
									}
								}
							}
					}
					minmax(&lp);
					lp->count=ucount;
					lp->next=(*up)->next;
					(*up)->next=lp;
					n++;
				}
			}
		}
	}//
	if(n-1!=2)
	{
	initcube_2(Cube);
	ReadFile(Cube,"01.txt");
	}
	return 1;
}
int sub_divide(LinkList *L,LinkList *p,cubex Cube)			//�ӷ��Ѻ���
{
	int i,k;
	int *k1=&k;
	k=random();//k��ʾ���ѷ���
	i=locate(*p,k,k1);
	k=(*k1);
	if(split(L,p,Cube,i,k))
	{
		if(unionlist(p,Cube,i,k))
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else if(split(L,p,Cube,i,k)==-1)
	{
		return 0;
	}
	else if(split_2(L,p,Cube,i,k))
	{
		if(unionlist_2(p,Cube,i,k))
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else if(split_2(L,p,Cube,i,k)==-1)
	{
		return 0;
	}
	else
	{
		return 0;
	}
}
void divide(cubex cube,LinkList *L)	//�ܷ��Ѻ���
{
		LinkList p;
		p=(LinkList)malloc(sizeof(Lgroup));
		while((*L)->size<=2160)
		{
		p=choose(*L);//ѡ��ɷ��ѵ��Ŵأ��Ա�����ѡ����
		if(sub_divide(L,&p,cube))
		{
		write_file1(cube);
		initcube_1(cube);
		(*L)->next=NULL;
		system("cls");
		printf("�Ŵ�����:%d\n",(*L)->size);
		countgroup(cube,L);
		}
		else
		{
			continue;
		}
		}
		printf("�������!\n");
		countgroup(cube,L);
}
int main()
{
	LinkList L;
	char *filename="break_init_1.txt";//"01.txt";//
	cubex Cube;
	Cube=initcube(l,l,l);
	ReadFile(Cube,filename);
	L=(LinkList)malloc(sizeof(Lgroup));
	L->next=NULL;
	countgroup(Cube,&L);
	divide(Cube,&L);
	system("pause");
}
