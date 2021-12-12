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
    strcat(students, line);
    fgets(line, sizeof(line), file);
    strcpy(input, line);
    fgets(line, sizeof(line), file);
    strcpy(expectedOutput, line);

    fclose(file);

    //-------------------------------//

    int fd, pid, ret_code;
    fd = open("studentList.txt", (O_WRONLY | O_CREAT | O_TRUNC), 0666);
    pid = fork();
    if (pid == 0) /* son */
    {
        printf("suceesful\n");
        close(1);  /* close stdout*/
        dup(fd);   /* dup will copy fd into stdout */
        close(fd); /* no need for fd anymore*/

        char *args[3];
        args[0] = "ls";
        args[1] = "students";
        args[2] = NULL;
        ret_code = execvp(args[0], args);
        if (ret_code == -1)
        {
            perror("exec failed ");
            close(fd);
            exit(-1);
        }
    }
    else /* father */
    {
        wait(NULL);
        printf("Father fork 1");
    }

    char const *const grades = "./grades.txt";
    FILE *gradeFile = fopen(grades, "w");
    if (!gradeFile)
    {
        printf("Error opening: %s", grades);
        return -1;
    }

    char const *const studentsList = "./studentList.txt";
    FILE *file2 = fopen(studentsList, "r");
    if (!file2)
    {
        printf("Error opening: %s", fileName);
        return -1;
    }

    char line2[50];
    //-----------------------main part----------------------------------
    while (fgets(line2, sizeof(line2), file2))
    {
        int output = open("output.txt", (O_WRONLY | O_CREAT | O_TRUNC), 0666);
        if (output < 0)
        {
            perror("after open");
            _exit(1);
        }
        //----------------calculate students function from input----------------//

        int fd2, pid2, ret_code2;
        char name[50];
        pid2 = fork();
        if (pid2 == 0) /* son */
        {
            close(1);      /* close stdout*/
            dup(output);   /* dup will copy fd into stdout */
            close(output); /* close no need for fd anymore*/

            memset(name, 0, 50);
            int i = 0;
            while (line2[i] != '\n')
            {
                name[i] = line2[i];
                i++;
            }
            char path[1000] = "./students";
            strcat(path, "/");
            strcat(path, name);
            strcat(path, "/studentMain.exe");

            char *args2[4];
            args2[0] = path;
            args2[1] = path;
            args2[2] = "../exercise1/input.txt";
            args2[3] = NULL;
            ret_code2 = execl(args2[0], args2[1], args2[2], args2[3]);
            if (ret_code2 == -1)
            {
                perror("exec failed INPUT ");
                close(output);
                exit(-1);
            }
        }
        else /* father */
        {
            wait(NULL);
            printf("\nFather fork 2\n");
        }
        //----------------Compare between output to expectedOutput----------------//

        int fd3, pid3, ret_code3, status;
        pid3 = fork();
        if (pid3 == 0) /* son */
        {
            close(1);      /* close stdout*/
            dup(output);   /* dup will copy fd into stdout */
            close(output); /* close no need for fd anymore*/

            char *args3[5];
            args3[0] = "code/partA/comp.exe";
            args3[1] = "code/partA/comp.exe";
            args3[2] = "../exercise1/output.txt";
            args3[3] = "../exercise1/expectedOutput.txt";
            args3[4] = NULL;
            ret_code3 = execl(args3[0], args3[1], args3[2], args3[3], args3[4]);
            if (ret_code3 == -1)
            {
                perror("exec failed ");
                close(output);
                exit(-1);
            }
        }
        else /* father */
        {
            wait(&status);
            printf("Father fork 3 %d ", status);
        }
        char name2[50];
        memset(name2, 0, 50);
        int i = 0;
        while (line2[i] != '\n')
        {
            name2[i] = line2[i];
            i++;
        }

        if (status == 512) //256 = 1 / 512 = 2
        {
            fprintf(gradeFile, "%s: ", name2);
            fprintf(gradeFile, "100\n");
        }
        else
        {
            fprintf(gradeFile, "%s: ", name2);
            fprintf(gradeFile, "0\n");
        }
    }
    fclose(gradeFile);

    //----------------Remove----------------//

    char *RMfiles[] = {"output.txt", "studentList.txt"};
    int j = 0;
    for (j = 0; j < 2; j++)
    {
        int fd4, pid4, ret_code4;
        pid4 = fork();
        if (pid4 == 0) /* son */
        {
            printf("\nRemove : %s \n ", RMfiles[j]);
            char *args4[3];
            args4[0] = "rm";
            args4[1] = RMfiles[j];
            args4[2] = NULL;
            ret_code4 = execvp(args4[0], args4);
            if (ret_code4 == -1)
            {
                perror("exec failed ");
                close(fd4);
                exit(-1);
            }
        }
        else /* father */
        {
            wait(NULL);
            printf("\nFather fork 4");
        }
    }

    return 0;
}
