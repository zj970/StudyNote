#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "music.h"


int check(char *file_name)
{
	
	int dest_file;
	char music[SIZE_MUSIC];//存取查询的歌词内容，最大为10240字节
	printf("你所要查找的歌词文件名为：%s",file_name);
	printf("\n正在查找中.........\n");
	/*以读/写方式打开歌词文件*/
	dest_file = open (file_name, O_RDWR);
	if (dest_file < 0)
	{
		printf("输入文件名有误/查找失误！");
		return 0;
		
	}
	else
	{
	read(dest_file, music,sizeof(music));
	printf("%s",music);
	return 1;
	}
	close(dest_file);
}
