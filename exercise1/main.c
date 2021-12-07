#include <stdio.h>
#include <sys/fcntl.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char *argv[]){
    
    int res1, res2, res3;
  
    char input[50];
    char expectedOutput[50];  
    char students[50]; // "./students"
    int fd1 =  open("./config.txt", O_RDONLY);
    
    res1 = read(fd1, &students, 50); // ./students
    res2 = read(fd1, &input, 50); // ./input
    res3 = read(fd1, &expectedOutput, 50); // ./expectedOutput

   
    printf("%s", students);

    close(fd1);

   return 1;
}