/*2007年上机复试题
把10到1000之间满足以下两个条件的数，存到result.txt文件中
1、是素数。
2、它的反数也是素数，如：123的反数是321。*/
//19-01-13 15:18
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
int prim(int n)
{
	int i;
	int k=(int)sqrt((double)n);
	for(i=2;i<=k;i++)
	{
		if(n%i==0) break;
	}
	if(i>k)return 1;
	else return 0;
}
int huiwen(int n)
{
	int i=0;
	int top=-1;int stack[4];
	while(n!=0)
	{
		stack[++top]=n%10;
		n=n/10;
	}
	int s=0;int k=0;
	while(top>=0)
	{
     s=s+stack[top--]*pow(10.0,k++);
	}
      
  //  printf("%d ",s);
	return s;
	
}
int main()
{
	
	FILE *fp;
	fp=fopen("result.txt","w+");
	if(fp==NULL)
	{
		perror("fopen err");
		exit(0);
	}
	for(int i=10;i<=1000;i++)
	{
		if(prim(i)&&prim(huiwen(i)))
		{
			printf("%d ",i);
			fprintf(fp,"%d ",i);
		}
			
	}
	fclose(fp);
	fp=NULL;
}
