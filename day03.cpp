#include<cstdio>
#include<cstdlib>
#include<cstring>
#include <ctype.h>
typedef struct Word
{
	char ch[20];//单词
	int count; // 频度
}Word;
typedef struct LNode//链表，由于单词个数未知使用链表
{
	struct LNode *next;
	Word word;
}LNode;
void writeFile(LNode *L)//写出结果文件
{
	FILE *wFp;
	LNode *p;
	char buf[35];
	wFp = fopen("out.txt", "wb");
	if(wFp == NULL)
	{
		perror("write file fopen err:");
		exit(1);
	}

	p = L->next;
	while(p != NULL)
	{
		memset(buf, 0, sizeof(buf));//初始化buff
		if(p->word.count > 5)       //次数大于5则输出
		{
			sprintf(buf, "%s:%d\r\n", p->word.ch, p->word.count);
			fputs(buf, wFp);
		}
		p = p->next;
	}

	// 关闭
	fclose(wFp);
	wFp = NULL;
}
//冒泡排序
void BubbleSort(LNode *head)
{
    LNode *p, *q;
    Word tmp;
    for(p = head->next; p != NULL; p = p -> next)
    {
        for(q = p -> next; q != NULL; q = q -> next)
        {
			if((p -> word.count) < (q -> word.count))
            {
                tmp = q -> word;
                q -> word = p -> word;
                p -> word = tmp;
            }
        }
    }
}
void countWord(LNode *linkList)
{
	FILE *rFp; // 读文件信息指针
	char ch;// 每次读取一个字符
	char strWord[20]; // 用于存储每次拼接单词
	int i; // 用于控制上面的word
	Word tmpWord; // 存储每次单词
	int flag; // 用于判断单词是否已经存在，0表示不存在，1表示存在

	// 链表
	LNode *p; // 控制链表的指针
	LNode *q;
	LNode *tmpNode; // 创建新节点用的

	rFp = fopen("input.txt", "rb");
	if(rFp == NULL)
	{
		perror("read file fopen err:");
		exit(0);
	}
	p = linkList;
	q = linkList;

	while(1)
	{
		// 每次读一个都要初始化变量
		i = 0;
		memset(strWord, 0, sizeof(strWord));
		ch = fgetc(rFp);
		if(feof(rFp)) // 读到结尾就跳出循环
		{
			break;
		}
		// 对字符进行判断，处理一个单词
		if(isalpha(ch)) // 如果是字母
		{
			// 再继续往下读
			while(1)
			{
				// 先将之前读的一个字母存起来
				*(strWord + i) = ch;
				// 再读一个
				ch = fgetc(rFp);
				if(isalpha(ch)) // 如果还是字母就继续读
				{
					i++;
					continue;
				}
				else break; // 不是		
			}

			// flag = 0;
			// 判断之前有没有存此单词
			while(p != NULL)
			{
				if(strcmp(strWord, p->word.ch) == 0)
				{
					p->word.count ++;
					flag = 1;
					break;
				}
				p = p->next;
			}
			if(p == NULL) // 用p是否移到了链尾来判断存在不存在,P为空，则该单词为新，创建结点，存入。
			{
				tmpWord.count = 1;
				strcpy(tmpWord.ch, strWord);

				tmpNode = (LNode *)malloc(sizeof(LNode));
				tmpNode->next = NULL;

				tmpNode->word = tmpWord;

				// 链接上链表
				q->next = tmpNode;
				q = q->next;
			}

			// 将p移到头节点
			p = linkList;
			
		}
	}

	// 关闭文件
	fclose(rFp);
	rFp = NULL;
}
int main()
{
	// 链表
	LNode *linkList;

	LNode *p;
	
	// 创建链表
	linkList = (LNode *)malloc(sizeof(LNode));
	linkList->next = NULL;

	// 算频度
	countWord(linkList);
	
	// 排序
	BubbleSort(linkList);
	
	// 写文件
	writeFile(linkList);

	p = linkList->next;
	while(p != NULL)
	{
		printf("%s:%d\n", p->word.ch, p->word.count);
		p = p->next;
	}
	return 0;
}
