#include	"acc.h"

void	*copyto(void *);
int stringChar(char*,char);


static int	sockfd;		/* global for both threads to access */
static FILE	*fp;

void
str_cli(FILE *fp_arg, int sockfd_arg)
{
	char		recvline[MAXLINE];
	pthread_t	tid;

	sockfd = sockfd_arg;	/* copy arguments to externals */
	fp = fp_arg;

	/* does no pass argument */
	Pthread_create(&tid, NULL, copyto, NULL);

	while (Readline(sockfd, recvline, MAXLINE) > 0){
		Fputs(recvline, stdout);
	}
}

void *
copyto(void *arg)
{
	char	sendline[MAXLINE];
	char 	line[MAXLINE]; //for client side validation
	while ((void *) Fgets(sendline, MAXLINE, fp) != NULL)
	{
		validate(sockfd,sendline);	//Validates and sends the input	
	}

	Shutdown(sockfd, SHUT_WR);	/* EOF on stdin, send FIN */

	return(NULL);
	/* 4return (i.e., thread terminates) when end-of-file on stdin */
}

int
stringChar(char* string, char c){
	int idx = -1;
	int i;

	for(i=0;i<strlen(string);i++){
		if(string[i] == c){
			idx = i;
		}
	}
	return idx;
}

