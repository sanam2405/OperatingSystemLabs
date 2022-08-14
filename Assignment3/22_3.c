/*

Team 22
Team Member 1 - Md Areeb Akhtar (002011001100)
Team Member 2 - Ashfaq Murshed (002011001096)
Team Leader   - Manas Pratim Biswas (002011001025)

Date - 13/08/2022

*/

/*

Assignment Details - Create two processes. Transfer 1GB file from process1 to process2 using a
                     Socket. Now, transfer that file from process2 to process1 using the same
                     Socket.Now, compare the two files to make sure that the same file has returned back.
                     Also, print the time required to do this double transfer. Attach this output to the
                     source file as a comment. Please note that, you can see the socket which your program creates. There
                     are also various bash shell commands available to see the sockets created by
                     the program. So, once your program creates the socket, make sure you use
                     proper command to see the socket info and paste that output as a comment in
                     your source file.

Input Description  - No input

Output Description - The time required for the round about travel is printed on the screen.

*/

/*

Command for creating a 1GB file :- fallocate -l 1G initialBigFile.txt
NOTE - This file has to be created in the same directory as that of the program

Compilation Command (in Linux Bash Terminal) :- gcc 22_3.c

Execution Command (in Linux Bash Terminal) :- ./a.out initialBigFile.txt

*/

/*

Sample Input  - No input
Sample Output -

Output :- (PROGRAM OUTPUT)

>>> Server side socket is created successfully!
>>> Server bind to server is suceessful!
>>> Server is now listening suceessfully at port 8069
>>> Client side socket is created successfully!
>>> Client connected to the server successfully!
>>> Server connected to the client successfully!
>>> Comparing the files...
>>> The files are compared and found to be the same
>>> The round-about time for the file transfer is : 6178 milliseconds
>>> Cleaning the created files!
>>> The created files are cleaned!


Output :- (CHECKING THE SOCKET DETAILS)
Linux Bash Command :- ss -t -a

State     Recv-Q Send-Q                              Local Address:Port                   Peer Address:Port  Process
LISTEN    0      4096                                127.0.0.53%lo:domain                      0.0.0.0:*
LISTEN    0      5                                       127.0.0.1:ipp                         0.0.0.0:*
ESTAB     0      0                                   192.168.29.89:56956                 35.163.89.233:https
ESTAB     0      0                                   192.168.29.89:49904               137.134.250.187:https
TIME-WAIT 0      0                                       127.0.0.1:43908                     127.0.0.1:8069
ESTAB     0      0                                   192.168.29.89:52664                   18.66.85.28:https
ESTAB     0      0                                   192.168.29.89:45400                51.116.253.168:https
ESTAB     0      0                                   192.168.29.89:59308                  157.240.1.60:https
LISTEN    0      5                                           [::1]:ipp                            [::]:*
TIME-WAIT 0      0        [2405:201:8004:f048:10ca:970e:6e7d:a302]:45796    [2404:6800:4009:829::2005]:https
ESTAB     0      0        [2405:201:8004:f048:10ca:970e:6e7d:a302]:36212    [2404:6800:4009:828::2003]:https
TIME-WAIT 0      0        [2405:201:8004:f048:10ca:970e:6e7d:a302]:45798    [2404:6800:4009:829::2005]:https
ESTAB     0      0        [2405:201:8004:f048:10ca:970e:6e7d:a302]:39486    [2404:6800:4009:812::2005]:https


Output :-
Linux Bash Command :- ls - l

total 44
-rw-rw-r-- 1 manas manas 18898 Aug 13 21:33 22_3.c
-rwxrwxr-x 1 manas manas 22184 Aug 13 21:31 a.out

*/

// Header files
#include <arpa/inet.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#define TEMP_FILE1 "process1_temporary_file"
#define TEMP_FILE2 "process2_temporary_file"

#define MAXLEN 1024
#define LOCALHOST "127.0.0.1" // IP address of the local host
#define PORT 8069             // Port number

// Method to get the time elapsed since the invoking of this function
long getTimeElapsed()
{
    struct timeval timeElapsed;
    gettimeofday(&timeElapsed, NULL);
    return timeElapsed.tv_sec * 1000 + timeElapsed.tv_usec / 1000;
}

// Method for cleaning the created files
void cleanFiles()
{
    printf(">>> Cleaning the created files!\n");

    remove(TEMP_FILE1);
    remove(TEMP_FILE2);
    remove("initialBigFile.txt");

    printf(">>> The created files are cleaned!\n");
}

// Method to compare two files and check if there is any mismatch or not
int compareFiles(char *firstFile, char *secondFile)
{
    int fileID1, fileID2; // File IDs of the files

    // Open the initial input file
    if ((fileID1 = open(firstFile, O_RDONLY)) == -1)
    {
        perror(">>> Error in opening the file!\n");
        return -1;
    }

    // Open the received file
    if ((fileID2 = open(secondFile, O_RDONLY)) == -1)
    {
        perror(">>> Error in opening the file!\n");
        if (close(fileID2) == -1)
        {
            perror(">>> Error in closing the file!\n");
        }
        return -1;
    }

    // Buffers to store contents of the file which can be later matched if they are identical
    char buffer1[MAXLEN];
    char buffer2[MAXLEN];

    int returnValue = 1;

    while (true)
    {
        int len1 = read(fileID1, buffer1, MAXLEN);
        int len2 = read(fileID2, buffer2, MAXLEN);
        // If length of the files are -1 then there occurs an error in reading file
        if (len1 == -1 || len2 == -1)
        {
            perror(">>> Error in reading the file!\n");
            returnValue = -1;
            break;
        }

        // If the sent and received files are different then their length will differ
        if (len1 != len2)
        {
            returnValue = 0;
            break;
        }

        // If length is 0 , it means we have read the whole file and reached EOF
        if (len1 == 0)
        {
            break;
        }

        // if len1 > 0, we continiue to read.
        for (int i = 0; i < len1; i++)
        {
            if (buffer1[i] != buffer2[i])
            {
                // Files are different in their input, hence error has occured while transmission
                returnValue = 0;
                break;
            }
        }

        if (returnValue == 0)
        {
            break;
        }
    }

    // Close the files after reading and checking them
    if (close(fileID1) == -1)
    {
        perror(">>> Error in closing the file!\n");
        return -1;
    }

    if (close(fileID2) == -1)
    {
        perror(">>> Error in closing the file!\n");
        return -1;
    }

    return returnValue;
}

// Method to get the file size in bytes, this allows us to validate that the entire file has reached the other side
long getFileSize(char *fileName)
{
    FILE *file;

    // Opening the file
    if ((file = fopen(fileName, "r")) == NULL)
    {
        perror(">>> Error in fopen. Unable to determine file size\n");
        return -1;
    }

    // Taking the pointer to the end of the file
    if (fseek(file, 0, SEEK_END) == -1)
    {
        perror(">>> Error in fseek. Unable to determine file size\n");
        return -1;
    }

    // Gets the size of the file, by calulating the difference between the start of the file and the current position of the pointer in the file
    long fileSize = ftell(file);

    // If size could not be determined then -1
    if (fileSize == -1)
    {
        perror(">>> Error in ftell. Unable to determine file size\n");
        return -1;
    }

    return fileSize;
}

// Sending the file via the socket
int sendFile(char *sourceFile, int destination)
{

    // Getting the size of the file
    long fileSize = getFileSize(sourceFile);

    // Error in getting the size of the file
    if (fileSize == -1)
    {
        return -1;
    }

    // Buffer/packet to be sent
    char buffer[MAXLEN];

    // First message sent is the size of the file
    *((long *)buffer) = fileSize;

    // Sending the file size to the other side so that the other side can determine of the entire file has been received or not
    if (send(destination, buffer, sizeof(long), 0) < 0)
    {
        perror(">>> Error in sending the file!\n");
        return -1;
    }

    // Opening the file whose content is to be sent
    int fileID = open(sourceFile, O_RDONLY);

    // If there is an error in opening the file then -1
    if (fileID == -1)
    {
        perror(">>> Error in opening the file!\n");
        return -1;
    }

    int returnValue = 1;

    // An infinite loop untill the entire file is sent
    while (1)
    {

        // Reading from the file into the buffer
        long bufferRead = read(fileID, buffer, MAXLEN);

        // If any error occured then -1
        if (bufferRead < 0)
        {
            perror(">>> Error in reading the file!\n");
            returnValue = -1;
            break;
        }

        if (bufferRead == 0)
            break; // EOF is reached

        // Sending the buffer/packet to the other side of the socket, if there is any failure then -1
        if (send(destination, buffer, bufferRead, 0) == -1)
        {
            returnValue = -1;
            break;
        }
    }

    // Closing the file
    if (close(fileID) == -1)
    {
        perror(">>> Error in closing the file!\n");
        return -1;
    }

    // returns 1 is success
    return returnValue;
}

// Receiving the file via the socket
int receiveFile(char *destinationFile, int source)
{

    char buffer[MAXLEN];

    // Receives the filesize so as to authenticate that the entire file has been received or not
    if (recv(source, buffer, sizeof(long), 0) < 0)
    {
        perror(">>> Error in receiving the file!\n");
        return -1;
    }

    // Size of the file
    long fileSize = *((long *)buffer);

    // Opening the destination file, where the contents received via socket will be stored
    int destinationID = open(destinationFile, O_WRONLY | O_CREAT, 0666);

    if (destinationID < 0)
    {
        perror(">>> Error in opening the file!\n");
        return -1;
    }

    long toReceive = fileSize;

    int returnValue = 1;

    // An infinite loop until the file has been received
    while (toReceive > 0)
    {

        // Receiving the contents in the form of packets
        int bytesRead = recv(source, buffer, MAXLEN, 0);

        // is negative is there is an error while recieving the contents of the file
        if (bytesRead < 0)
        {
            perror(">>> Error in reading!\n");
            returnValue = -1;
            break;
        }

        if (bytesRead == 0) // EOF has been reached
            break;

        // Writing into the destination file
        if (write(destinationID, buffer, bytesRead) < 0)
        {
            perror(">>> Error in writing!\n");
            returnValue = -1;
            break;
        }

        toReceive -= bytesRead;
    }

    if (close(destinationID) < 0)
    {
        perror(">>> Error in closing the file!\n");
        return -1;
    }

    // If the file has been recieved successfully then returns 1
    return returnValue;
}

// Creating the server
int createServer()
{

    int serverID;

    // Creating the server side interface using TCP/IP protocols
    serverID = socket(AF_INET, SOCK_STREAM, 0);

    // If there is a failure in creating the server then -1
    if (serverID < 0)
    {
        perror(">>> Unable to create server side socket!\n");
        return serverID;
    }
    printf(">>> Server side socket is created successfully!\n");

    // Server side address information
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;   // IPv4 family of addresses
    server_address.sin_port = htons(PORT); // Adding the port number
    server_address.sin_addr.s_addr = INADDR_ANY;
    bzero(&server_address.sin_zero, 8);

    // Binding the server address to the socket created, if it fails to bind then -1
    if (bind(serverID, (const struct sockaddr *)&server_address, sizeof(server_address)) < 0)
    {
        perror(">>> Error in binding to the server!\n");

        if (close(serverID) == -1)
        {
            perror(">>> Error in closing the server!\n");
        }

        return -1;
    }

    printf(">>> Server bind to server is suceessful!\n");

    // Listening for the clients
    if (listen(serverID, 1) < 0)
    {
        perror(">>> Error in server listening!\n");
        if (close(serverID) == -1)
        {
            perror(">>> Error closing!!!\n");
        }

        return -1;
    }

    printf(">>> Server is now listening suceessfully at port %d\n", PORT);

    // Returning the server side descripter
    return serverID;
}

// To connect to the server to client
int acceptConnection(int serverID)
{

    int connectionfd;                 // Connection socket file descriptor
    struct sockaddr_in clientAddress; // A sockaddr_in for client
    unsigned int addressLength = sizeof(clientAddress);

    // Accepting the client and connecting to the server
    connectionfd = accept(serverID, (struct sockaddr *)&clientAddress, &addressLength);

    // When it fails to accept the client then -1
    if (connectionfd < 0)
    {
        perror(">>> Server could not accept connection!\n");
        return -1;
    }

    // Return server side descriptor
    return connectionfd;
}

// To connect the client to the server
int connectToServer()
{

    // Creating the client side of socket interface using TCP/IP protocols
    int clientID = socket(AF_INET, SOCK_STREAM, 0);

    // If it fails to create the socket then -1
    if (clientID < 0)
    {
        perror(">>> Error in creating client side socket!\n");
        return clientID;
    }
    printf(">>> Client side socket is created successfully!\n");

    // Address details
    struct sockaddr_in clientAddress;
    clientAddress.sin_family = AF_INET;   // IPv4 address family
    clientAddress.sin_port = htons(PORT); // Adding port to the address
    clientAddress.sin_addr.s_addr = inet_addr(LOCALHOST);
    bzero(&clientAddress.sin_zero, 8);

    // Connecting the server side of the socket, when it fails to connect then -1
    if (connect(clientID, (struct sockaddr *)&clientAddress, sizeof(clientAddress)) < 0)
    {
        perror(">>> Client could not connect!\n");

        if (close(clientID) == -1)
        {
            perror(">>> Error in closing client!\n");
        }
        return -1;
    }

    // Returning client side descriptor
    return clientID;
}

// process1 (server side program)
void process1(char *sourceFile)
{

    // Creating a server socket
    int serverID = createServer();

    // Server id is negative if the server socket fails to get created
    if (serverID < 0)
    {
        perror(">>> Creation of server failed!\n");
        exit(EXIT_FAILURE);
    }

    // Connecting to a client
    int connectID = acceptConnection(serverID);

    // Connect ID is negative if the server is not connected the client
    if (connectID < 0)
    {
        perror(">>> Connection failed!\n");
        exit(EXIT_FAILURE);
    }

    printf(">>> Server connected to the client successfully!\n");

    long startingTime = getTimeElapsed();

    // Sending to the client
    if (sendFile(sourceFile, connectID) < 0)
    {
        if (close(connectID) < 0)
        {
            perror(">>> Error in closing!\n");
        }
        if (close(serverID) < 0)
        {
            perror(">>> Error in closing!\n");
        }

        exit(EXIT_FAILURE);
    }

    // receiving the file from the client
    if (receiveFile(TEMP_FILE1, connectID) < 0)
    {
        if (close(connectID) < 0)
        {
            perror(">>> Error in closing!\n");
        }
        if (close(serverID) < 0)
        {
            perror(">>> Error in closing\n");
        }

        exit(EXIT_FAILURE);
    }

    long endingTime = getTimeElapsed();

    // Calculating the round-about time for transferring the file between process1 and process2 and back to process1
    long totalTimeTaken = endingTime - startingTime;

    printf(">>> Comparing the files...\n");

    // Compares the contents of the file
    if (compareFiles(sourceFile, TEMP_FILE1) > 0)
    {
        printf(">>> The files are compared and found to be the same\n");
        printf(">>> The round-about time for the file transfer is : %ld milliseconds\n", totalTimeTaken);
    }
    else
    {
        printf(">>> Mismatch found in the files!\n");
    }

    // Closing the connection to the socket
    if (close(connectID) < 0)
    {
        perror(">>> Error in closing!\n");
    }

    if (close(serverID) < 0)
    {
        perror(">>> Error in closing!\n");
    }

    cleanFiles(); // Method for cleaning the created files
}

// process2 (client side program)
void process2()
{

    int clientID = connectToServer(); // Method to connect to server

    // ClientID is -1 for failure in connection
    if (clientID < 0)
    {
        perror(">>> Connecting to server failed!\n");
        exit(EXIT_FAILURE);
    }

    printf(">>> Client connected to the server successfully!\n");

    // Receiving file via the socket (from the server)
    if (receiveFile(TEMP_FILE2, clientID) == -1)
    {
        if (close(clientID) < 0)
        {
            perror(">>> Error in closing!\n");
        }
        exit(EXIT_FAILURE);
    }

    // Sending file via the socket (from the client)
    if (sendFile(TEMP_FILE2, clientID) < 0)
    {
        if (close(clientID) == -1)
        {
            perror(">>> Error in closing!\n");
        }

        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[argc + 1])
{
    // cheacking the number og arguments
    if (argc != 2)
    {
        printf(">>> The number of arguments must be equal 1!\n");
        return 1;
    }

    // The path of the file which is to be sent and received via the sockets
    char *sourceFilePath = argv[1];

    // Forking to create two processes (parent and child)
    pid_t forkID = fork();

    // Fork id is negative if the program is unable to fork
    if (forkID < 0)
    {
        perror(">>> An error occured in forking...\n");
        return 1;
    }

    else if (forkID == 0)
    {
        // Child process (process2)
        process2();
    }

    else
    {
        // Parent process (process1)
        process1(sourceFilePath);
    }

    return 0;
}
