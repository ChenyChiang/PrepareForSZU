/*
2006年上机复试题
1、找出100到1000内的不含9的素数，存到result文件中。
*/
#include<stdlib.h>
#include<stdio.h>
#include<math.h>
int no_nine(int n)
{
	int i=0;
	int top=-1;
	int stack[4];
	while(n!=0)
	{
		if((n%10)!=9)
		{	
			stack[++top]=n%10;
			n=n/10;
		}
		else
		{
			top=-1;
			break;

		}
			
	}
	int s=0;int k=0;
	while(top>=0)
	{ 
		s=s+stack[top--]*pow(10.0,k++);
	}
	return s;
      
}
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
int main()
{
	FILE *fp;
	fp=fopen("result.txt","r+");
	if(fp==NULL)
	{
		perror("perror");
		exit(0);
	}
	int i;
	for(i=10;i<=1000;i++)
	{
		if(prim(i)&&no_nine(i))
		{
			printf("%d ",i);
			fprintf(fp,"%d ",i);
		}
	}
	fclose(fp);
	fp=NULL;
}
