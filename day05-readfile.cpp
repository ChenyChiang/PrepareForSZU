#include<stdio.h>
#include<stdlib.h>
#include<string.h>
using namespace std;
#include<vector>
int main(){
	FILE *fp;
	if((fp=fopen("a.txt","r+"))==NULL){
		perror("file open err");
		exit(0);
	}
	/*char s[]="6\n[pvg, hek]\n[pvv, hak]";
	const char *d="\n[, ]";
	char *p=strtok(s,d);
	while(p)
	{
		printf("%s\n",p);
		p=strtok(NULL,d);
	}*/



	fseek(fp,0L,SEEK_END);// 将光标停在文件的末尾
        long lSize= ftell (fp);//返回文件的大小（单位是bytes）
        fseek(fp,0L,SEEK_SET); /* 定位到文件开头 */
	char *buff =(char*) malloc(lSize+1);
	memset (buff,0,lSize);//为了解决windows这个sb平台下换行符为\r\n
	//int number=lSize/sizeof(buff[0]);
	fread(buff,lSize,1,fp);
	//buff[lSize]='\0';
	//sprintf("%s\n",buff);
	puts(buff);
}
