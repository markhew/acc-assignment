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
	char* cmd;
	while ((void *) Fgets(sendline, MAXLINE, fp) != NULL)
	{
		strcpy(line,sendline);

		cmd = strtok(line," ");


		if(strcmp(cmd,"JOIN") == 0 || strcmp(cmd,"JOIN\n") ==0 ||
			strcmp(cmd,"MSG") == 0 || strcmp(cmd,"MSG\n") ==0 ||
			strcmp(cmd,"WHOIS") == 0 || strcmp(cmd,"WHOIS\n") ==0 ||
			strcmp(cmd,"TIME") == 0 || strcmp(cmd,"TIME\n") ==0 ||
			strcmp(cmd,"ALIVE") == 0 || strcmp(cmd,"ALIVE\n") ==0 ||
			strcmp(cmd,"QUIT") == 0 || strcmp(cmd,"QUIT\n") ==0
			)
		{
			Writen(sockfd, sendline, strlen(sendline));
		}

		else{
			printf("Invalid Command, valid commands are :\nJOIN, MSG, WHOIS, TIME, ALIVE, QUIT\n" );
		}	
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

