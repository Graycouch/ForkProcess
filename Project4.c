
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>

/*
* This program uses the fork function to print numbers in the range of 1 to N.
* The first half of the numbers are printed by the parent process and the
* second half are printed by the child process. Since these print statements are performed by
* different processes, the program may produce interleaved output.
*
* CSC 3304 Programming project No. 4
*
* @author       Abdel Rahman Mansour
* @since        03/26/2021
*
*/
int main(int argc, char* argv[])
{
    pid_t pid;

    int N;

    if (argc != 3)
    {
        printf("Incorrect number of arguments\n");
        exit(0);
    }

    FILE* input = fopen(argv[1], "r");
    FILE* output = fopen(argv[2], "w");

    fscanf(input, "%d", &N);

    if (N < 0)
    {
        printf("negative number entered %d", N);
        exit(0);
    }

    pid = fork();

    if (pid < 0)
    {
        printf("failed to create child\n");
        exit(0);
    }

    else if (pid == 0)
    {
        wait(NULL);

        for (int i = (N / 2) + 1; i <= N; i++)
        {
            char String[] = "Child process: ";
            sprintf(String, "%s%d\n", String, i);
            fputs(String, output);
        }
    }

    else
    {
        for (int i = 0; i <= N / 2; i++)
        {
            char String[] = "Parent process: ";
            sprintf(String, "%s%d\n", String, i);
            fputs(String, output);
        }
    }

    fclose(input);
    fclose(output);

    return 0;
}