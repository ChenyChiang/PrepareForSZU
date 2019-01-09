void encode()
{
	unsigned char cip1='a';//八位无符号整数1
	unsigned char cip2='c';//八位无符号整数2
	FILE *fp,*wfp;
	if((fp=fopen(rPath,"r+"))==NULL)
	{
		perror("fopen err");
		exit(0);
	}
	if((wfp=fopen(wPath2,"w+"))==NULL)
	{
		perror("fopen err");
		exit(0);
	}
	fseek(fp,0,SEEK_END);
	unsigned int size=ftell(fp);//返回size字节长度
	//printf("%d\n",size);
	rewind(fp);
	char *buff=(char*)malloc(size);
	memset(buff,0,size);
	fgets(buff,size+1,fp);
	//fread(buff,1,size,fp);
	fclose(fp);
	fp=NULL;
	int i,j;
	for(i=0,j=1;i<size;i++,j++)
	{
		buff[i]=buff[i]^cip1;
		buff[j]=buff[j]^cip2;
		//printf("%c",buff[i]);
	}
	puts(buff);
	fputs(buff,wfp);
	fclose(wfp);
	wfp=NULL;
}
