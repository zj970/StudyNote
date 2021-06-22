#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

int main()
{
	struct termios new_serial;
	struct termios old_serial;
	int fd;
	fd = open ("/dev/ttyS2", O_RDONLY);
	if (tcgetattr(fd, &old_serial) != 0){
	perror("tcgetattr");
	return -1;
	}/*保存原先串口的配置*/

	new_serial.c_cflag |= CLOCAL | CREAD;
	cfmakeraw(&new_serial);
	/*激活选项*/

	cfsetispeed(&new_serial, B115200);
	cfsetospeed(&new_serial, B115200);
	/*设置波特率*/

	new_serial.c_cflag &= ~CSIZE;/*用数据位掩码清空数据位设置*/
	new_serial.c_cflag |= CS8;

	/*设置奇偶校验位
	new_serial.c_cflag |= (PARODD | PARENB);
	new_serial.c_iflag |= INPCK;/*使能奇效验
	new_serial.c_cflag |= PARENB;
	new_serial.c_cflag &= ~PARODD;
	new_serial.c_iflag |= INPCK;/*使能偶校验*/
	
	new_serial.c_cflag &= ~PARENB;
	new_serial.c_iflag &= ~INPCK;/*不设置奇偶校验位*/
	
	/*设置停止位*/
	new_serial.c_cflag &= ~CSTOPB;/*将停止位设置为一个比特*/
	new_serial.c_cflag |= CSTOPB; /*将停止位设置为两个比特*/

	/*设置最少字符和等待时间*/
	new_serial.c_cc[VTIME] = 0;
	new_serial.c_cc[VMIN] = 0;
	
	/*清除串口缓冲*/
	int tvdrain(int fd);/*使程序阻塞，直到输出缓冲区的数据全部发送完毕*/
	int tcflow(int fd, int action);/*用于暂停或重新开始输出*/
	int tcflush(int fd, int queue_selector);/*用于清空输入/输出缓冲区*/
	
	/*激活串口配置*/
	tcsetattr(fd, TCSANOW, &new_serial);
	close(fd);
	return 0;
}

