/*
1、从网页上下载input.dat文件，里面是用二进制编写的，里面放了一堆int型的数，每个数占4个字节，每次读取两个，这两个数构成一个坐标。
（1）规定处于第一象限的数是有效点，（即x>0,y>0的坐标），问这么多点中有效点有多少个？
（2）从键盘上输入k和n，从第一问中的有效点中找出距离小于n，距离小于n的点的个数要大于k，将它们以文本格式输出到文件中。
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define RPATH "D:/test/input2015.data"
#define WPATH "D:/test/output2015.txt"

typedef struct Point
{
	int locX;
	int locY;
}Point;

typedef struct LinkList
{
	Point point;
	struct LinkList *next;
}LNode;

int isFirstPoint(Point point)//判断满足第一象限
{
	if(point.locX > 0 && point.locY > 0)
		return 1;
	return 0;
}

void countFirstPiont(LNode *linkList)
{
	LNode *p =linkList;// 链表初始化
	LNode *tmpNode;
	LNode *q;
		
	FILE *rFp;//文件指针初始化
	rFp = fopen(RPATH, "rb");
	if(rFp == NULL)
	{
		perror("read file fopen err:");
		exit(0);
	}


  int tmpNum[2]; // 每次读取的两个数
	while(1)
	{
		Point tmpP;
		unsigned int len = fread(tmpNum, sizeof(tmpNum), 1, rFp);
		if(len == 0)
			break;	
		tmpP.locX = tmpNum[0];
		tmpP.locY = tmpNum[1];

		if(!isFirstPoint(tmpP))
		{
			continue;
		}

		tmpNode = (LNode *)malloc(sizeof(LNode));
		tmpNode->next = NULL;
		tmpNode->point = tmpP;

		p->next = tmpNode;
		p = p->next;
	}

	fclose(rFp);
	rFp = NULL;

	q = linkList->next;
	while(q != NULL)
	{
		printf("(%d, %d)\n", q->point.locX, q->point.locY);
		q = q->next;
	}
}
//判断距离小于N的点
int lessthanN(Point aPoint, Point bPoint, int n)
{
    double distance = sqrt(pow(double(aPoint.locX - bPoint.locX), 2) + pow(double(aPoint.locY - bPoint.locY), 2));
    
    if (distance < n) {
        return 1;
    }
    return 0;
}

//计算满足k和n的点
void countDistanceKN(LNode *linkList)
{
	int k, n;
	FILE *wFp;// 打开写文件
	wFp = fopen(WPATH, "wb");
	if(wFp == NULL)
	{
		perror("write file fopen err:");
		exit(1);
	}
	LNode *q;
	LNode *p;
	printf("请输入k和n:");//从键盘上输入k和n，从第一问中的有效点中找出距离小于n，距离小于n的点的个数要大于k，将它们以文本格式输出到文件中。
	scanf("%d%d", &k, &n);
	for(p = linkList->next; p != NULL; p = p->next)
	{
		int count = 0;
		char buf[20];
		memset(buf, 0, sizeof(buf));
		for(q = linkList->next; q != NULL; q = q->next)
		{
			
			if(p == q) continue;

			if(lessthanN(p->point, q->point, n))
			{
				count++;
			}
		}

		if(count > k) // 大于k就输出,.......输出所有pq距离小于n的点.
		{
			printf("(%d, %d):%d\n", p->point.locX, p->point.locY, count);
			sprintf(buf, "(%d, %d):%d\r\n", p->point.locX, p->point.locY, count);
			fputs(buf, wFp);
		}
	}

	fclose(wFp);
	wFp = NULL;
}

int main()
{
	LNode *linkList;

	// 链表初始化
	linkList = (LNode *)malloc(sizeof(LNode));
	linkList->next = NULL;

	printf("----------算有效点开始-----------\n");
	// 算有效点
	countFirstPiont(linkList);

	printf("----------算满足k和n的点开始-----------\n");

	countDistanceKN(linkList);
	return 0;
}
