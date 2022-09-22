/*
Team 22
Team Member 1 - Md Areeb Akhtar (002011001100)
Team Member 2 - Ashfaq Murshed (002011001096)
Team Leader   - Manas Pratim Biswas (002011001025)
Date - 22/09/2022
*/

/*
Assignment Details - The OS is a program that uses various data structures. Like all programs in
                     execution, you can determine the performance and other behaviour of the OS by
                     inspecting its state - the values stored in its data structures. In this part of the
                     assignment, we study some aspects of the organization and behaviour of a Linux
                     system by observing values of kernel data structures exposed through the /proc
                     virtual file system.

                     The /proc virtual file system:
                     Linux uses the /proc file system to collect information from kernel data structures.
                     The /proc implementation provided with Linux can read many different kernel data
                     structures. If you cd to /proc on a Linux machine, you will see a number of files and
                     directories at that location. Files in this directory subtree each correspond to some
                     kernel data structure. The subdirectories with numeric names contain virtual files
                     with information about the process whose process ID is the same as the directory
                     name. Files in /proc can be read like ordinary ASCII files. You can open each file
                     and read it using library routines such as fgets() or fscanf(). The proc (5) manual
                     page explains the virtual files and their content available through the /proc file
                     system.

                     Requirements in detail:
                     You are supposed to write a C program which should run continuously and print lists
                     of the following dynamic values every seconds:
                     ● Per second disk read/write in the system
                     ● Per second Timer Interrupts
                     ● Currently executing kernel scheduling entities (processes, threads)
                     ● Number of kernel scheduling entities that currently exist on the system

Input Description  - No input
Output Description - Print the dynamic values every seconds
                     ● Per second disk read/write in the system
                     ● Per second Timer Interrupts
                     ● Currently executing kernel scheduling entities (processes, threads)
                     ● Number of kernel scheduling entities that currently exist on the system

*/

/*
Compilation Command (in Linux Bash Terminal) :- gcc 22_6.c
Execution Command (in Linux Bash Terminal) :- ./a.out
*/

/*
Sample Input  - No input
Sample Output -
Output :- (PROGRAM OUTPUT)

Displaying ...

Time spent in user mode : 2.262943 %, idle mode : 96.603818 % , system mode : 0.966815 %

Available Memory : 29371156 kb
The Percentage Available Memory : 89.564830

Average Read Rate of the disk (sectors per second) : 0.000000
Average Write Rate of the disk (sectors per second) : 0.000000
Rate of Context Switches (number per sec) : 1481.000000
Rate of Process Creations (number per sec) : 39.000000

Kernel Information:
Kernel Name: CPU0
Kernel Release: CPU2
------------------------------------------------------------------------------------------

Displaying ...

Time spent in user mode : 2.263280 %, idle mode : 96.599033 % , system mode : 0.970359 %

Available Memory : 29439616 kb
The Percentage Available Memory : 89.773593

Average Read Rate of the disk (sectors per second) : 0.000000
Average Write Rate of the disk (sectors per second) : 0.000000
Rate of Context Switches (number per sec) : 3413.000000
Rate of Process Creations (number per sec) : 73.000000

Kernel Information:
Kernel Name: CPU0
Kernel Release: CPU2
------------------------------------------------------------------------------------------

Displaying ...

Time spent in user mode : 2.262823 %, idle mode : 96.596032 % , system mode : 0.973862 %

Available Memory : 29437600 kb
The Percentage Available Memory : 89.767446

Average Read Rate of the disk (sectors per second) : 0.000000
Average Write Rate of the disk (sectors per second) : 0.000000
Rate of Context Switches (number per sec) : 2433.000000
Rate of Process Creations (number per sec) : 0.000000

Kernel Information:
Kernel Name: CPU0
Kernel Release: CPU2
------------------------------------------------------------------------------------------

Displaying ...

Time spent in user mode : 2.262900 %, idle mode : 96.592369 % , system mode : 0.977222 %

Available Memory : 29452516 kb
The Percentage Available Memory : 89.812931

Average Read Rate of the disk (sectors per second) : 0.000000
Average Write Rate of the disk (sectors per second) : 0.000000
Rate of Context Switches (number per sec) : 2678.000000
Rate of Process Creations (number per sec) : 0.000000

Kernel Information:
Kernel Name: CPU0
Kernel Release: CPU2
------------------------------------------------------------------------------------------

Displaying ...

Time spent in user mode : 2.265861 %, idle mode : 96.584341 % , system mode : 0.981252 %

Available Memory : 29391488 kb
The Percentage Available Memory : 89.626831

Average Read Rate of the disk (sectors per second) : 0.000000
Average Write Rate of the disk (sectors per second) : 0.000000
Rate of Context Switches (number per sec) : 8889.000000
Rate of Process Creations (number per sec) : 127.000000

Kernel Information:
Kernel Name: CPU0
Kernel Release: CPU2
------------------------------------------------------------------------------------------

Displaying ...

Time spent in user mode : 2.265891 %, idle mode : 96.580689 % , system mode : 0.984559 %

Available Memory : 29381660 kb
The Percentage Available Memory : 89.596861

Average Read Rate of the disk (sectors per second) : 0.000000
Average Write Rate of the disk (sectors per second) : 0.000000
Rate of Context Switches (number per sec) : 4497.000000
Rate of Process Creations (number per sec) : 1.000000

Kernel Information:
Kernel Name: CPU0
Kernel Release: CPU2
------------------------------------------------------------------------------------------

Displaying ...

Time spent in user mode : 2.275317 %, idle mode : 96.564258 % , system mode : 0.991114 %

Available Memory : 28880592 kb
The Percentage Available Memory : 88.068897

Average Read Rate of the disk (sectors per second) : 0.000000
Average Write Rate of the disk (sectors per second) : 0.000000
Rate of Context Switches (number per sec) : 38953.000000
Rate of Process Creations (number per sec) : 235.000000

Kernel Information:
Kernel Name: CPU0
Kernel Release: CPU2
------------------------------------------------------------------------------------------

Displaying ...

Time spent in user mode : 2.285700 %, idle mode : 96.548378 % , system mode : 0.995575 %

Available Memory : 28810016 kb
The Percentage Available Memory : 87.853682

Average Read Rate of the disk (sectors per second) : 0.000000
Average Write Rate of the disk (sectors per second) : 0.000000
Rate of Context Switches (number per sec) : 16880.000000
Rate of Process Creations (number per sec) : 6.000000

Kernel Information:
Kernel Name: CPU0
Kernel Release: CPU2
------------------------------------------------------------------------------------------

Displaying ...

Time spent in user mode : 2.291216 %, idle mode : 96.537862 % , system mode : 0.999903 %

Available Memory : 28842456 kb
The Percentage Available Memory : 87.952605

Average Read Rate of the disk (sectors per second) : 0.000000
Average Write Rate of the disk (sectors per second) : 0.000000
Rate of Context Switches (number per sec) : 10891.000000
Rate of Process Creations (number per sec) : 10.000000

Kernel Information:
Kernel Name: CPU0
Kernel Release: CPU2
------------------------------------------------------------------------------------------

Displaying ...

Time spent in user mode : 2.293423 %, idle mode : 96.530529 % , system mode : 1.003544 %

Available Memory : 28834540 kb
The Percentage Available Memory : 87.928466

Average Read Rate of the disk (sectors per second) : 0.000000
Average Write Rate of the disk (sectors per second) : 0.000000
Rate of Context Switches (number per sec) : 10149.000000
Rate of Process Creations (number per sec) : 36.000000

Kernel Information:
Kernel Name: CPU0
Kernel Release: CPU2
------------------------------------------------------------------------------------------

Displaying ...

Time spent in user mode : 2.293222 %, idle mode : 96.527353 % , system mode : 1.006924 %

Available Memory : 28839368 kb
The Percentage Available Memory : 87.943188

Average Read Rate of the disk (sectors per second) : 0.000000
Average Write Rate of the disk (sectors per second) : 0.000000
Rate of Context Switches (number per sec) : 2434.000000
Rate of Process Creations (number per sec) : 6.000000

Kernel Information:
Kernel Name: CPU0
Kernel Release: CPU2
------------------------------------------------------------------------------------------

Displaying ...

Time spent in user mode : 2.297329 %, idle mode : 96.518215 % , system mode : 1.011239 %

Available Memory : 28789612 kb
The Percentage Available Memory : 87.791462

Average Read Rate of the disk (sectors per second) : 0.000000
Average Write Rate of the disk (sectors per second) : 0.000000
Rate of Context Switches (number per sec) : 12052.000000
Rate of Process Creations (number per sec) : 38.000000

Kernel Information:
Kernel Name: CPU0
Kernel Release: CPU2
------------------------------------------------------------------------------------------

Displaying ...

Time spent in user mode : 2.299319 %, idle mode : 96.511962 % , system mode : 1.014876 %

Available Memory : 28765868 kb
The Percentage Available Memory : 87.719056

Average Read Rate of the disk (sectors per second) : 0.000000
Average Write Rate of the disk (sectors per second) : 0.000000
Rate of Context Switches (number per sec) : 8119.000000
Rate of Process Creations (number per sec) : 24.000000

Kernel Information:
Kernel Name: CPU0
Kernel Release: CPU2
------------------------------------------------------------------------------------------

Displaying ...

Time spent in user mode : 2.299204 %, idle mode : 96.508802 % , system mode : 1.018244 %

Available Memory : 28766128 kb
The Percentage Available Memory : 87.719849

Average Read Rate of the disk (sectors per second) : 0.000000
Average Write Rate of the disk (sectors per second) : 0.000000
Rate of Context Switches (number per sec) : 2344.000000
Rate of Process Creations (number per sec) : 0.000000

Kernel Information:
Kernel Name: CPU0
Kernel Release: CPU2
------------------------------------------------------------------------------------------

Displaying ...

Time spent in user mode : 2.301466 %, idle mode : 96.502733 % , system mode : 1.021830 %

Available Memory : 28767020 kb
The Percentage Available Memory : 87.722569

Average Read Rate of the disk (sectors per second) : 0.000000
Average Write Rate of the disk (sectors per second) : 0.000000
Rate of Context Switches (number per sec) : 7592.000000
Rate of Process Creations (number per sec) : 33.000000

Kernel Information:
Kernel Name: CPU0
Kernel Release: CPU2
------------------------------------------------------------------------------------------

^C
*/

// Header Files
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#define MAX_BUFFER_LENGTH 10000

void printLine()
{
    printf("------------------------------------------------------------------------------------------\n\n");
}

double toDouble(const char *str) // Method to convert string to double
{

    int n = strlen(str);
    int i;
    double ans = 0;
    for (i = 0; i < n; ++i)
    {
        if (str[i] >= '0' && str[i] <= '9')
        {
            ans = ans * 10 + (str[i] - '0');
        }
    }
    return ans;
}

int toInt(const char *str) // Method to convert string to integer
{
    int n = strlen(str);
    int i, ans = 0;
    for (i = 0; i < n; ++i)
    {
        if (str[i] >= '0' && str[i] <= '9')
        {
            ans = ans * 10 + (str[i] - '0');
        }
    }
    return ans;
}

void kernelInfo()
{
    FILE *fp;
    fp = fopen("/proc/interrupts", "rb");
    char *kernelName = (char *)malloc(1024);
    char *release = (char *)malloc(1024);
    char *temp = (char *)malloc(1024);
    fscanf(fp, "%s %s %s", kernelName, temp, release);
    printf("\nKernel Information: \n");
    printf("Kernel Name: %s\n", kernelName);
    printf("Kernel Release: %s\n", release);
}

int main(int argc, char const *argv[])
{
    char stream[MAX_BUFFER_LENGTH];

    double total = 0, idle, user, temp, system, mem_total, ctxt_prev, process_prev, sector_write_prev, sector_read_prev;
    double user_total = 0, idle_total = 0, system_total = 0, disk_read = 0, disk_write = 0;
    unsigned long long int available_mem, available_mem_total = 0;
    double ctxt_rate = 0, process_rate = 0;
    int observations = 0, disks = 0;
    int read_time = 1, print_time = 1;

    // Reading /proc/stat to save the initial values for the context switches and processess running in the system
    FILE *kernel_st_file = fopen("/proc/stat", "r");
    if (kernel_st_file == NULL)
    {
        perror("Error in opening file to read kernel/system statistics\n");
        exit(EXIT_FAILURE);
    }

    // Taking the initial values
    while (fgets(stream, MAX_BUFFER_LENGTH, kernel_st_file))
    {
        char *tk = NULL;
        tk = strtok(stream, " ");
        int i = 1, flag = 0;

        while (tk != NULL)
        {

            if (strcmp(tk, "ctxt") == 0)
            {
                flag = 1;
            }
            if (strcmp(tk, "processes") == 0)
            {
                flag = 2;
            }
            if (i == 2 && flag == 1)
            {
                flag = 0;
                ctxt_prev = toDouble(tk);
            }
            if (i == 2 && flag == 2)
            {
                flag = 0;
                process_prev = toDouble(tk);
            }

            i++;
            tk = strtok(NULL, " ");
        }
        free(tk);
    }
    fclose(kernel_st_file);

    FILE *diskstat_file = fopen("/proc/diskstats", "r");
    if (diskstat_file == NULL)
    {
        perror("Error in opening the file to read the disk statistics \n");
        exit(EXIT_FAILURE);
    }

    while (fgets(stream, MAX_BUFFER_LENGTH, diskstat_file))
    {

        char *token = NULL;
        int i = 1;
        int flag = 0;

        token = strtok(stream, " ");

        while (token != NULL)
        {
            // Calculating only for sda
            if (strcmp(token, "sda") == 0)
            {
                flag = 1;
            }
            // If the data is related to sda , then only consider it
            if (flag == 1)
            {
                // Record the number of sectors read sucessfully
                if (i == 6)
                {
                    sector_read_prev = toDouble(token);
                }
                // Record the number of sectors to which write was successfull
                if (i == 10)
                {
                    sector_write_prev = toDouble(token);
                }
            }
            token = strtok(NULL, " ");
            i++;
        }
        free(token);
    }
    fclose(diskstat_file);

    // Starting the read and write clocks for maintaining the time bound for reading files and printing the statistics
    clock_t initial_read = clock();
    clock_t initial_write = clock();

    while (1)
    {

        // Taking the reading of the current time
        clock_t final_time = clock();

        // Calculating the amount of time paassed since the last read and write operations
        int diff_read = (int)(final_time - initial_read) / CLOCKS_PER_SEC;
        int diff_print = (int)(final_time - initial_write) / CLOCKS_PER_SEC;

        // If the time elapsed is equal to the read_rate provided then record the data
        if (diff_read == read_time)
        {

            // Declaring and initializing variables
            total = 0;
            temp = 0;
            int i = 1;
            observations++;
            double read_rate = 0, write_rate = 0;
            double ctxt_new, process_new;

            // Processor time in different modes found in the /proc/stat file
            FILE *stat_file = fopen("/proc/stat", "r");
            if (stat_file == NULL)
            {
                perror("Error in opening file for reading processor time statistics \n");
                exit(EXIT_FAILURE);
            }

            fscanf(stat_file, "%s", stream);
            while (i <= 10)
            {

                fscanf(stat_file, "%lf", &temp);
                total += temp;

                // Record user mode data
                if (i == 1)
                {
                    user = temp;
                }
                // Record system mode data
                else if (i == 3)
                {
                    system = temp;
                }
                // Record idle mode data
                else if (i == 4)
                {
                    idle = temp;
                }

                i++;
            }

            idle = (idle * 100.0) / total;
            user = (user * 100.0) / total;
            system = (system * 100.0) / total;
            idle_total += idle;
            user_total += user;
            system_total += system;

            fclose(stat_file);

            // Amount of memory available
            FILE *mem_file = fopen("/proc/meminfo", "r");
            if (mem_file == NULL)
            {
                perror(" Error in opening file for reading memory details \n");
                exit(EXIT_FAILURE);
            }
            // Reading the total memory
            fscanf(mem_file, "%s", stream);
            fscanf(mem_file, "%lf", &mem_total);
            fscanf(mem_file, "%s\n", stream);
            fgets(stream, MAX_BUFFER_LENGTH, mem_file);
            // Reading the free(or available memory )
            fscanf(mem_file, "%s", stream);
            fscanf(mem_file, "%lld", &available_mem);
            fscanf(mem_file, "%s", stream);
            available_mem_total += available_mem;

            fclose(mem_file);

            // Disk read write
            FILE *disk_file = fopen("/proc/diskstats", "r");
            if (disk_file == NULL)
            {
                perror("Error in opening the file to read the disk statistics \n");
                exit(EXIT_FAILURE);
            }
            double sector_read, sector_write;
            while (fgets(stream, MAX_BUFFER_LENGTH, disk_file))
            {

                char *token = NULL;
                int i = 1;
                int flag = 0;

                token = strtok(stream, " ");

                while (token != NULL)
                {
                    // Calculating only for sda
                    if (strcmp(token, "sda") == 0)
                    {
                        flag = 1;
                    }
                    // If the data is related to sda , then only consider it
                    if (flag == 1)
                    {
                        // Record the number of sectors read sucessfully
                        if (i == 6)
                        {
                            sector_read = toDouble(token);
                        }
                        // Record the number of sectors to which write was successfull
                        if (i == 10)
                        {
                            sector_write = toDouble(token);
                        }
                    }
                    token = strtok(NULL, " ");
                    i++;
                }

                free(token);
            }
            read_rate = (sector_read - sector_read_prev) / read_time;
            write_rate = (sector_write - sector_write_prev) / read_time;

            sector_write_prev = sector_write;
            sector_read_prev = sector_read;

            disk_read += read_rate;
            disk_write += write_rate;

            fclose(disk_file);

            // Reading from /proc/stat file for recording the context switch rate and the process creation rate
            FILE *kernel_stat_file = fopen("/proc/stat", "r");
            if (kernel_stat_file == NULL)
            {
                perror("Error in opening file to read kernel/system statistics\n");
                exit(EXIT_FAILURE);
            }

            while (fgets(stream, MAX_BUFFER_LENGTH, kernel_stat_file))
            {

                char *tk = NULL;
                tk = strtok(stream, " ");
                int i = 1, flag = 0;

                while (tk != NULL)
                {
                    if (strcmp(tk, "ctxt") == 0)
                    {
                        flag = 1;
                    }
                    if (strcmp(tk, "processes") == 0)
                    {
                        flag = 2;
                    }
                    // Record the context switches happened till now
                    if (i == 2 && flag == 1)
                    {
                        flag = 0;
                        ctxt_new = toDouble(tk);
                    }
                    // Record the number of processess creayed till now
                    if (i == 2 && flag == 2)
                    {
                        flag = 0;
                        process_new = toDouble(tk);
                    }
                    i++;
                    tk = strtok(NULL, " ");
                }
                free(tk);
            }
            // Calculate the rates and add it to the global variable for doing the average later on
            ctxt_rate += ((ctxt_new - ctxt_prev) / read_time);
            process_rate += ((process_new - process_prev) / read_time);

            // Reinitialize the initial context switches and processess in the system
            ctxt_prev = ctxt_new;
            process_prev = process_new;

            fclose(kernel_stat_file);

            // Reset the timer for reading
            initial_read = clock();
        }
        // If the time elapsed is equal to the print_rate provided then print the data
        if (diff_print == print_time)
        {

            // Average out all the observations

            idle_total /= observations;
            user_total /= observations;
            system_total /= observations;

            available_mem_total /= observations;
            double percentage_mem_available = (available_mem_total * 100.0) / mem_total;

            disk_write /= observations;
            disk_read /= observations;

            ctxt_rate /= observations;
            process_rate /= (double)observations;

            // Printing all the observations
            printf("Displaying ... \n\n");
            printf("Time spent in user mode : %lf %%, idle mode : %lf %% , system mode : %lf %% \n\n", user_total, idle_total, system_total);
            printf("Available Memory : %lld kb\n", available_mem_total);
            printf("The Percentage Available Memory : %lf\n\n", percentage_mem_available);
            printf("Average Read Rate of the disk (sectors per second) : %lf\n", disk_read);
            printf("Average Write Rate of the disk (sectors per second) : %lf\n", disk_write);
            printf("Rate of Context Switches (number per sec) : %lf\n", ctxt_rate);
            printf("Rate of Process Creations (number per sec) : %lf\n", process_rate);
            kernelInfo();
            printLine();

            // Reseting all the Global Variables
            observations = 0;
            idle_total = 0;
            system_total = 0;

            user_total = 0;
            available_mem_total = 0;

            disk_read = 0;
            disk_write = 0;

            ctxt_rate = 0;
            process_rate = 0;

            // Reseting the timer
            initial_write = clock();
        }
    }
    return 0;
}