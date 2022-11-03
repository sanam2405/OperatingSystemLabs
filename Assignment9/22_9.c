/*
Team 22
Team Member 1 - Md Areeb Akhtar (002011001100)
Team Member 2 - Ashfaq Murshed (002011001096)
Team Leader   - Manas Pratim Biswas (002011001025)
Date - 03/11/2022
*/

/*
Assignment Details -

The objective of this assignment is to use thread programming technique to
write a parallel program which will find the output of an edge detection filter.
The input to the filter is a rectangular matrix (MxN), in which the elements
are the pixel values of an image. The output is also a rectangular matrix of
same size where the elements are the edge pixel values. The edge pixel
values are constructed from the image using:-
edgei,j = imagei−1,j + imagei+1,j + imagei,j−1 + imagei,j+1 − 4 imagei,j
If an image pixel has the same value as its four surrounding neighbors (i.e.
no edge) then the value of edgei,j will be zero. If the pixel is very different
from its four neighbors (i.e. a possible edge) then edgei,j will be large in
magnitude. We will always consider i and j to lie in the range 1, 2, . . .M and
1, 2, . . .N respectively. Pixels that lie outside this range (e.g. imagei,0 or
imageM+1,j) are simply considered to be set to zero.
You have to also measure the time elapsed. The Matrix should be large
enough (dynamically allocated) to fit in your computer memory so as to
make the speedup measurement process easy.
As you increase the number of threads(max to your number of CPUs), your
timing and speedup should show improvement. Use ‘gettimeofday’ to note
down the timing. Make sure you attach the timing to the starting comment
block of your source file and also show the speedup. Your time should not
include the Matrix initialization time.
You have to use various ‘Pthread’ library calls to do this assignment
properly. Use the proper process listing command (ps) to show (and attach
it to the starting comment block of your source file) that your threads are
running in the system. Also, use proper command to show CPU and
Memory utilization and attach these outputs to the starting comment block
of your source file.
This program should take five command line arguments. The First
argument is the Row Size of the Rectangular Matrix. The Second argument
is the Column Size of the Rectangular Matrix.

The Third argument is about the number of threads. For example, the value
of the second argument will be 1, 2, 3, and 4 etc.; signifying total no of
threads which will be created.
The Fourth argument will be the value of the ‘mod’ which will be used to
initialize all the elements of the input Rectangular Matrix.
The Fifth (last) argument will be the print_switch. If its value is ‘1’, both the
Input and Output Matrices will be printed on the screen. In case the value is
‘0’, Matrices won’t be printed on the screen.

*/

/*
Compilation Command (in Linux Bash Terminal) :- gcc 22_9.c
Execution Command (in Linux Bash Terminal) :- ./a.out 5 3 2 10 1
*/

/*
Sample Input  - ./a.out 5 3 2 10 1
Sample Output -
Output :- (PROGRAM OUTPUT)

The total time taken = 0.000001 seconds

ORIGINAL MATRIX :

2       1       6
2 	    2       6
9 	    7   	2
0 	    2   	4
0 	    2   	3
--------------------------------------------

RESULTANT MATRIX :

-5 	    6   	-17
5 	    8   	-14
-27    -13     	 9
11 	    5 	    -9
2 	   -3 	    -6
--------------------------------------------


*/

#include <limits.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/random.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

#define MAX_THREAD 1000

int print_switch = 0;
int numberOfThreads = 0;
int M = 0;
int N = 0;
int MOD = 0;

int **originalMatrix;     // Stores the original matrix
int **resultantMatrix;    // Stores the edge pixel output matrix
float totalTimeTaken = 0; // Stores the total time taken

int **create_matrix(int M, int N);
void output(int **arr);

void printLine() // Method to print a dashed-line
{
    printf("--------------------------------------------\n");
}

void *edge(void *arg)
{
    // Timer
    struct timeval startingTime, endingTime;

    // startingTime timer
    gettimeofday(&startingTime, NULL);

    long int threadNumber = (long int)arg;
    int i, j, k;

    int from = (threadNumber * M) / numberOfThreads;
    int to = ((threadNumber + 1) * M) / numberOfThreads;

    for (int i = from; i < to; i++)
    {
        for (int j = 0; j < N; j++)
        {
            resultantMatrix[i][j] = 0;
            int left = 0, right = 0, top = 0, bottom = 0;
            if (i != 0)
                top = originalMatrix[i - 1][j];
            if (i != M - 1)
                bottom = originalMatrix[i + 1][j];
            if (j != 0)
                left = originalMatrix[i][j - 1];
            if (j != N - 1)
                right = originalMatrix[i][j + 1];

            resultantMatrix[i][j] = top + left + right + bottom - (4 * originalMatrix[i][j]);
        }
    }

    // Timer Stops
    gettimeofday(&endingTime, NULL);

    // Calculating total time taken by the program.
    double time_taken;

    time_taken = (endingTime.tv_sec - startingTime.tv_sec) * 1e6;
    time_taken = (time_taken + (endingTime.tv_usec - startingTime.tv_usec)) * 1e-6;
    totalTimeTaken += time_taken;
}

int main(int argc, char *argv[])
{

    if (argc != 6)
    {
        printf("The number of arguments is not correct!\n");
        exit(0);
    }

    M = atoi(argv[1]);
    N = atoi(argv[2]);
    numberOfThreads = atoi(argv[3]);
    MOD = atoi(argv[4]);
    print_switch = atoi(argv[5]);

    pthread_t tid[MAX_THREAD];
    long int i, j;

    originalMatrix = create_matrix(M, N);
    resultantMatrix = create_matrix(M, N);

    // Creating threads
    for (i = 0; i < numberOfThreads; i++)
    {
        if (pthread_create(&tid[i], NULL, &edge, (void *)i) != 0)
        {
            perror("Unable to create the thread\n");
            exit(0);
        }
    }

    // Joining Threads
    for (j = 0; j < numberOfThreads; j++)
    {
        if (pthread_join(tid[j], NULL) != 0)
        {
            perror("Unable to join thread\n");
            exit(0);
        }
    }

    printf("The total time taken = %f seconds\n", totalTimeTaken);

    if (print_switch == 1)
    {
        printf("\nORIGINAL MATRIX : \n");
        output(originalMatrix);
        printLine();
        printf("\nRESULTANT MATRIX : \n");
        output(resultantMatrix);
        printLine();
    }

    free(originalMatrix);
    free(resultantMatrix);

    return 0;
}

void output(int **arr)
{
    int i, j;
    int row = M;
    int col = N;
    for (i = 0; i < row; i++)
    {
        printf("\n");
        for (j = 0; j < col; j++)
            printf("%d \t", arr[i][j]);
    }
    printf("\n");
}

int **create_matrix(int M, int N)
{
    int r = M, c = N, i, j;

    int **arr = (int **)malloc(r * sizeof(int *));
    for (i = 0; i < r; i++)
        arr[i] = (int *)malloc(c * sizeof(int));

    for (i = 0; i < r; i++)
        for (j = 0; j < c; j++)
        {
            // Generate Random Number
            int randomNumber;
            if (getrandom(&randomNumber, sizeof(int), GRND_NONBLOCK) == -1)
            {
                perror("getrandom():");
                exit(1);
            }
            if (randomNumber < 0)
            {
                randomNumber *= -1;
            }
            arr[i][j] = randomNumber % MOD;
        }
    return arr;
}
