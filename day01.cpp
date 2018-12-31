#include<stdio.h>
#include<time.h>
#include<stdlib.h>
int main()
{
	FILE *fp;
	if((fp=fopen("F:\\test20000.txt","w"))==NULL)
		exit(0);
	srand((int)time(0));
	int i,j;
	for(i=0;i<20000;i++)
	{
		j=rand()%1000+1;
		fprintf(fp,"%d ",j);
	}
	fclose(fp);
}
