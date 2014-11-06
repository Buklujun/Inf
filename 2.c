#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include "mylib.h"



int main() {
    char* str_1;
    int fifo = 0;
    fifo = open("a.fifo", O_RDONLY);
    if(fifo < 0)
    printf("Fifo error");
    str_1 = read_to_string (fifo, str_1);
    printf("%s", str_1);
    close(fifo);
    unlink("a.fifo");
    return 0;
}
