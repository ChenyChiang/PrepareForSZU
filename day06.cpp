/**
 1、从网页上下载input.dat文件，里面是用二进制编写的，里面放了一堆int 型的数，每个数占4个字节，每次读取两个，这两个数构成一个坐标。
 （1）规定处于第一象限的数是有效点，（即x>0,y>0的坐标），问这么多点中有效点有多少个？
 （2）现在用户从键盘输入一个坐标和一个数字K，设计算法输出K个离该坐标距离最近的点的坐标和每个坐标到该点的距离，写入到output.txt文件中。
 */
#include<cstdio>
#include<cstdlib>
#include<cmath>
#define rPath "F:/input.dat"
#define wPath "F:/output.txt"
typedef struct point
{
	double x,y;
	double dis;
}Point;
typedef struct Lnode{
	Point point;
	struct Lnode *next;
}Lnode;
void readFile(Lnode *L)
{
	Lnode *p;
	p=L;
	FILE *fp;
	if((fp=fopen(rPath,"r+"))==NULL) exit(0);
	int tempRead[2];//临时存一次读取的数据
	Point tp;
	while(1)
	{
		unsigned int len=fread(tempRead,sizeof(tempRead),1,fp);
		if(len==0) break;
		tp.x=tempRead[0];tp.y=tempRead[1];
		if(tp.x>0&&tp.y>0)//符合第一象限条件,存储到链表
		{
			Lnode *s=(Lnode*)malloc((sizeof(Lnode)));
			s->point=tp;
			p->next=s;
			p=p->next;
		}
	}
	fclose(fp);
	//fp=NULL;
}
void printfirst(Lnode *L)//输出满足(1)问中点的坐标和个数
{
	int count=0;
	Lnode *q = L->next;
	while(q != NULL)
	{
		printf("(%d, %d)\n", q->point.x, q->point.y);
		count++;
		q = q->next;
	}
	printf("位于第一象限的点的个数为%d\n",count);
}
double countDis(Point p1,Point p2)
{
	double d=sqrt(pow((p1.x-p2.x),2)+pow((p1.y-p2.y),2));
	return d;
}
void Sort(Lnode *L){
	Lnode *p, *q;
    Point tmpP;
    for(p = L->next; p != NULL; p = p->next)
    {
        for(q = p->next; q != NULL; q = q->next)
        {
            if((p->point.dis) > (q->point.dis))
            {
                tmpP = q->point;
                q->point = p->point;
                p->point = tmpP;
            }
        }
    }
}
void writeFile(Lnode *L,int k){
	FILE *fp;
	Lnode *p;
	int i;
	char buf[40];
	if((fp=fopen(rPath,"wb"))==NULL) exit(0);

	// 算距离
	for(p = L->next, i = 0; p != NULL && i < k; p = p->next, i++)
	{
		sprintf(buf ,"(%d, %d):%.3lf\r\n", p->point.x, p->point.y, p->point.dis);
		fputs(buf, fp);
	}

	fclose(fp);
	fp = NULL;

}
void disPoint(Lnode *L)
{
	int x, y, k;
	Point tPoint;
	Lnode *p;
	
	printf("请输入坐标和k:");

	scanf("%d%d%d", &x, &y, &k);

	tPoint.x = x;
	tPoint.y = y;
	
	// 算距离
	for(p = L->next; p != NULL; p = p->next)
	{
		p->point.dis = countDis(tPoint, p->point);
	}

	// 排序
	Sort(L);

	//写出前k个
	writeFile(L, k);
}
int main()
{
  Lnode *L=(Lnode*)malloc((sizeof(Lnode)));
	L->next==NULL;
	readFile(L);
	printfirst(L);
	disPoint(L);
}
