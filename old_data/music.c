#include <stdio.h>
#include "music.h"

int main()
{
	char music_filelrc[SIZE];//开辟一个大小为32的一维字符型数组存歌词文件名
	char *file_name;
	file_name = music_filelrc;
	int ch = 0;
	printf("请输入歌词文件名（小于32字节）：");
	scanf("%s",file_name);
	ch = check(file_name);
	if (ch == 1)
	{
	update(file_name);
	}
	return 0;
}
