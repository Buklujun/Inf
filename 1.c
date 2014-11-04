#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "mylib.h"

int main (int argc, char* argv[])
{
	
	if (argc != 2)
	printf("Troubles with arguments");
	
	int fd[2];
	int fifo = 0;
	int error = 0;
	if (pipe(fd) < 0){
		printf("Can't open pipe");
		exit(-1);
	}
	
	if ((error = dup2(fd[1], STDOUT_FILENO))<0){
		printf("errror with dup2");
	}

	int res = fork();
	if (res < 0) {
		printf("Can't fork\n");	
	}
	if(res) {
		execlp("ls", "ls", "-la", argv[1]);
	}
	
	res = fork();
	if (res) {
		close(fd[1]);
		
		
	if ((error = mkfifo("a.fifo", 0666)) < 0) {
			printf ("Can't creat fifo");
			} 
	else {
		if ((fifo = open("a.fifo", O_WRONLY)) < 0)
			{
			printf ("Cant open fifo");
			}
		bufread (fd[0], fifo);
		
		close (fd[0]);
	}	
	}
		else if(res > 0){
		close(fd[1]);
		close(fd[0]);

				}
return 0;
}


