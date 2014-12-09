#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <errno.h>
#include "mylib.h"


int main(int argc, char* argv[]) {

	int id = 0;
	int n = atoi(argv[1]);
	int size;
	size = n*n;
	int x,i,j = 0;
	int *matrix = (int*)calloc(n*n, sizeof(int));

	for (i=0;i<n;i++){
                for (int j=0;j<n;j++)
                {   matrix[n*i+j] = rand() % 100;
        	}}

	if ((id = open("1.txt", O_WRONLY | O_CREAT | O_EXCL, 0777)) < 0){
		perror("Error with open");
		exit(-1);}
    write_int_to(matrix, id, size);
    
   // for (i=0;i<n;i++){
        //for (int j=0;j<n;j++)
        //{
              //     printf("%d ",matrix[n*i+j]);
            //if (j == n-1)
          //  printf("\n");
        //}}



return 0;
}
