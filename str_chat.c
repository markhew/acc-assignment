#include	"acc.h"

void join(int);
void
str_chat(int sockfd)
{
	ssize_t		n;
	char		line[MAXLINE];

	for ( ; ; ) {
		if ( (n = Readline(sockfd, line, MAXLINE)) == 0)
			return;		/* connection closed by other end */
		
		char str[MAXLINE];
		strcpy(str,line);

   		char *token;
   

   		token = strtok(str, " ");

		if(strcmp(token,"JOIN")==0){
			join(sockfd);
		}   
		else{
			printf("Invalid Command : %s\n",token);
			printf("%s\n", str);
		}


		Writen(sockfd, line, n);
	}
}

void 
join(int sockfd){
	printf("JOINING CHAT\n" );
}
