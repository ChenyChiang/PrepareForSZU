/*2008年
2、此文件中按文本方式存放了一段其他文章，其中有若干长度小于15的英文单词，
单词之间用空格分开，无其他符号。
3、顺序读取这段文章的不同的单词（大小写敏感），
同时在读取的过程中排除所有的单词THE以及变形，即这些单词不能出现在读取的结果中。
4、将读取的所有单词的首字母转大写后，输出D根目录下new.txt，每个单词一行。*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
typedef struct LNode
{
	struct LNode *next;
	char ch[15];
}LNode;
void print(LNode *L)
{
	LNode *p=L->next;
	while(p!=NULL)
	{
		printf("%s\n", p->ch);
	
		p=p->next;
	}

}
void writeFile(LNode *L)
{
	FILE *fp;
	fp=fopen("new.txt","w+");
	if(fp==NULL)
	{
		perror("fopen err");
		exit(0);
	}
	LNode *p=L->next;
	while(p!=NULL)
	{
		fprintf(fp,"%s\n", p->ch);
	
		p=p->next;
	}
}
void readFile(LNode *linkList)
{
	
	FILE *rFp = fopen("org.dat", "rb");
	
	if(rFp == NULL)
	{
		perror("read file fopen err:");
		exit(0);
	}
	/*fseek(rFp,0,SEEK_END);
	unsigned long size=ftell(rFp);
	rewind(rFp);
	char *str=(char*)malloc(sizeof(char)*size);
	memset(str,0,size+1);
	fread(str,1,size,rFp);
	puts(str);*/
    char ch;
	char word[15]={0};
	int i,j;
	LNode *p;
	p = linkList;
	while(1)
	{
		i = 0; // i初始化为0
		memset(word, 0, sizeof(word));
		ch = fgetc(rFp);
		if(feof(rFp))
		{
			break;
		}

		if(isalpha(ch)) // 如果是字母，就继续往下读，知道不是字母为止
		{
			int flag = 0;
			while(1)
			{
				*(word + i) = ch;

				ch = fgetc(rFp);
				if(isalpha(ch))
				{
					i++;
					continue;
				} 
				else
				{
					break;
				}
			}

			if(strcmp("THE", word) == 0 || strcmp("the", word) == 0 || strcmp("The", word) == 0)
			{ // 过滤掉the
				continue;			
			}
			else
			{
				LNode tmpWord;
				LNode *q;

				if(!isupper(word[0]))
				{
					word[0] = word[0] - 32;
		
				}
				strcpy(tmpWord.ch,word);
				 //判断之前有没有存
				for(q = linkList->next; q != NULL; q = q->next)
				{
					if(strcmp(q->ch, tmpWord.ch) == 0) // 已经存在了就不存了
					{
						break;
					}
				}

				if(q == NULL) // q走到了最后，说明不存在，新建一个节点
				{
					LNode *s = (LNode *)malloc(sizeof(LNode));	
					s->next=NULL;
					strcpy(s->ch, tmpWord.ch) ;
					p ->next = s;
					p = p->next;
				}
			}
		}
	}
	print(linkList);
}
int main()
{
	LNode *linkList;
	linkList = (LNode *)malloc(sizeof(LNode));
	linkList->next = NULL;
	readFile(linkList);
	writeFile(linkList);


}
