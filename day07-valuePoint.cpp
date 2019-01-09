/*从服务器上下载数据文件org.dat文件以二进制方式存放一系列整数，每个整数占4个字节。
从第一个整数开始，第一个整数和第二个整数构成一个坐标点，以此类推，数据文件中保存了许多坐标点数据。
问题1：规定处于第一象限的坐标点为有效点，请问数据文件中所有点的个数n为多少？有效点的个数k为多少？
问题2：每个有效点与坐标原点构成一个的矩形，请问k个有效点与坐标原点构成的k个矩形的最小公共区域面积为多少？
问题3：寻找有效点钟符合下列条件的点：以该点为坐标原点，其它有效点仍然是有效点即处于第一象限（不包括坐标轴上的点）输出这些点。
问题4：对所有有效点进行分组，每个有效点有且只有属于一个分组，分组内的点符合下列规则：
若对组内所有点的x坐标进行排序，点p1(x1,y1)在点p2(x2,y2)后面，即x1>x2那么y1>y2，请输出所有的分组?
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>
typedef struct point{
	int x;
	int y;
	int group;
}Point;
typedef struct Lnode{
	Point point;
	struct Lnode *next;
}Lnode;
Point point[100];
int *pos;
Lnode *L;
int num;
void print(Lnode *l)
{
	Lnode *p=l->next;
	while(p!=NULL)
	{
		printf("(%d,%d)\n",p->point.x,p->point.y);
		p=p->next;
	}

}
//冒泡排序
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
        num = lSize/sizeof(int);//字节数除以单个大小=个数
	printf("文件点的个数为%d\n",num);
	pos = (int*) malloc (sizeof(int)*num);  //开辟num个空间
	
	if (pos == NULL)  
	{  
		printf("malloc err");   
		exit(0);
	} 
	fread(pos,sizeof(int),num,fp);//读取文件
	fclose(fp);
	fp=NULL;
}
void valuepoint()
{
	int cout=0;//计算有效点个数
	for(int i = 0; i <num-1; i++)
		if(pos[i]>0&&pos[i+1]>0) cout++;
	printf("有效点的个数为%d\n",cout);	

	L=(Lnode*)malloc(sizeof(Lnode));
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
	//BubbleSort(L)
}
void minarea(Lnode *linkList)
{
	int minX, minY;
	int area;
	Lnode *p;
	p = linkList->next;
	minX = p->point.x;
	minY = p->point.y;

	while(p != NULL)
	{
		if(minX > p->point.x) minX = p->point.x;
		if(minY > p->point.y) minY = p->point.y;
		p = p->next;
	}

	area = minX * minY;
	printf("最小面积是:%d\n", area);
}
void recountPoint(Lnode *linkList)
{
	Lnode *p;
	Lnode *q;

	p = linkList->next;
	q = linkList->next;

	while(p != NULL)
	{
		while(q != NULL)
		{
			if(p != q)
			{
				if(!(q->point.x > p->point.x && q->point.y > p->point.y))
				{
					break;
				}
			}
			q = q->next;
		}

		if(q == NULL)
		{
			printf("新的有效点是(%d, %d)\n", p->point.x, p->point.y);
		}
		else{printf(" no  new point\n");break;}
			
		 // q回头
        q = linkList->next;
		p = p->next;
	}
}
void divideGroup(Lnode *linkList)
{
	Lnode *p;
	Lnode *q;
	Lnode *s;
	int i;

	// 按x排序
	BubbleSort(linkList);

    for (p = linkList->next, p->point.group = 0, i = 0; p != NULL; p = p->next, i++)
    {
        for (q = p->next; q != NULL; q = q->next)
        {
            // 如果横坐标不同，且纵坐标小于（也就是满足x1>x2,y1>y2,(x1, y1)在(x2, y2)后面）
            if (q->point.x != p->point.x && q->point.y > p->point.y)
            {
                q->point.group = p->point.group;
            } 
			else 
			{               
                q->point.group = p->point.group + 1;
            }
        }
    }
	s = linkList->next;
    while (s != NULL) 
	{
        printf("(%d, %d)属于第%d组\n", s->point.x, s->point.y, s->point.group + 1);
        s= s->next;
    }
}

int main()
{
	readfile();
	valuepoint();//有效点
	minarea(L);//最小面积
	recountPoint(L);//最新有效点
	divideGroup(L);//分组
	return 0;
}
