#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include "mylib.h"


int main(int argc, char* argv[]) {
    
    int i, id = 0;
    int fd[2];
    if (pipe(fd) < 0)
        printf("error open pipe\n");
    
    int n_fork = 0;
    if ((n_fork = fork()) < 0)
        printf("error with fork\n");
    
    if(n_fork == 0)
    {   if (dup2(fd[1], STDOUT_FILENO) < 0)
        printf("error with dup\n");
        
        execlp("ps", "ps", argv[1], NULL);
        
    }
    close(fd[1]);
    
    char* string;
    string = read_to_string(fd[0], string);
    close(fd[0]);
    printf("%s\n", string);
    int size = strlen(string);
    printf("%d\n", size);
    close(fd[0]);

    key_t key = 0;
    if ((key = ftok("write.c", 0)) < 0)
        printf("error with key\n");
    
    printf("key =  %d\n", key);
    
    if ((id = shmget(key, size, 0)) < 0)
    printf("error with shmget\n");
    
    printf("id = %d\n", id);
    
    char* memory;
    if ((memory = (char*)shmat(id, NULL, 0)) < 0)
        printf("error with shmat\n");
    
    printf("%d\n", memory);
    
    
    //for(i = 0; i < size; i++)
      //  memory[i] = string[i];

    
    //if (shmdt(memory) < 0)
      //  printf("error with shmdt\n");
    return 0;
}
