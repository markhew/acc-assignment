#include	"acc.h"

void
str_chat(int sockfd)
{
	ssize_t		n;
	char		line[MAXLINE];

	//printf("%d\n", max_idle_time );
	for ( ; ; ) {
		if ( (n = Readline(sockfd, line, MAXLINE)) == 0)
			return;		/* connection closed by other end */
		printf("Received Line : %s\n", line );
		//char* str = strtok(line, " ");
		
		//printf(str[0]);
		//printf("\n");

		Writen(sockfd, line, n);
	}
}
