#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include "mylib.h"

int main(int argc, char** argv) {

    int fifo = 0;

    fifo = open("a.fifo", O_RDONLY);
    if(fifo < 0)
	printf("Fifo error");

    bufread(fifo, STDOUT_FILENO);

    close(fifo);
    unlink("a.fifo");

    return 0;
}
