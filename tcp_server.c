/* A simple server in the internet domain using TCP
 * Answer the questions below in your writeup
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
    /* 1. What is argc and *argv[]?
     * argc is number of args passed in, argv is an array containing the args as c-strings
     */
    int sockfd, newsockfd, portno;
    /* 2. What is a UNIX file descriptor and file descriptor table?
     * A file descriptor is an integer that shows a kernel open file. The file descriptor table maps file descriptors to files.
     */
    socklen_t clilen;

    struct sockaddr_in serv_addr, cli_addr;
    /* 3. What is a struct? What's the structure of sockaddr_in?
     * A struct is a data type that holds variables of different types. sockaddr_in is a struct that holds an internet address.
     */

    int n;
    if (argc < 2)
    {
        fprintf(stderr, "ERROR, no port provided\n");
        exit(1);
    }

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    /* 4. What are the input parameters and return value of socket()
     * The input parameters are domain (internetwork), type (stream socket), and protocol (0 means default protocol). The return value is a file descriptor int.
     */

    if (sockfd < 0)
        error("ERROR opening socket");
    bzero((char *)&serv_addr, sizeof(serv_addr));
    portno = atoi(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    if (bind(sockfd, (struct sockaddr *)&serv_addr,
             sizeof(serv_addr)) < 0)
        error("ERROR on binding");
    /* 5. What are the input parameters of bind() and listen()?
     * bind() takes a file descriptor,pointer to sockaddr struct, and struct size. listen() takes file descriptor and backlog.
     */

    listen(sockfd, 5);
    clilen = sizeof(cli_addr);

    while (1)
    {
        /* 6.  Why use while(1)? Based on the code below, what problems might occur if there are multiple simultaneous connections to handle?
         * while(1) is an infinite loop so it keeps on running unless error occurs. the server will not be able to handle if multiple simultaneous connections exist.
         */

        char buffer[256];
        newsockfd = accept(sockfd,
                           (struct sockaddr *)&cli_addr,
                           &clilen);
        /* 7. Research how the command fork() works. How can it be applied here to better handle multiple connections?
         * fork() creates a duplicates the calling process and creates a new one. It handles multiple connections.
         */

        if (newsockfd < 0)
            error("ERROR on accept");
        bzero(buffer, 256);

        n = read(newsockfd, buffer, 255);
        if (n < 0)
            error("ERROR reading from socket");
        // printf("Here is the message: %s\n",buffer);
        n = write(newsockfd, "I got your message", 18);
        if (n < 0)
            error("ERROR writing to socket");
        close(newsockfd);
    }
    close(sockfd);
    return 0;
}

/* This program makes several system calls such as 'bind', and 'listen.' What exactly is a system call?
 * A system call is a request to the kernel of an OS.
 */