
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <poll.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>


/* sixthdrvtest 
  */
int fd;

void my_signal_fun(int signum)
{
	unsigned char key_val;
	read(fd, &key_val, 1);
	printf("key_val: 0x%x\n", key_val);
}

int main(int argc, char **argv)
{
	unsigned char key_val;
	int ret;
	int Oflags;

	//signal(SIGIO, my_signal_fun);
	
	fd = open("/dev/buttons", O_RDWR | O_NONBLOCK);//注意这里的打开方式 O_NONBLOCK表示为阻塞打开
	if (fd < 0)
	{
		printf("can't open!\n");
		return -1;
	}

	//fcntl(fd, F_SETOWN, getpid());
	
	//Oflags = fcntl(fd, F_GETFL); 
	
	//fcntl(fd, F_SETFL, Oflags | FASYNC);


	while (1)
	{
		ret = read(fd, &key_val, 1);
		printf("key_val: 0x%x, ret = %d\n", key_val, ret);
		sleep(5);//以非阻塞（O_NONBLOCK）打开；非阻塞的方式打开的时候，调用read的时候会立即返回，需要休眠一下防止上面不停的打印
	}
	
	return 0;
}

