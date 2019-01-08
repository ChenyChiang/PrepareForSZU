#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>
typedef struct point{
	int x;
	int y;
}Point;
typedef struct Lnode{
	Point point;
	struct Lnode *next;
}Lnode;
Point point[100];
void BubbleSort(Lnode *head)
{
	Lnode *p,*q;
	for(p = head->next; p != NULL; p = p -> next)
	{
		for(q = p -> next; q != NULL; q = q -> next)
		{
			if((p ->point.x) > (q -> point.x))
			{
				int tmp = q -> point.x;
				q -> point.x= p -> point.x;
				p ->  point.x = tmp;
			}
		}
	}
}
void readfile()
{
	FILE *fp;
	if((fp=fopen("F:\\test.dat","rb"))==NULL)
	{
		perror("fopen err");
		exit(0);
	}
	fseek (fp , 0 , SEEK_END);       
	long lSize = ftell (fp); //返回字节数 
	rewind (fp); 
	//开辟存储空间
	int num = lSize/sizeof(int);//字节数除以单个大小=个数
	printf("文件点的个数为%d\n",num);
	int *pos = (int*) malloc (sizeof(int)*num);  //开辟num个空间
	if (pos == NULL)  
	{  
		printf("malloc err");   
		exit(0);
	} 
	fread(pos,sizeof(int),num,fp);//读取文件

	int cout=0;//计算有效点个数
	for(int i = 0; i < num-1; i++)
		if(pos[i]>0&&pos[i+1]>0) cout++;
	printf("有效点的个数为%d\n",cout);	

	Lnode *L=(Lnode*)malloc(sizeof(Lnode));
	L->next=NULL;
	for(int i = 0; i < num-1; i++)
	{
		if(pos[i]>0&&pos[i+1]>0) 
		{
			Lnode *s=(Lnode*)malloc(sizeof(Lnode));
			s->point.x=pos[i];
			s->point.y=pos[i+1];
			s->next=L->next;
			L->next=s;

		}
	}
	print(L);
	BubbleSort(L);
	
	printf("最小公共区域面积为%d\n:",L->next->point.x*L->next->point.y);
	printf("问题(3)的点为:(%d,%d)\n",L->next->point.x,L->next->point.y);
	printf("问题(4)的分组为:\n");
	print(L);
	free(pos);     //释放内存
	fclose(fp);
	fp=NULL;
}

int main()
{
	readfile();
	return 0;
}
