2、此文件中按文本方式存放了一段其他文章，其中有若干长度小于15的英文单词，
单词之间用空格分开，无其他符号。
3、顺序读取这段文章的不同的单词（大小写敏感），
同时在读取的过程中排除所有的单词THE以及变形，即这些单词不能出现在读取的结果中。
4、将读取的所有单词的首字母转大写后，输出D根目录下new.txt，每个单词一行。*/
//2019-1-12 19:30
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
typedef struct LNode
{
	struct LNode *next;
	char str1[15];
}LNode;
void print(LNode *L)
{
	LNode *p;
	p=L->next;
	while(p!=NULL)
	{
	printf("%s ",p->str1);
	p=p->next;
	}
	
}
void process(char *str)
{
	FILE *fp;
	fp=fopen("new.txt","w+");
	if(fp==NULL)
	{
		perror("fopen err");
		exit(0);
	}
	int i=0;
	while(str[i]!='\0')
	{
		int j=i;
		while(str[j]!=' '&&str[j]!='\0')
		{
			if((str[j]=='t'&&str[j+1]=='h'&&str[j+2]=='e')||(str[j]=='T'&&str[j+1]=='h'&&str[j+2]=='e'))
			j=j+3;
			else
				fprintf(fp,"%c",str[j]);
		    j++;
		}
			
		fprintf(fp,"\n");
		i=j+1;
	}

	fclose(fp);
	fp=NULL;
}
void readfile(char *str)
{
	FILE *fp;
	fp=fopen("org.dat","rb");
	if(fp==NULL)
	{
		perror("fopen err");
		exit(0);
	}
	fseek(fp,0,SEEK_END);
	unsigned long size=ftell(fp);
	rewind(fp);
	str=(char*)malloc(sizeof(char)*size);
	memset(str,0,size+1);
	fread(str,1,size,fp);
	int i=0,j=0;
	char *ess=(char*)malloc(sizeof(char)*size);
	memset(ess,0,size+1);
	while(str[i]!='\0')
	{
		if(str[i]>='a'&&str[i]<='z'||str[i]>='A'&&str[i]<='Z')
			ess[j++]=str[i];
		if(str[i]==' ')
			ess[j++]=' ';
		i++;
	}
	ess[j]='\0';
	puts(ess);
	process(ess);
	fclose(fp);
	fp=NULL;
}

int main()
{
	char *buff=NULL;
	readfile(buff);
	return 0;
}
