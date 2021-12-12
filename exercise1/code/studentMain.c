#include <stdio.h>
#include <sys/fcntl.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    FILE *file;
    int x=0,y=0,i=0;
    char num1,num2,ch;
    file=fopen(argv[1],"r");
    if(file==NULL){
        printf("file in not available \n");
    }
    else
    {
        ch=fgetc(file);
        num1=ch;
        ch=fgetc(file);
        num2=ch;

        x=num1-'0';
        y=num2-'0';
        printf("%d",x+y);
    }
    return 0;
}