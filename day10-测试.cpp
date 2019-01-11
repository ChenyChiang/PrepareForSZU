/*
2009年上机复试题
1、用IE浏览器从FTP上下载org.dat，并保存在D盘的根目录下。
2、此文件中按文本方式存放了一段其他文章，其中有若干长度小于15的十
进制或八进制数字，数字之间用“,”分开，数字内部存在且仅存在空格。
3、八进制数以起始位“0”作为标示与十进制数区分。
4、顺序读取这些数字将他们转变为十进制数后按从大到小的顺序排序后，输
出到D盘根目录下new.txt，每个数字一行。
eg：_235_,34__2,_043_1_,1_3 分别是：十进制235，十进制342.，八进制431，十进制13。_代表空格
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#define MAX 15
char *buff;
int *res,index=0;
void toDecimal(int a[],int n)
{
	int i=0;
	for(i=n;i>=0;i--)
	{
		s=a[i]*pow(10,j)+
	}

}
void isnum()
{
	int i,j,k=0,n=0;
	int top=-1;
	int stack[MAX];
	int num[50][15]={0};//定义二维数组存数字
	for(i=0;i<strlen(buff);i++)
	{
		if(buff[i]>='0'&&buff[i]<='9')
		{
			for(j=i;(buff[j]>='0'&&buff[j]<='9');j++)
			{
				n++;//统计每个数字位数
				int a=buff[j]-'0';//转换为数字
				stack[++top]=a;
			
				printf("%d",a);

			
			}	
			toDecimal(stack,top);
			i=i+n-1;
			n=0;
			k=0;
			printf("\n");

		}
	}


}

void readFile()
{
	FILE *rfp;
	if((rfp=fopen("org.dat","r+"))==NULL)
	{
		perror("fopen err");
		exit(0);
	}
	fseek(rfp,0,SEEK_END);
	unsigned long size=ftell(rfp);
	rewind(rfp);
	buff=(char*)malloc(sizeof(char)*size);
	fgets(buff,size+1,rfp);
	//puts(buff);
	char str[15]={0};
	int j=0,k=0,i;
	for(i=0;i<strlen(buff);i++)//去空格
	{
		if(buff[i]!=' ')
		{
			buff[j++]=buff[i];
		}
	}
	buff[j]='\0';
	puts(buff);

	fclose(rfp);
	rfp=NULL;
}
int main()
{
	readFile(); 
	isnum();
	return 0;
}
