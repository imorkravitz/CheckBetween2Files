#include <stdio.h>
#include <sys/fcntl.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>


int main(int argc, char *argv[]){
    
    int result1, result2;
    char* file1 = argv[1];
    char* file2 = argv[2];
    
    char c1, c2;
    int fd1 =  open(file1, O_RDONLY);
    int fd2 = open(file2, O_RDONLY);

    if(fd1<0 || fd2<0){
        perror("after open");
        _exit(1);
    }

    do{
        result1 = read(fd1, &c1, sizeof(c1));
        result2 = read(fd2, &c2, sizeof(c2));
        printf("%c c1\n" , c1);
        printf("%c c2\n" , c2);
        if (result1==result2){ // compare lentgh    
            if (c1==c2){ // compare caracter
               
            }else{_exit(1);}
        }else{_exit(1);}
    }
    
    while(result1 > 0 && result2 > 0);
    close(fd1); // free allocated memory
    close(fd2);
    _exit(2);

    return 0;
}