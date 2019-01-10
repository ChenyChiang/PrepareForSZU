/*
2010年
1、FTP上下载make.exe和org.dat，运行make.exe输入准考证后三位生成
data.txt，文件为二进制编码。
2、data.txt内存有2048个整数，其中前n个为非0数，后2048-n个数为0，
将其读入数组，计算非零数的个数n。
3、选出n个数中的最大数&最小数。
4、选出n个数中最大素数。
5、将n个数从大到小排序，并平均分成三段(若n非3的整数倍，则不考虑最后的1-2个数)，
选出中间段的最大数和最小数。
*/
//2019-01-10 22:40
//Haosion
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
//#define rPath "F:/data.txt"
int num[2048];
void trans()
{
	for(int i=0;i<2048;i++)
	{
		int s=0;
		int k=0;
		while(num[i])
		{
			s=s+pow(2.0,k)*(num[i]%10);
			k++;
			num[i]=num[i]/10;
		}
		num[i]=s;

	}
	/*for(int i=0;i<2048;i++)
		printf("%d ",num[i]);
	printf("\n");*/
}
void readFile()
{
	FILE *rfp;
	if((rfp=fopen("bindata.txt","rb"))==NULL)
	{
		perror("fopen err");exit(0);
	}
	char str[10];
	for(int i=0;i<2048;i++)
	{
		fscanf(rfp,"%d ",&num[i]);
		//printf("%d ",num[i]);
	}
	trans();
}
int notzero()//计算非0个数
{
	int cout=0;
	for(int i=0;i<2048;i++)
	{
		if(num[i]!=0)cout++;
		else break;
	}
	printf("非0个数为%d\n",cout);
	return cout;
}
void getmaxmin(int n)
{
	int max=num[0];
	int min=num[0];
	for(int i=0;i<n;i++)
	{
		if(num[i]>max) max=num[i];
		if(num[i]<min) min=num[i];
	}
	printf("最大值为%d,最小值为%d\n",max,min);
}
int isprime(int n)
{
	int i;
	int k=(int)sqrt((double)n);
	for(i=2;i<=k;i++)
		if(n%i==0) break;
	if(i>k)
		return 1;
	else return 0;
}
void maxprim(int n)
{
	int cout=0;
	for(int i=0;i<n;i++)
	{
		if(isprime(num[i]))cout++;
	}
	int j=0;
	int *buf=(int*)malloc(sizeof(int)*cout);
	for(int i=0;i<n;i++)
	{
		if(isprime(num[i]))
			buf[j++]=num[i];
	}
	int max=buf[0];
	for(int i=0;i<cout;i++)
	{
		if(buf[i]>max) max=buf[i];
	
	}
	printf("最大素数为%d\n",max);

}
void sortgroup(int n)
{
	int i,j;
	int flag=1;
	for(i=0;i<n-1;i++)
	{
		for(j=n-1;j>i;j--)
		{
			if(num[j-1]<num[j])
			{
				flag=0;
				int temp=num[j-1];
				num[j-1]=num[j];
				num[j]=temp;
				
			}
		
		}	if(flag==1)break;
	}
	/*for(i=0;i<n;i++)
		printf("%d ",num[i]);*/
	int mid1,mid2;
	mid1=n/3-1;
	mid2=n/3*2-1;
	int max=num[mid1+1];
	int min=num[mid1+1];
	for(i=mid1+1;i<=mid2;i++)
		{if(num[i]>max) max=num[i];
		if(num[i]<min) min=num[i];
	}
	printf("中间组的最大值为%d,最小值为%d\n",max,min);
}
int main()
{
	int numbers;
	readFile();
	numbers=notzero();//计算非0个数
	getmaxmin(numbers);//选出n个数中的最大数&最小数。
	maxprim(numbers);//最大素数
	sortgroup(numbers);//排序分组
	return 0;
}
