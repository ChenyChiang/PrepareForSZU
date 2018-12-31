#include<cstdio>
#include<cstdlib>
#include<cmath>
bool zhishu(int n)//判断是否为素数
{
	int i;
	int k=(int)sqrt( (double)n );
	for(i=2;i<=k;i++)
	{
		if(n%i==0) break;
	}
	if(i>k)
		return true;
	else 
		return false;
}
int main(){
	int buff[20000];
	int i,c=0,cout=0;
	FILE *fp,*fp1;//定义读入文件指针fp，和写出文件指针fp1
	if((fp=fopen("F:\\test20000.txt","r+"))==NULL) exit(0);
	for(i=0;i<20000;i++)//读入文本文件
		fscanf(fp,"%d ",&buff[i]);
	/*for(i=0;i<100;i++)if(zhishu(buff[i])) cout++;
	printf("%d\n",cout);
	for(i=0;i<100;i++){
		if(zhishu(buff[i]))
		{		
			printf("%d ",buff[i]);
			c++;
			if(c%5==0)printf("\n");
		}

	}*/
	fclose(fp);
	if((fp1=fopen("F:\\result20000.txt","w+"))==NULL) exit(0);
	for(i=0;i<20000;i++)if(zhishu(buff[i])) cout++;
	fprintf(fp1,"%d\n",cout);//写出个数
	for(i=0;i<20000;i++)
	{
		if(zhishu(buff[i]))
		{		
			fprintf(fp1,"%d ",buff[i]);//写出文本文件
			c++;
			if(c%5==0)fprintf(fp1,"\n");
		}

	}

}
