void decode()
{
	unsigned char cip1='1';//八位无符号整数1
	unsigned char cip2='2';//八位无符号整数2
	FILE *fp,*wfp;
	if((fp=fopen(wPath2,"r+"))==NULL)
	{
		perror("fopen err");
		exit(0);
	}
	if((wfp=fopen(wPath3,"w+"))==NULL)
	{
		perror("fopen err");
		exit(0);
	}
	fseek(fp,0,SEEK_END);
	unsigned int size=ftell(fp);//返回size字节长度
	rewind(fp);
	char *buff=(char*)malloc(size);
	memset(buff,0,size);
	fgets(buff,size+1,fp);
	fclose(fp);
	fp=NULL;
	int i,j;
	for(i=0,j=1;i<size-1;i++,j++)
	{
		buff[i]=buff[i]^cip1;
		buff[j]=buff[j]^cip2;
	}
	puts("解密字符为:");
	puts(buff);
	fputs(buff,wfp);
	fclose(wfp);
	wfp=NULL;
}
