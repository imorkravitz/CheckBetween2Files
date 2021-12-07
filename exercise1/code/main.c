#include <stdio.h>
#include <sys/fcntl.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    
    char* c = argv[1];
    char* d = argv[2];
    int x = atoi(c);
    int y = atoi(d);

    printf("%d", x+y);

    return 0;
}