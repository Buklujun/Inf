#include <unistd.h>

int bufread(int fd_from, int fd_to) {
	int error = 0;
	int length = 1;
	char buff[1024] = {0};
	while ((length = read (fd_from, buff, 1024)) > 0)
	{error = write (fd_to, buff, 1024);
	if (error < 0)
	return -1;
	

}
	return 0;




}
