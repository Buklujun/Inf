#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/times.h>
#include <errno.h>
#include "mylib.h"

int *answer;
struct thread_args
{
    int *matrix;
    int size;
    int first_pos;
    int last_pos;
};

void* func(void* args)
{
    struct thread_args* thr = (struct thread_args*) args;
    int i, j, k, l, m, count = 0;
    int *matrix = thr->matrix;
    int size = thr->size;
    int first_pos = thr->first_pos;
    int last_pos = thr->last_pos;
    for (i = first_pos; i < last_pos; i++){
        m = i*size;
        for(j = 0; j < size; j++){
            l = 0;
            for(k = 0; k < size; k++){
                count += matrix[m+k] * matrix[j+l];
                l += size;
                }
            answer[m +j] = count;
            count = 0;
            }
        }
    pthread_exit(NULL);
}

int main(int argc,char* argv[]) {
    int i = 0;
    int m = atoi(argv[2]);
    int n = atoi(argv[1]);
    pthread_t thread[m];
    int id, fd, id_res = 0;
    int size = n*n;
    time_t prog_time = 0;
    clock_t proc_time = 0;
    int *matrix = (int*)calloc(size, sizeof(int));
    answer = (int*)calloc(size, sizeof(int));
    if ((id = open("1.txt", O_RDONLY, 0777)) < 0){
        perror("Error with open");
        exit(-1);}
    read_to_int(id, matrix, size);
    
    for (i=0;i<n;i++){
      for (int j=0;j<n;j++)
    {
                  printf("%d ",matrix[n*i+j]);
    	if (j == n-1)
    	printf("\n");
      	}}
    
    int step = n/m;
    int k_pos = 0;
    struct thread_args arg[m];
    
    prog_time = time(NULL);
    proc_time = clock();
    
    for (i = 0; i < m;i++){
        arg[i].matrix = matrix;
        arg[i].size = n;
        arg[i].first_pos = k_pos;
        k_pos += step;
        arg[i].last_pos = (i == m - 1) ? n : k_pos;
        if(pthread_create(&thread[i], NULL, func, (void*)&arg[i]) < 0)
            printf("Error cteare thread\n");}
    
    for(i=0;i<m;i++)
        pthread_join(thread[i],NULL);
    
    if((fd = open("result.txt",O_WRONLY | O_CREAT | O_EXCL,0666))<0)
    {
        printf("can't open for writing\n");
        exit(-1);
    }
    char *str = (char*)calloc(size, sizeof(char));
    for (i=0;i<n;i++){
        for (int j=0;j<n;j++)
        {
            sprintf(str+strlen(str),"%d ",answer[n*i+j]);
            
        }}
    write_string_to(str, fd);
    proc_time = clock() - proc_time;
    prog_time = time(NULL) - prog_time;
    printf("time=%lf\n", (double)proc_time/CLOCKS_PER_SEC);
    printf("real time : %ld \n", prog_time);



return 0;
}
