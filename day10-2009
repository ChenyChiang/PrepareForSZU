/*
2009年
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
#include<ctype.h>
char *buff;
int charToDec(char *num)//进制转换
{
	if(*num == '0') // 处理八进制
	{
		// base代表采的进制方式
		return strtol(num, NULL, 8);//参数num字符串转换成8进制长整型数,
	}
	return atoi(num);
}
void sort(int a[],int n)
{
	int i,j;int flag=1;
	for(i=0;i<n;i++)
	{
		for(j=n-1;j>i;j--)
			if(a[j-1]<a[j]){
			flag=0;
			int temp=a[j-1];
			a[j-1]=a[j];
			a[j]=temp;
			}
		if(flag==1)break;

	}
}
void writefile(int a[],int sum)
{
	FILE *wfp;
	if((wfp=fopen("new.txt","w"))==NULL)
	{
		perror("fopen err");
		exit(0);
	}
		for(int in=0;in<sum;in++)
	{
		if(a[in]!=0)
		{fprintf(wfp,"%d\n",a[in]);}
       
	}	fclose(wfp);
	wfp=NULL;

}
void isnum()
{
	int i,j,k=0,n=0,a=0;
	char num[15]={0};
	int res[20]={0};
	for(i=0;i<strlen(buff);i++)
	{
		if(buff[i]>='0'&&buff[i]<='9')
		{
			for(j=i;(buff[j]>='0'&&buff[j]<='9');j++)
			{
				n++;//统计每个数字位数
				num[k++]=buff[j];			
			}
			num[n]='\0';//puts(num);
			
			res[a++]=charToDec(num);
			
			i=i+n-1;
			n=0;
			k=0;
		}
	}
	int sum=0;
	for(int in=0;in<sizeof(num);in++)
	{
		if(res[in]!=0)
		{sum++;}
       
	}
	sort(res,sum);
	writefile(res,sum);
	
}

void readFile()
{
	FILE *rfp;
	if((rfp=fopen("org.dat","rb"))==NULL)
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
	/*char *string, *stopstring;
    double x;
    int base;
    long l;
    unsigned long ul;
    string = "042ss";
    printf("string = %s\n", string);
    ul = strtoul(string, &stopstring, 8);
    printf("strtol = %ld(base %d)\n", ul, 8);
	printf("Stopped scan at: %s\n", stopstring);*/
	return 0;
}
