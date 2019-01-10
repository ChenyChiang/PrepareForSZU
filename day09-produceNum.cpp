#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define MAX 10
int num[2048];
void binary(int a[],int n)//转换为二进制
{
	FILE *wfp1;
	if((wfp1=fopen("bindata.txt","wb"))==NULL)
	{
		perror("fopen err");
		exit(0);
	} 
	
	int i,j,k;
	int top=-1;
	int stack[MAX];//定义栈stack用于进制转换
	for(i=0;i<n;i++,top=-1)
	{
		if(a[i]==0)//若为0,则二进制不变
		{
			printf("0 ");
			fprintf(wfp1,"0 ");
		}
		while(a[i]!=0)//不为0,辗转相除,入栈
		{
			stack[++top]=a[i]%2;
			a[i]=a[i]/2;
		}
		for(j=top;j>=0;j--)//输出
		{
			
			fprintf(wfp1,"%d",stack[j]);	if(j==0)fprintf(wfp1," ");		
		}
		for(k=top;k>=0;k--)
		{
			printf("%d",stack[k]);
			if(k==0)printf(" ");
		}	
	}
	fclose(wfp1);
	wfp1=NULL;



}	
void produceNum()//随机生成2048个数
{
	FILE *wfp;
	if((wfp=fopen("data.txt","wb"))==NULL)
	{
		perror("fopen err");
		exit(0);
	} 
	srand((int)time(0));

	for(int i=0;i<1024;i++)
	{
		num[i]=rand()%200+1;
	}
	for(int i=1024;i<2048;i++)
	{
		num[i]=0;
	}
	for(int i=0;i<2048;i++)
	{
		fprintf(wfp,"%d ",num[i]);
	}
	fclose(wfp);
	wfp=NULL;

}

int main()
{
	//produceNum();
	FILE *rfp;
	if((rfp=fopen("data.txt","rb"))==NULL)
	{
		perror("fopen err");
		exit(0);
	}
	binary(num,2048);
	fclose(rfp);
	rfp=NULL;
	
}
