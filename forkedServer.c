/* A simple server in the internet domain using TCP
   The port number is passed as an argument */

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
     int sockfd, newsockfd, portno;
     socklen_t clilen;
     char buffer[256];
     struct sockaddr_in serv_addr, cli_addr;
     int n, i;
     pid_t pid;

     int idSize = 100;
     char buf[idSize];
     char formattedString[idSize + 20];

     FILE * idFile = fopen("./drone_id.txt", "r");
  
     //  fgets( char *buf, int n, FILE *fp );
     fgets(buf, idSize, idFile);
  
     sprintf (formattedString, "my id is: %s\n", buf);
     printf("my id is: %s\n", buf);
     printf("my formattted id is: repeat: %s", formattedString);
     int outlen = strlen(formattedString);

     if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     }
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0) 
        error("ERROR opening socket");
     bzero((char *) &serv_addr, sizeof(serv_addr));
     portno = atoi(argv[1]);
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0) 
              error("ERROR on binding");
     listen(sockfd,5);
     clilen = sizeof(cli_addr);
     
     i = 0;
     while(1) {
       i++;

       newsockfd = accept(sockfd, 
			  (struct sockaddr *) &cli_addr, 
			  &clilen);       
       pid = fork();

       if (pid == 0) {
	 if (newsockfd < 0) 
	   error("ERROR on accept");
	 bzero(buffer,256);
	 n = read(newsockfd,buffer,255);
	 if (n < 0) error("ERROR reading from socket");
	 printf("Here is the message: %s\n",buffer);
/* 	 n = write(newsockfd,"my name is FAFSBU",18); */
	 n = write(newsockfd, formattedString, outlen);
	 if (n < 0) error("ERROR writing to socket");
	 break;
       }
       else {
	 continue;
       }
     }

     close(newsockfd);
     close(sockfd);  
     return 0; 
}