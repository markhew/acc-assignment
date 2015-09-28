#include	"acc.h"

void join(int, char*);
void
str_chat(int sockfd)
{
	ssize_t		n;
	char		line[MAXLINE];
	clock_t		tmr;

	for ( ; ; ) {
		n = Readline(sockfd, line, MAXLINE);
		
		if ( n == 0){
			return;		/* connection closed by other end */
		}

		char str[MAXLINE];
		strcpy(str,line);

   		char *cmd;
   		char *rest;

   

   		cmd = strtok(str, " ");
      	rest = strtok(NULL, "\n");


		if(strcmp(cmd,"JOIN")==0){
			join(sockfd,rest);
		}   
		else{
			printf("Invalid Command : %s\n",cmd);
		}


		Writen(sockfd, line, n);
	}
}

void 
join(int sockfd, char* rest){
	printf("JOINING CHAT\n" );
	


}
