/*
Team 22
Team Member 1 - Md Areeb Akhtar (002011001100)
Team Member 2 - Ashfaq Murshed (002011001096)
Team Leader   - Manas Pratim Biswas (002011001025)
Date - 01/09/2022
*/

/*
Assignment Details - The objective of this assignment is to avoid deadlock. For this purpose define two
					 global variables (Total_1 and Total_2) and initialize both of them to 10000000. You
					 should also have two mutexes to protect these two global variables. You need to
					 create three threads also (Th1, Th2 and Th3).
					 The function of thread Th1 is to generate a random quantity (not more than 10) and
					 subtract that quantity from Total_2 and add that quantity to the Total_1. Likewise,
					 The function of thread Th2 is to generate a random quantity (not more than 10) and
					 subtract that quantity from Total_1 and add that quantity to the Total_2. While
					 manipulating the Totals, the Th1 and Th2 should lock both the mutex and then
					 unlock it after changing the Totals.
					 The function of the thread Th3 is to keep displaying the individual Totals and Grand
					 Total (sum of Total_1 and Total_2). Make sure the displayed values are consistent.
					 Note that this program should run forever.
					 The order of locking and unlocking the Mutex is very important, because that’s what
					 avoids a Deadlock or creates one. Once you correctly identify the order for avoiding
					 Deadlock, you should upload the program. Also, include that information (as a
					 comment in your source file) regarding the order for creating Deadlock.
					 Make sure there are enough printf in your program so that it can be clearly
					 understood that there is no Deadlock.

Input Description  - No input
Output Description - Print the individual total and the grand total
*/

/*
Compilation Command (in Linux Bash Terminal) :- gcc 22_5.c
Execution Command (in Linux Bash Terminal) :- ./a.out -pthread
*/

/*
Sample Input  - No input
Sample Output -
Output :- (PROGRAM OUTPUT)

----------------------------------------------------------
The CURRENT SUMS are : 
>>> Total_1 : 10000009
>>> Total_2 : 9999991
>>> Total1 + Total2 : 20000000
----------------------------------------------------------
----------------------------------------------------------
The CURRENT SUMS are : 
>>> Total_1 : 10000008
>>> Total_2 : 9999992
>>> Total1 + Total2 : 20000000
----------------------------------------------------------
----------------------------------------------------------
The CURRENT SUMS are : 
>>> Total_1 : 10000007
>>> Total_2 : 9999993
>>> Total1 + Total2 : 20000000
----------------------------------------------------------
----------------------------------------------------------
The CURRENT SUMS are : 
>>> Total_1 : 10000006
>>> Total_2 : 9999994
>>> Total1 + Total2 : 20000000
----------------------------------------------------------
----------------------------------------------------------
The CURRENT SUMS are : 
>>> Total_1 : 10000005
>>> Total_2 : 9999995
>>> Total1 + Total2 : 20000000
----------------------------------------------------------
----------------------------------------------------------
The CURRENT SUMS are : 
>>> Total_1 : 10000015
>>> Total_2 : 9999985
>>> Total1 + Total2 : 20000000
----------------------------------------------------------
----------------------------------------------------------
The CURRENT SUMS are : 
>>> Total_1 : 10000014
>>> Total_2 : 9999986
>>> Total1 + Total2 : 20000000
----------------------------------------------------------
----------------------------------------------------------
The CURRENT SUMS are : 
>>> Total_1 : 10000013
>>> Total_2 : 9999987
>>> Total1 + Total2 : 20000000
----------------------------------------------------------
----------------------------------------------------------
The CURRENT SUMS are : 
>>> Total_1 : 10000012
>>> Total_2 : 9999988
>>> Total1 + Total2 : 20000000
----------------------------------------------------------
----------------------------------------------------------
The CURRENT SUMS are : 
>>> Total_1 : 10000011
>>> Total_2 : 9999989
>>> Total1 + Total2 : 20000000
----------------------------------------------------------
----------------------------------------------------------
The CURRENT SUMS are : 
>>> Total_1 : 10000010
>>> Total_2 : 9999990
>>> Total1 + Total2 : 20000000
----------------------------------------------------------
----------------------------------------------------------
The CURRENT SUMS are : 
>>> Total_1 : 10000009
>>> Total_2 : 9999991
>>> Total1 + Total2 : 20000000
----------------------------------------------------------
----------------------------------------------------------
The CURRENT SUMS are : 
>>> Total_1 : 10000008
>>> Total_2 : 9999992
>>> Total1 + Total2 : 20000000
----------------------------------------------------------
----------------------------------------------------------
The CURRENT SUMS are : 
>>> Total_1 : 10000007
>>> Total_2 : 9999993
>>> Total1 + Total2 : 20000000
----------------------------------------------------------
----------------------------------------------------------
The CURRENT SUMS are : 
>>> Total_1 : 10000006
>>> Total_2 : 9999994
>>> Total1 + Total2 : 20000000
----------------------------------------------------------
----------------------------------------------------------
The CURRENT SUMS are : 
>>> Total_1 : 10000005
>>> Total_2 : 9999995
>>> Total1 + Total2 : 20000000
----------------------------------------------------------
----------------------------------------------------------
The CURRENT SUMS are : 
>>> Total_1 : 10000015
>>> Total_2 : 9999985
>>> Total1 + Total2 : 20000000
----------------------------------------------------------
----------------------------------------------------------
The CURRENT SUMS are : 
>>> Total_1 : 10000014
>>> Total_2 : 9999986
>>> Total1 + Total2 : 20000000
----------------------------------------------------------
----------------------------------------------------------
The CURRENT SUMS are : 
>>> Total_1 : 10000013
>>> Total_2 : 9999987
>>> Total1 + Total2 : 20000000
----------------------------------------------------------
----------------------------------------------------------
The CURRENT SUMS are : 
>>> Total_1 : 10000012
>>> Total_2 : 9999988
>>> Total1 + Total2 : 20000000
----------------------------------------------------------
^C



*/


/*

Deadlock Sequence -

        To prevent a deadlock :   
        
		(I) In the method Th1
                                        
        Lock mutex1 followed by mutex2.
        After completion of the processes unlock mutex2 followed by mutex1
        
        pthread_mutex_lock(&mutex_1);
        pthread_mutex_lock(&mutex_2);
        pthread_mutex_unlock(&mutex_2);
        pthread_mutex_unlock(&mutex_1);
                                    
        (II) In the method Th2
    
        Lock mutex2 followed by mutex1.
        After completion of the processes unlock mutex1 followed by mutex2
        
        pthread_mutex_lock(&mutex_2);
        pthread_mutex_lock(&mutex_1);
        pthread_mutex_unlock(&mutex_1);
        pthread_mutex_unlock(&mutex_2);
                                    
        To create a deadlock : 
        Any other sequence of execution apart from the forementioned one will create a deadlock  
        
        Eg:(II) In method Th2
                                
        Lock mutex2 followed by mutex1.
        After completion of the processes unlock mutex2 followed by mutex1
        
        pthread_mutex_lock(&mutex_2);
        pthread_mutex_lock(&mutex_1);
        pthread_mutex_unlock(&mutex_2);
        pthread_mutex_unlock(&mutex_1);

*/


// Header Files
#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>

int Total_1 = 10000000;
int Total_2 = 10000000;

pthread_mutex_t mutex_1;
pthread_mutex_t mutex_2;


void printLine()
{
	printf("----------------------------------------------------------\n");
	return;
}

int randomNumberGenerator(int lowerCap, int higherCap)			// Generates a random number between lowerCap and higherCap
{
	int difference = higherCap - lowerCap;
	int randomNumber = lowerCap + rand() %  (higherCap - lowerCap + 1);

	return randomNumber;
}

void *getTheSums() 
{
	printLine();

	printf("The CURRENT SUMS are : \n");
    printf(">>> Total_1 : %d\n",Total_1);
	printf(">>> Total_2 : %d\n",Total_2);
	int totalSum = Total_1 + Total_2;
	printf(">>> Total1 + Total2 : %d\n",totalSum);

	printLine();

    sleep(1);

	void *ptr;

	return ptr;
}

void *threadOne() 
{
    pthread_mutex_lock(&mutex_1);
	
    pthread_mutex_lock(&mutex_2);
    
	int randomNumber;
	time_t time1;
	
	srand((unsigned) time(&time1));
	
	randomNumber = randomNumberGenerator(0,10);
	Total_1 += randomNumber;
	Total_2 -= randomNumber;

    sleep(1);
        
    pthread_mutex_unlock(&mutex_2);
    
    pthread_mutex_unlock(&mutex_1);

	void *ptr;

	return ptr;
}

void *threadTwo() 
{
	pthread_mutex_lock(&mutex_2);
	
	pthread_mutex_lock(&mutex_1);
	 
	int randomNumber;
	time_t time2;
	
	srand((unsigned) time(&time2));

	randomNumber = randomNumberGenerator(0,10);
	
	Total_1 -= randomNumber;
	Total_2 += randomNumber;

	sleep(1);
	
	pthread_mutex_unlock(&mutex_1);
	
	pthread_mutex_unlock(&mutex_2);
	
	void *ptr;

	return ptr;
}

int main(int argc, char *argv[]) 
{
	while(1) 
	{
														// Initializing the lock
    	pthread_mutex_init(&mutex_1, NULL);
    	pthread_mutex_init(&mutex_2, NULL);
    	
    	
    	pthread_t Th1, Th2, Th3;						// Creating the thread
    	pthread_create(&Th1, NULL, threadOne, NULL);
    	pthread_create(&Th2, NULL,  threadTwo, NULL);
    	pthread_create(&Th3, NULL, getTheSums, NULL);
    	
    	
    	pthread_join(Th1, NULL);						// Joining the thread
    	pthread_join(Th2, NULL);
    	pthread_join(Th3,NULL);

	}
	
	return 0;
}