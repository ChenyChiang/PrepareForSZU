/*2011
1、输出1000-9999中满足以下条件的所有数：
（1）该数是素数。
（2） 十位数和个位数组成的数是素数，百位数和个位数组成的数是素数。
（3）个位数和百位数组成的数是素数，个位数和十位数组成的数是素数。
*/
int prim(int n)
{
	int i;
	int k=(int)sqrt( (double)n );
	for(i=2;i<=k;i++)
	{
		if(n%i==0)
		{
			break;

		} 

	}
	if(i>k)
		return 1;

	else
		return 0;

}
void primeNum()
{
	FILE *fp;
	if((fp=fopen(wPath1,"w+"))==NULL)
	{
		perror("fopen err");
		exit(0);
	}
	int i;int cout=0;
	for(i=1000;i<9999;i++)
	{
		if(prim(i))
		{
			int k1=i%10;
			int k2=i/10%10;
			int k3=i/100;
			int num1=10*k2+k1;
			int num2=10*k3+k1;
			int num3=10*k1+k2;int num4=10*k1+k3;

			if(prim(num1)&&prim(num2)&&prim(num3)&&prim(num4))
			{
				cout++;
			}
		}
	}
	printf("满足条件的素数有%d个\n ",cout);
	fprintf(fp,"满足条件的素数有%d个\n ",cout);
	int line=0;
	for(i=1000;i<9999;i++)
	{
		if(prim(i))
		{
			int k1=i%10;
			int k2=i/10%10;
			int k3=i/100;
			int num1=10*k2+k1;
			int num2=10*k3+k1;
			int num3=10*k1+k2;int num4=10*k1+k3;

			if(prim(num1)&&prim(num2)&&prim(num3)&&prim(num4))
			{
				line++;
				printf("%d ",i);
				fprintf(fp,"%d ",i);	
				if(line%5==0)
				{	
					printf("\n");
					fprintf(fp,"\n");
				}

			}

		}

	}

}
