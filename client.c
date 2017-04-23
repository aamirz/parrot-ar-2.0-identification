/*****************************************
* Author: Robert Ingalls
*****************************************/
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

void error(char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
    int sockfd, portno, n;

    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[256];
    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);

    bzero(buffer,256);
/*     printf("buffer zeroed, now connecting...\n"); */
    if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0)
        error("ERROR connecting");

    // ORIGINAL 
/*     printf("Please enter the message: "); */
/*     bzero(buffer,256); */
/*     fgets(buffer,255,stdin); */
/*     n = write(sockfd,buffer,strlen(buffer)); */
/*     if (n < 0) */
/*          error("ERROR writing to socket"); */
/*     n = write(sockfd,"i love cake",strlen("i love cake")); */
    if (n < 0)
      error("didn't give message to server");
    n = read(sockfd,buffer,30);
/*     printf("passed read on client side \n"); */
    if (n < 0)
         error("ERROR reading from socket");
    printf("%s\n",buffer);
    return 0;
}
