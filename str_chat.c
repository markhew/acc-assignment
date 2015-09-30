#include	"acc.h"

int stringChar(char*,char);

int
str_chat(int sockfd)
{
	ssize_t		n;
	char		line[MAXLINE];
	clock_t		tmr;

	for ( ; ; ) {
		n = Readline(sockfd, line, MAXLINE);
		
		if ( n == 0){
			return 0;		/* connection closed by other end */
		}
		if( n== EAGAIN){
			printf("EAGAIN\n");
		}
		

		char str[MAXLINE];
		strcpy(str,line);


   		char *cmd;
   		char *rest;
   		
		int spc = stringChar(str,' ');
		if(spc < 0){
			if(strlen(str) == 1){ //In Case user only enters '\n'
				char c[2] = " ";
				strcat(str,c);
			}
			cmd = strtok(str, "\n");
			rest = strdup("");
		}	
		else{
   		cmd = strtok(str, " ");
      	rest = strtok(NULL, "\n");
      	}

		if(strcmp(cmd,"JOIN")==0){
			join(sockfd,rest);
		}
		else if(strcmp(cmd,"WHOIS")==0){
			if(rest == NULL || strcmp(rest,"")==0){
				Writen(sockfd, "Who is who?\n",15);
			}
			else{
				whois(sockfd,rest);
			}
		}
		else if(strcmp(cmd,"TIME")==0){
			showTime(sockfd);
		}
		else if(strcmp(cmd,"MSG")==0){
			message(sockfd,rest);
		}
		else if(strcmp(cmd,"QUIT")==0){
			quit(sockfd,rest);
			return 0;
		}
		else{
			char* invalMsg = "Enter Valid Command(JOIN, MSG, WHOIS, TIME, ALIVE, QUIT)\n";

			Writen(sockfd,invalMsg,strlen(invalMsg));
		}
	
	}
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


