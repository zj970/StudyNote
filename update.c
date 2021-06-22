#include <stdio.h>
#include "music.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

void update(char *file_name)
{
	FILE *fp;
	char update[up];//定义输入的更新内容大小
	char ch;
	char *p;
	int i;
	int address,c;
	int set_nu = 1; //
	int set_num;
	int len; //
	p = update;
	printf("\n你要修改的歌词文件名：%s",file_name);
	printf("\n你想在第几行修改内容：");
	scanf("%d",&set_num);
	printf("修改内容:");
	scanf("%s",p);
	fp = fopen(file_name, "r+");
	while (set_nu != set_num)
	{
		ch = fgetc(fp);
		if (ch == '\n')
		set_nu++;
	}
	address = ftell(fp);
	printf("%d",address);
	while (fgetc(fp) !=']')
	c=ftell(fp);
	len = strlen(p);
	fseek(fp, c+1 ,SEEK_SET);
	for(i=0; i<len;i++)
	fputc(update[i],fp);
	fclose(fp);	
	return ;

}
