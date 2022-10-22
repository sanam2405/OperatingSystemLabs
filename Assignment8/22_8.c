/*
Team 22
Team Member 1 - Md Areeb Akhtar (002011001100)
Team Member 2 - Ashfaq Murshed (002011001096)
Team Leader   - Manas Pratim Biswas (002011001025)
Date - 22/10/2022
*/

/*
Assignment Details - Consider a process with three threads A, B, and C. The default thread of the process
                     receives two inputs (X, Y) and places them in a queue that is accessible by all the
                     three threads A, B and C. For each pair of input (X,Y), we require that the request
                     must first be processed by thread A (Multiplication (X*Y)),then B(Division (X*Y)/2),
                     then C (Addition (X+Y)), then B again ( (X*Y) /(X+Y)), and finally by A((X+Y)* (X+Y))
                     before the pair (X,Y) can be removed and discarded from the queue.
                     Thread A must read the next request from the queue only after it is finished with all
                     the above steps of the previous one. Write down code for the functions run by the
                     threads A, B, and C, to enable this synchronization. You may use any
                     synchronization primitive of your choice to solve this question.

Input Description  - N, number of random pairs followed by N random pairs seperated by space
Output Description - Prints the results of the operations
*/

/*
Compilation Command (in Linux Bash Terminal) :- gcc 22_8.c
Execution Command (in Linux Bash Terminal) :- ./a.out 
*/

/*
Sample Input  - 

Enter N, the number of pairs : 5

Enter the pair 1 : 1 2

Enter the pair 2 : 3 4

Enter the pair 3 : 5 6

Enter the pair 4 : 7 8

Enter the pair 5 : 9 10

Sample Output -
Output :- (PROGRAM OUTPUT)

---------------------------------------------------------
 Thread A (X*Y) = 2 
 Thread B ((X*Y)/2) = 1.00 
 Thread C (X+Y) = 3 
 Thread B ((X*Y)/(X+Y)) = 0.67 
 Thread A ((X+Y)*(X+Y)) = 9 

 Thread A (X*Y) = 12 
 Thread B ((X*Y)/2) = 6.00 
 Thread C (X+Y) = 7 
 Thread B ((X*Y)/(X+Y)) = 1.71 
 Thread A ((X+Y)*(X+Y)) = 49 

 Thread A (X*Y) = 30 
 Thread B ((X*Y)/2) = 15.00 
 Thread C (X+Y) = 11 
 Thread B ((X*Y)/(X+Y)) = 2.73 
 Thread A ((X+Y)*(X+Y)) = 121 

 Thread A (X*Y) = 56 
 Thread B ((X*Y)/2) = 28.00 
 Thread C (X+Y) = 15 
 Thread B ((X*Y)/(X+Y)) = 3.73 
 Thread A ((X+Y)*(X+Y)) = 225 

 Thread A (X*Y) = 90 
 Thread B ((X*Y)/2) = 45.00 
 Thread C (X+Y) = 19 
 Thread B ((X*Y)/(X+Y)) = 4.74 
 Thread A ((X+Y)*(X+Y)) = 361 

All the operations have been completed!
---------------------------------------------------------

*/


// Header files
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>


pthread_mutex_t mutex;

void * dummy;       // Dummy pointer

void printLine()    // Method to print a line
{
    printf("---------------------------------------------------------\n");
}

// This is the queue where the front node stores the beginning node of
// the LL and the read node stores the ending node of the LL
struct Queue 
{
	struct QNode *front, *rear;
};

// A linked list (LL) node to store a queue entry
struct QNode 
{
	int item1;
    int item2;
	struct QNode* next;
};

// Method to create an empty queue
struct Queue* createQueue()
{
	struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue));
	q->front = q->rear = NULL;
	return q;
}

// Method to create a new linked list node.
struct QNode* newNode(int x,int y)
{
	struct QNode* temp = (struct QNode*) malloc(sizeof(struct QNode));
	temp->item1 = x;
    temp->item2 = y;
	temp->next = NULL;
	return temp;
}

// Method to enqueue into the queue
void enQueue(struct Queue* q, int x ,int y)
{
	// Create a new LL node
	struct QNode* temp = newNode(x,y);

	// If queue is empty, then new node is front and rear both
	if (q->rear == NULL) 
    {
		q->front = q->rear = temp;
		return;
	}

	// Add the new node at the end of queue and change rear
	q->rear->next = temp;
	q->rear = temp;
}

// Mehod to remove a key from the queue
void deQueue(struct Queue* q)
{
	// If queue is empty, returns NULL.
	if (q->front == NULL)
		return;

	// Stores previous front and move front by one node ahead
	struct QNode* temp = q->front;

	q->front = q->front->next;

	// If front becomes NULL, then rear is set to NULL
	if (q->front == NULL)
		q->rear = NULL;

	free(temp);
}

volatile int taskNo = 1;
void * methodA(void *args)
{
	struct Queue *q = (struct Queue *)args;
	while(q->front != NULL)
	{

		while((taskNo == 1 || taskNo == 5))
		{
			if(taskNo == 1)
			{
				pthread_mutex_lock(&mutex);
				if(q->front == NULL)
                                {
                                        printf("All the operations have been completed!\n");
                                        printLine();
                                        exit(0);
                                }
				int x = q->front->item1;
                int y = q->front->item2;
				int result = x*y;
				printf(" Thread A (X*Y) = %d \n",result);
				taskNo = 2;
				pthread_mutex_unlock(&mutex);
			}
			else if(taskNo == 5)
			{
				pthread_mutex_lock(&mutex);
				if(q->front == NULL)
                                {
                                        printf("All the operations have been completed!\n");
                                        printLine();
                                        exit(0);
                                }
			
                		int x = q->front->item1;
                		int y = q->front->item2;
                		int result = (x+y) * (x+y);
                		printf(" Thread A ((X+Y)*(X+Y)) = %d \n\n",result);
                		
				deQueue(q);

				taskNo = 1;
                pthread_mutex_unlock(&mutex);
			}

		}
	}

    return dummy;
}
void * methodB(void *args)
{
     struct Queue *q = (struct Queue *)args;
	 while(q->front != NULL)
        {

                while((taskNo == 2 || taskNo == 4))
                {
                        if(taskNo == 4)
                        {       pthread_mutex_lock(&mutex);
				                if(q->front == NULL)
                                {
                                        printf("All the operations have been completed!\n");
                                        printLine();
                                        exit(0);
                                }
                               
				int x = q->front->item1;
                int y = q->front->item2;
				double result = 0 ;
				if( (x+y) == 0 )
				{
					printf(" Thread B ((X*Y)/(X+Y)) = undefined \n");
				}
				else
				{
                     result = ((double) (x*y) / (x+y));
					 printf(" Thread B ((X*Y)/(X+Y)) = %0.2lf \n",result);
				}
                                taskNo = 5;
                                pthread_mutex_unlock(&mutex);
                        }

                        else if(taskNo == 2)
                        {       pthread_mutex_lock(&mutex);
				                if(q->front == NULL)
                                {
                                        printf("All the operations have been completed!\n");
                                        printLine();
                                        exit(0);
                                }

                                int x = q->front->item1;
				                int y = q->front->item2;
                                double result = ((double)(x*y)/2.0);
                                printf(" Thread B ((X*Y)/2) = %0.2lf \n",result);
                                taskNo = 3;
                                pthread_mutex_unlock(&mutex);
                        }

                }
        }
        return dummy;
}
void * methodC(void *args)
{
    struct Queue *q = (struct Queue *)args;
	while(q->front != NULL)
        {
             

                while(taskNo == 3)
                {
			        pthread_mutex_lock(&mutex);
			                    if(q->front == NULL)
                             	{
                                        printf("All the operations have been completed!\n");
                                        printLine();
                                        exit(0);
                                }
			        int x = q->front->item1;
                    int y = q->front->item2;
                    
                    int result = x+y;
                    printf(" Thread C (X+Y) = %d \n",result);
                    taskNo = 4;
                    pthread_mutex_unlock(&mutex);
                }
        }
        return dummy;
}


int main()
{
	int N;
	struct Queue* q = createQueue();

	printf("Enter N, the number of pairs : ");
	scanf("%d",&N);
	
	for(int i = 1 ; i <= N ; i++)
	{
		int x , y;
		printf("\nEnter the pair %d : ",i);
		scanf("%d %d",&x,&y);
		enQueue(q,x,y);
	}
	printf("\n");
    printLine();

	pthread_t A,B,C;
	
	pthread_mutex_init(&mutex,NULL);
	//Creating threads
	if( pthread_create(&A,NULL,&methodA,(void *)q) != 0 )
	{
		perror("Error in creating Thread A \n)");
		exit(0);
	}
	if( pthread_create(&B,NULL,&methodB,(void *)q) != 0 )
        {
                perror("Error in creating Thread B \n)");
                exit(0);
        }
	if( pthread_create(&C,NULL,&methodC,(void *)q) != 0 )
        {
                perror("Error in creating Thread C \n)");
                exit(0);
        }
			
	// Joining Threads 
        if( pthread_join(A,NULL) != 0 )
        {
                perror("Error in joining Thread A \n)");
                exit(0);
        }
	if( pthread_join(B,NULL) != 0 )
        {
                perror("Error in joining Thread B \n)");
                exit(0);
        }
	if( pthread_join(C,NULL) != 0 )
        {
                perror("Error in joining Thread C \n)");
                exit(0);
        }
	pthread_mutex_destroy(&mutex);

	return 0;
}
