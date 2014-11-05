#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "mylib.h"
#define SIZE 1024

int main (int argc, char* argv[])
{
	
	if (argc != 2)
	printf("Troubles with arguments");
	
    char* ls_string;
	int fd[2];
	int fifo = 0;
	int error = 0;
	if (pipe(fd) < 0){
		printf("Can't open pipe");
		exit(-1);
	}
	
	
	int res = fork();
	if (res < 0) {
		printf("Can't fork\n");	
	}
	if(res > 0) {
        
        if ((error = dup2(fd[1], STDOUT_FILENO))<0){
            printf("errror with dup2");
        }
		execlp("ls", "ls", "-la", argv[1]);
                }
    
	if (res == 0) {
        ls_string = read_to_string (fd[0], ls_string);
		close(fd[1]);
        printf("%s", ls_string);
    }
    
	if ((error = mkfifo("a.fifo", 0666)) < 0) {
			printf ("Can't creat fifo\n");
			}
        fifo = open("a.fifo", O_RDWR);
			
        printf("%d\n", fifo);
        write_string_to(ls_string, fifo);
    

        close(fd[0]);
return 0;
}


