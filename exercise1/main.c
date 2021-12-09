#include <stdio.h>
#include <sys/fcntl.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    char students[50];
    char input[50];
    char expectedOutput[50];

    char const *const fileName = "./config.txt";
    FILE *file = fopen(fileName, "r");
    if (!file)
    {
        printf("Error opening: %s", fileName);
        return -1;
    }
    char line[500];
    fgets(line, sizeof(line), file);
    strcpy(students, line);
    fgets(line, sizeof(line), file);
    strcpy(input, line);
    fgets(line, sizeof(line), file);
    strcpy(expectedOutput, line);

    printf("%s", students);
    printf("%s", input);
    printf("%s", expectedOutput);

    fclose(file);

    //-------------------------------//

    int fd, pid, ret_code;
    fd = open("studentList.txt", (O_WRONLY | O_CREAT | O_TRUNC), 0666);
    pid = fork();
    if (pid == 0) /* son */
    {
        printf("Son : %d ;file descriptor: %d \n", getpid(), fd);
        close(1);  /* close stdout*/
        dup(fd);   /* dup will copy fd into stdout */
        close(fd); /* no need for fd anymore*/

        char *args[3];
        args[0] = "ls";
        args[1] = "students";
        args[2] = NULL;
        ret_code = execvp(args[0], args);
        // ret_code = execvp(args[0], args);	/*always same exe */
        if (ret_code == -1)
        {
            perror("exec failed ");
            close(fd);
            exit(-1);
        }
    }
    else /* father */
    {
        printf("Father: after fork, sons proc id is %d \n", pid);
        wait(NULL);
    }
    int grades = open("grades.txt", (O_WRONLY | O_CREAT | O_TRUNC), 0666);
    if (grades < 0)
    {
        perror("after open");
        _exit(1);
    }
    int output = open("output.txt", (O_WRONLY | O_CREAT | O_TRUNC), 0666);
    if (output < 0)
    {
        perror("after open");
        _exit(1);
    }
    char const *const studentsList = "./studentList.txt";
    FILE *file2 = fopen(studentsList, "r");
    if (!file2)
    {
        printf("Error opening: %s", fileName);
        return -1;
    }
    char line2[50];
    while (fgets(line2, sizeof(line), file2))
    {
        int fd2, pid2, ret_code2;
        pid2 = fork();
        if (pid2 == 0) /* son */
        {
            printf("Son : %d ;file descriptor: %d \n", getpid(), fd);
            close(1);   /* close stdout*/
            dup(fd2);   /* dup will copy fd into stdout */
            close(fd2); /* no need for fd anymore*/

            char *args2[5];
            args2[0] = "cd";
            args2[1] = "students/roy";
            args2[2] = "./main.exe";
            args2[3] = "input.txt";
            args2[4] = NULL;
            ret_code2 = execvp(args2[0], args2);
            // ret_code = execvp(args[0], args);	/*always same exe */
            if (ret_code2 == -1)
            {
                perror("exec failed ");
                close(fd2);
                exit(-1);
            }
            else /* father */
            {
                printf("Father: after fork, sons proc id is %d \n", pid2);
                wait(NULL);
            }
        }
        //char Buff[50];
        //strcpy(Buff, line2);
        //printf("%s\n", line2);
    }
    return 0;
}
