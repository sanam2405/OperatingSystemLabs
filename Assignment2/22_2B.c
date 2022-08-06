/*

Team 22
Team Member 1 - Md Areeb Akhtar (002011001100)
Team Member 2 - Ashfaq Murshed (002011001096)
Team Leader   - Manas Pratim Biswas (002011001025)

Date - 6/08/2022

*/

/*

Assignment Details - Create two processes. Transfer 1GB file from process1 to process2 using a
                     FIFO. Now, transfer the same file from process2 to process1 using another
                     FIFO. Now, compare the two files to make sure that the same file has returned
                     back. Also, print the time required to do this double transfer. Attach this output
                     to the source file as a comment.
                     To create FIFO, you can either use shell command or system call.
                     To create a large file you can use the relevant command.
                     Use „ls –l‟ command to show the FIFO and the large file. Attach this output to
                     the source file as a comment.

Input Description  - No input

Output Description - The time required for the round about travel is printed on the screen.

*/

/*

Compilation Command - gcc 22_2B.c

Execution Command   - ./a.out

*/

/*

Sample Input  - No input
Sample Output -

>>> Opened the file initialFile.txt for reading
>>> Writing to FIFO fifo1
>>> Opened the file receivedFile.txt for writing
>>> Reading from FIFO fifo1
>>> Writing to FIFO fifo1 is completed
>>> File received from process 1
>>> Writing to FIFO fifo2 from the file receivedFile.txt
>>> Writing to fifo2 is completed
>>> Reading from fifo2 and writing to the file receivedBackFile.txt to compare received back file with the initial file sent by process1
>>> Both the files are same, there is no mismatch!
>>> The round-about time for transferring the file between process1 and process2 and back to process1 is 1596 milliseconds


Output of 'ls - l'

total 1048616
-rw-rw-r-- 1 manas manas       1530 Aug  6 20:24 22_2A.c
-rw-rw-r-- 1 manas manas       8595 Aug  6 22:48 22_2B.c
-rwxrwxr-x 1 manas manas      17480 Aug  6 22:47 a.out
prw-rw-r-- 1 manas manas          0 Aug  6 22:43 fifo1
prw-rw-r-- 1 manas manas          0 Aug  6 22:43 fifo2
-rw-rw-r-- 1 manas manas 1073741824 Aug  6 21:44 initialFile.txt
-rw-rw-r-- 1 manas manas          0 Aug  6 22:47 receivedBackFile.txt

*/

// Header files
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

// Method to get the time elapsed since the invoking of this function
long getTimeElapsed()
{
    struct timeval timeElapsed;
    gettimeofday(&timeElapsed, NULL);
    return timeElapsed.tv_sec * 1000 + timeElapsed.tv_usec / 1000;
}

// Method to compare two files and check if there is any mismatch or not
void compareFiles(FILE *firstFile, FILE *secondFile)
{
    char firstFileChar = getc(firstFile);
    char secondFileChar = getc(secondFile);

    int lineNumber = 1;
    int totalErrors = 0;

    while (firstFileChar != EOF && secondFileChar != EOF)
    {
        if (firstFileChar == '\n' && secondFileChar == '\n')
        {
            lineNumber++;
        }
        if (firstFileChar != secondFileChar)
        {
            totalErrors++;
            printf(">>> Mismatch occurred at line number : %d\n", lineNumber);
        }

        firstFileChar = getc(firstFile);
        secondFileChar = getc(secondFile);
    }

    if (totalErrors == 0)
    {
        printf(">>> Both the files are same, there is no mismatch!\n");
    }
}

int main()
{
    int startingTime = getTimeElapsed();
    char *fifo1 = "fifo1";
    // Creating named pipe(FIFO) fifo1 using mknod() system call to transfer large file from process1 to process2
    mknod(fifo1, S_IFIFO | 0666, 0);
    char *fifo2 = "fifo2";
    // Creating named pipe(FIFO) fifo2 using mknod() system call to transfer large file from process2 to process1
    mknod(fifo2, S_IFIFO | 0666, 0);
    // Create a new process
    int processID = fork();

    if (processID == 0) // Child process
    {
        // Reading from FIFO, writing into a file and sending to parent process
        int fd = open(fifo1, O_RDONLY);
        const char *receivedFile = "receivedFile.txt";
        FILE *receivedfp = fopen(receivedFile, "w");
        if (receivedfp == NULL)
            printf(">>> Failed to open the file %s for writing\n", receivedFile);
        else
            printf(">>> Opened the file %s for writing\n", receivedFile);
        if (fd > 0)
        {
            printf(">>> Reading from FIFO fifo1\n");
            char str[100];
            while (read(fd, str, sizeof(str)))
            {
                fputs(str, receivedfp);
            }
            printf(">>> File received from process 1\n");
            close(fd);
        }
        else
        {
            printf(">>> Failed to open FIFO fifo1 for reading\n");
        }

        fclose(receivedfp);

        // Creating another FIFO and sending the received file to the other process

        receivedfp = fopen(receivedFile, "r");
        fd = open(fifo2, O_WRONLY);
        if (fd > 0)
        {
            printf(">>> Writing to FIFO fifo2 from the file %s\n", receivedFile);
            char buffer[100];
            while (fgets(buffer, sizeof(buffer), receivedfp))
            {
                int len = strlen(buffer);
                int n = write(fd, buffer, len);
                if (n != len)
                    perror("write");
            }

            printf(">>> Writing to fifo2 is completed\n");
        }
    }
    else // Parent process
    {
        // Used the shell command fallocate to create the 1GB large file named 'initialFile.txt'
        // Command : fallocate -l 1G initialFile.txt
        const char *initialFile = "initialFile.txt";
        FILE *fp = fopen(initialFile, "r");
        if (fp == NULL)
            printf(">>> Failed to open the file %s for reading\n", initialFile);
        else
            printf(">>> Opened the file %s for reading\n", initialFile);
        int fd = open(fifo1, O_WRONLY);
        if (fd > 0)
        {
            printf(">>> Writing to FIFO fifo1\n");
            char str[100];
            while (fgets(str, sizeof(str), fp))
            {
                int len = strlen(str);
                int n = write(fd, str, len); // Writing to FIFO fifo1 from file initialFile.txt
                if (n != len)
                    perror("write");
            }

            printf(">>> Writing to FIFO fifo1 is completed\n");
        }
        else
        {
            printf(">>> Failed to open FIFO fifo1 for writing\n");
        }
        close(fd);
        fclose(fp);

        // Reading from fifo2 to check if file received back is same as file sent to process 2
        fd = open(fifo2, O_RDONLY);
        const char *receivedBackFile = "receivedBackFile.txt";
        FILE *receivedbackfp = fopen(receivedBackFile, "w");
        if (fd > 0)
        {
            printf(">>> Reading from fifo2 and writing to the file %s to compare received back file with the initial file sent by process1\n", receivedBackFile);
            char buffer[100];
            while (read(fd, buffer, sizeof(buffer))) // Reading from fifo2 and writing to file receivedBackFile
            {
                fputs(buffer, receivedbackfp);
            }
        }
        else
        {
            perror("read");
        }

        close(fd);
        fclose(receivedbackfp);

        int endingTime = getTimeElapsed();
        // Calculating the round-about time for transferring the file between process1 and process2 and back to process1
        int totalTimeTaken = endingTime - startingTime;

        // Comparing receivedBackFile.txt with initialFile.txt
        fp = fopen(initialFile, "r");
        receivedbackfp = fopen(receivedBackFile, "r");
        compareFiles(fp, receivedbackfp);

        fclose(fp);
        fclose(receivedbackfp);
        printf(">>> The round-about time for transferring the file between process1 and process2 and back to process1 is %d milliseconds\n", totalTimeTaken);
    }

    return 0;
}