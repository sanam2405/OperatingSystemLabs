/*

Team 22
Team Member 1 :- Md Areeb Akhtar (002011001100)
Team Member 2 :- Ashfaq Murshed (002011001096)
Team Leader   :- Manas Pratim Biswas (002011001025)

Date - 27/08/2022

*/

/*

Assignment Details :- Objective of this programming assignment is to use mmap() call and observe page-fault
                      using the ‘sar’ command. A big file (about 8GB) should be created using the ‘fallocate’ command.
                      This big file should be written with a single integer value (say X) at a specific offset (say F).
                      Both the integer value and the offset should be generated using a random function.
                      Please do remember this random function should generate a quantity anywhere between 0 and 8G.
                      The above big file should also be mapped in the virtual address space using mmap() call.
                      Once it is mapped, the data should be read from the same specific offset (F).
                      Now, if the data read is X`; then verify that X and X` are the same.
                      In case of verification failure, an error message is to be printed.
                      Note that, the offset value F can be anywhere between 0 and 8G.
                      This sequence of writing and reading data to/from a specific offset and also verification should
                      be put in a while loop to go forever.
                      In another terminal execute the command ‘sar –B 1 1000’ to observe for the page fault.
                      This command should be started before the above program is put under execution.
                      So, one can observe that the page faults are increasing, once the above program starts executing.
                      The output of the program and the ‘sar’ command should be pasted as a comment at
                      the beginning of the program file.

Input Description  :- The name of the file to be transferred is entered as a command line input for execution of the program.


Output Description :-

    >>  The method prints the value written in the offset of the buffer and also the value read from the same offset
    >>  The method also prints whether the value written and read are the same or not


*/

/*

Command for creating a 8GB file :- fallocate -l 8G sampleFile.txt
NOTE :- This file has to be created in the same directory as that of the program

Compilation Command :- gcc 22_4.c

Execution Command   :- ./a.out  sampleFile.txt

*/

/*

Sample Input  :- No input

NOTE :- Use Control + C to exit from the infinite loop

Sample Output :- (PROGRAM OUTPUT)

The Value Written is : 658980830
The Value Read is : 658980830
The value that is read and written are the same!
---------------------------------------------
The Value Written is : 2019207291
The Value Read is : 2019207291
The value that is read and written are the same!
---------------------------------------------
The Value Written is : 381785217
The Value Read is : 381785217
The value that is read and written are the same!
---------------------------------------------
The Value Written is : 1772096689
The Value Read is : 1772096689
The value that is read and written are the same!
---------------------------------------------
The Value Written is : 1998067057
The Value Read is : 1998067057
The value that is read and written are the same!
---------------------------------------------
The Value Written is : 1310842475
The Value Read is : 1310842475
The value that is read and written are the same!
---------------------------------------------
The Value Written is : 53634673
The Value Read is : 53634673
The value that is read and written are the same!
---------------------------------------------
The Value Written is : 546260544
The Value Read is : 546260544
The value that is read and written are the same!
---------------------------------------------
The Value Written is : 124001343
The Value Read is : 124001343
The value that is read and written are the same!
---------------------------------------------
The Value Written is : 282070661
The Value Read is : 282070661
The value that is read and written are the same!
---------------------------------------------
The Value Written is : 979071901
The Value Read is : 979071901
The value that is read and written are the same!
---------------------------------------------
The Value Written is : 37470041
The Value Read is : 37470041
The value that is read and written are the same!
---------------------------------------------
The Value Written is : 1493430060
The Value Read is : 1493430060
The value that is read and written are the same!
---------------------------------------------
The Value Written is : 2135061740
The Value Read is : 2135061740
The value that is read and written are the same!
---------------------------------------------


Output :- (OUTPUT OF SAR COMMAND)
Linux Bash Command :- sar -B 1 1000

Linux 5.15.0-46-generic (manas-MS-7C02) 	08/27/2022 	_x86_64_	(12 CPU)

10:18:59 PM  pgpgin/s pgpgout/s   fault/s  majflt/s  pgfree/s pgscank/s pgscand/s pgsteal/s    %vmeff
10:19:00 PM      0.00    190.10    127.72      0.00    100.99      0.00      0.00      0.00      0.00
10:19:01 PM      0.00      0.00    141.00      0.00    954.00      0.00      0.00      0.00      0.00
10:19:02 PM      0.00     32.00  38326.00     16.00    516.00      0.00      0.00      0.00      0.00
10:19:03 PM      0.00    312.00 131072.00     26.00   1432.00      0.00      0.00      0.00      0.00
10:19:04 PM      0.00    120.00 109889.00     23.00   1637.00      0.00      0.00      0.00      0.00
10:19:05 PM      0.00  12732.00  92118.00     21.00   1528.00      0.00      0.00      0.00      0.00
10:19:06 PM      0.00    120.00  84928.00      8.00   1359.00      0.00      0.00      0.00      0.00
10:19:07 PM      0.00    128.00  81149.00     20.00   1402.00      0.00      0.00      0.00      0.00
10:19:08 PM      0.00    652.00  66205.00     14.00   1481.00      0.00      0.00      0.00      0.00
10:19:09 PM      0.00    704.00  60770.00     13.00   1478.00      0.00      0.00      0.00      0.00
10:19:10 PM      0.00 667428.00  54271.00      7.00   4484.00      0.00      0.00      0.00      0.00
10:19:11 PM      0.00 877444.00 103421.00      6.00   4584.00      0.00      0.00      0.00      0.00
10:19:12 PM      0.00    120.00 118305.00      4.00   1255.00      0.00      0.00      0.00      0.00
10:19:13 PM      0.00    112.00 103513.00      6.00   1347.00      0.00      0.00      0.00      0.00
^C

Average:         0.00 111355.89  74535.12     11.71   1681.58      0.00      0.00      0.00      0.00

*/

// Header Files
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#define LOWER 0          // LOWER value for the randomIntegerGenerator method
#define UPPER 8589934592 // UPPER value for the randomIntegerGenerator method

char *addressOfMapBuffer; // The address of the buffer created by the mmap() method call is stored

void printLine()
{
    printf("---------------------------------------------\n");
}
int readInteger(unsigned long offset)
{
    unsigned long readValue;
    sscanf(addressOfMapBuffer + offset, "%lu", &readValue);
    printf("The Value Read is : %-10lu\n", readValue);
    return readValue;
}

int writeInteger(unsigned long offset, unsigned long value)
{
    printf("The Value Written is : %-10lu\n", value);
    sprintf(addressOfMapBuffer + offset, "%lu", value);
}

unsigned long randomIntegerGenerator()
{
    unsigned long lowerRange = LOWER;
    unsigned long upperRange = UPPER;
    unsigned long randomNumber = lowerRange + (rand() % (upperRange - lowerRange + 1));
    return randomNumber;
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Sufficient number of arguments are not provided!\n");
        printf("The expected execution command is : ./a.out <file_name>\n");
        exit(1);
    }

    // Opening the user specified file
    int FILE = open(argv[1], O_RDWR, S_IRUSR | S_IWUSR);

    // The information about the user specified file is stored in this structure
    struct stat sb;

    // Getting the information of the file in the sb variable
    if (fstat(FILE, &sb) == -1)
    {
        perror("Some ERROR occured while getting the file size!");
        exit(1);
    }

    // Mapping the file in the virtual address space
    if ((addressOfMapBuffer = (char *)mmap(NULL, sb.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, FILE, 0)) == MAP_FAILED)
    {
        perror("Some ERROR occured while mapping the file!");
        exit(2);
    }

    // Setting the seed value for the rand() function
    srand(time(NULL));
    unsigned long offset, writtenValue, readValue;

    while (1)
    {
        writtenValue = randomIntegerGenerator(); // Getting a random integer in the weittenValue variable from the randomIntegerGenerator method

        offset = randomIntegerGenerator(); // Getting a random integer in the offset variable from the randomIntegerGenerator method

        writeInteger(offset, writtenValue); // Writing the value in writtenValue varible in the offset position of the addressOfMapBuffer

        readValue = readInteger(offset); // Reading a value in readValue from the offset position of the addressOfMapBuffer

        // Checking whether readValue and writtenValue are same or not
        if (writtenValue == readValue)
        {
            printf("The value that is read and written are the same!\n");
            printLine();
        }
        else
        {
            printf("The value that is read and written are NOT the same!\n");
            printLine();
        }
    }

    return 0;
}
