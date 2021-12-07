#include <stdio.h>
#include <sys/fcntl.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
    
    int res1, res2, res3;
    // char* fileName = "./config.txt";
    // FILE* file;;
    // char* line = NULL;
    
    // file = fopen(fileName, "r");
    // if (file == NULL)
    // {
    //     exit(EXIT_FAILURE);
    // }
    

    string input;
    string expectedOutput;  
    string students; // "./students"
    int fd1 =  open("./config.txt", O_RDONLY);
    
    res1 = read(fd1, students, 50); // ./students
    res2 = read(fd1, input, 50); // ./input
    res3 = read(fd1, expectedOutput, 50); // ./expectedOutput

   
    printf("%s", students);

    fclose(file);
    if (line){
        free(line);
    }
    close(fd1);

   return 1;
}