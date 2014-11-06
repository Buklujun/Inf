#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define SIZE 512

char* read_to_string (int fd_from, char* message) {
    int i = 0;
	int length = 0;
	message = (char*)calloc(SIZE, sizeof(char));
	while ((length = read (fd_from, message + i * SIZE, SIZE)) == SIZE )
	{
		message = (char*)realloc(message, SIZE * (i + 2) * sizeof(char));
		i++;
        if (length < SIZE )
            
            break;
	}
    return message;
}


void write_string_to (char* message, int fd_to)
{	int error = 0;
	int string_len = 0;
	string_len = strlen (message);
    printf("Size of string = %d\n", string_len);
	if ((error = write(fd_to, message, string_len)) < 0)
	printf("Error with write\n");
    
    printf("SIze of write = %d\n", error);
	
}
