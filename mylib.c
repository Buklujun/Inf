#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define SIZE 512

char* read_to_string (int fd_from, char* message) {
    int i = 0;
    int length = 0;
    message = (char*)calloc(SIZE, sizeof(char));
    while ((length = read (fd_from, message + i * SIZE, SIZE)) != 0 )
	{	i++;
		message = (char*)realloc(message, SIZE * (i + 1) * sizeof(char));
        if (length < SIZE)
	{
           break;
	}
    }
    return message;
	
}

void write_string_to (char* message, int fd_to)
{	int error = 0;
	int count = 0;
	int string_len = 0;
	string_len = strlen (message);
    printf("Size of string = %d\n", string_len);
	while ((error = write(fd_to, message + count, string_len - count)) != 0)
	{
	   count += error;
	   if (string_len == count)
	     break;
	if (error < 0){
        printf("Error with write\n");
           break;	}
	}
	
	
}

void write_int_to (int* message, int fd_to, int size)
{	int error = 0;
    int count = 0;
    printf("%d\n", size);
    
    while ((error = write(fd_to, message + count, (size - count)*sizeof(int))) != 0)
    {
        printf("zapisalos' %d\n", error);
        count += error;
        if (size*sizeof(int) == count)
            break;
        if (error < 0){
            printf("Error with write\n");
            break;	}
    }
    
}

void read_to_int (int fd_from, int* message, int size) {
    int i = 0;
    int count = 0;
    int length = 0;
    while ((length = read (fd_from, message + count, (size - count)*sizeof(int))) != 0 )
    {	count += length;
        if (count == size)
        break;
        
    }
    
}
