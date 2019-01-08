#include<stdio.h>
#include<stdlib.h>
#include<time.h>
void produceNum()
{
	FILE *fp;
	if((fp=fopen("F:\\test.dat","wb"))==NULL)
	{
		perror("fopen err");	exit(0);
	}
	srand((int)time(0));
	int i,j;
  int pos[100];
	for(i=0;i<100;i++)
	{
		pos[i]=rand()%200+1-100;//生成100个随机数(-100~100)存入数组POS
	}
	
	
	for(int i = 0; i < 100; i++)
			fwrite(&pos[i],sizeof(int),1,fp);//将POS数组写入文件fp

	fclose(fp);
	fp=NULL;
}
int main()
{
	  produceNum();
}
