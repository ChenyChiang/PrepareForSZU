#include<cstdio>
#include<cstdlib>
#include<cstring>
typedef struct Path{
	char ori[15];
	char dest[15];
}Path;
typedef struct Requst{
	Path path;
	int hop;
}Request;

int isRelated(char *,char* ,int ,Path*,int);
Path *tpaths;//全局变量
Request *tres;

int readInputfile()
{
	FILE *fp;
	if((fp=fopen("PathInput.txt","r+"))==NULL){ 
		perror("read file fopen err");
		exit(0);
	}
	fseek(fp,0L,SEEK_END);// 将光标停在文件的末尾
    long lSize= ftell (fp);//返回文件的大小（单位是bytes）
    fseek(fp,0L,SEEK_SET); /* 定位到文件开头 */
	char *buff =(char*) malloc(lSize+1);
	memset (buff,0,lSize);//初始化buff,否则屯屯屯,shit!windowssb平台下换行符为\r\n
	int number=lSize/sizeof(buff[0]);
	fread(buff,lSize,1,fp);//将数据读入到buff
	int n,i;
	const char *b="\n[, ]";
	sscanf(buff, "%d", &n);
	char *str = strtok(buff, b);//把数量读掉
	tpaths = (Path* )malloc(sizeof(Path) * n);

	for(str = strtok(NULL, b), i = 0; str != NULL; str = strtok(NULL, b), i++)
	{
		strcpy((tpaths+i)->ori, str);
		str = strtok(NULL, b);// 再切一次就是目的地
		strcpy((tpaths + i)->dest, str);	
	}
	printf("现有飞行路线:\n");
	for(int i=0;i<n;i++)
	printf("[%s, %s]\n",tpaths[i].ori,tpaths[i].dest);
	fclose(fp);// 关闭文件
	return i;	
}
int readRequestfile()
{
	FILE *fp;
	if((fp=fopen("PathRequest.txt","r+"))==NULL){ 
		perror("read file fopen err");
		exit(0);
	}
	fseek(fp,0L,SEEK_END);// 将光标停在文件的末尾
    long lSize= ftell (fp);//返回文件的大小（单位是bytes）
    fseek(fp,0L,SEEK_SET); /* 定位到文件开头 */
	char *buff =(char*) malloc(lSize+1);
	memset (buff,0,lSize);//初始化buff,否则屯屯屯,shit!windowssb平台下换行符为\r\n
	fread(buff,lSize,1,fp);//将数据读入到buff
	int n,i;
	const char *b="\n[, , ]";
	sscanf(buff, "%d", &n);
	char *str = strtok(buff, b);//把数量读掉
	Request *tres = (Request* )malloc(sizeof(Request) * n);
	for(str = strtok(NULL, b), i = 0; str != NULL; str = strtok(NULL, b), i++)
	{
		strcpy((tres+i)->path.ori, str);
		str = strtok(NULL, b);// 再切一次就是目的地
		strcpy((tres + i)->path.dest, str);
		sscanf(buff, "%d", &(tres+i)->hop);
		str = strtok(NULL, b);// 再切一次hop
	}
	fclose(fp);// 关闭文件
	printf("要求飞行路线:\n");
	for(int i=0;i<n;i++)
		printf("[%s, %s, %d]\n",(tres+i)->path.ori,(tres+i)->path.dest,tres->hop);
	return i;

}
void isFlyAndWrite(int inCount, int reCount)
{
	int i;
	char buf[100];
	FILE *wFp = fopen("out.txt", "wb");
    
    if (wFp == NULL) 
	{
        
        perror("write file fopen err:");
        exit(7);
    }
	printf("预期飞行结果:\n");
	for(i = 0; i < reCount; i++)
	{
		char *ori = (tres + i)->path.ori;
		char *des = (tres + i)->path.dest;
		int maxHops = (tres+ i)->hop;
		// 每次清空
		memset(buf, 0, sizeof(buf));
		if(isRelated(ori, des, maxHops, tpaths, inCount)) // 判断是否在maxhops下可以飞
		{
			printf("[%s, %s]:YES\n", ori, des);
            sprintf(buf, "[%s, %s, YES]\r\n", ori, des);
		}
		else
		{
			printf("[%s, %s]:NO\n", ori, des);
            sprintf(buf, "[%s, %s, NO]\r\n", ori, des);
		}

		fputs(buf, wFp);
	}

	fclose(wFp);
	wFp = NULL;
}

/**
	ori：要求的起点
	des：要求的重点
	maxHops：要求的最大路线数
	paths：原本的路线表
	inCount：路线表中路线的个数
	return：0：为不可以在规定hop飞到，1：可以
 */
int isRelated(char *ori, char *des, int maxHops, Path *paths, int inCount)
{
	char tmpOri[15];
	int i;
	for(i = 0; i < inCount && maxHops > 0; i++)
	{
		if (strcmp(ori, (paths + i)->ori) == 0) // 如果起点一样，比较终点
        {
            
            if (strcmp(des, (paths + i)->dest) == 0) // 起终点都一样返回真
            {
                return 1;
            }
            else
            {
                strcpy(tmpOri, (paths + i)->dest); // 使用中间变量将起点相同终点不同的作为下一次递归的起点

				if (isRelated(tmpOri, des, maxHops - 1, paths, inCount)) // 每次减一为了保证在规定最大hop内
                {
                    return 1;
                }
            }
        }
	}

	return 0;
}

int main() 
{
	int QD=readInputfile();
	int ZD=readRequestfile();
    isFlyAndWrite(QD, ZD);
    return 0;
}
