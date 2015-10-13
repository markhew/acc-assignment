#include	"acc.h"

int stringChar(char*,char);

void
str_chat(int sockfd)
{
	ssize_t		n;
	char		line[MAXLINE];
	char*		timed_out_msg = "Server : Timed out\n";
	char*		still_alive_msg = "Server : Good to know :)\n";
	int*		status;

	for ( ; ; ) {
		n = Readline(sockfd, line, MAXLINE );
		if ( n == 0){
			return;		/* connection closed by other end */
		}
		if( errno == EAGAIN){ //If we receive an EAGAIN, make the time out occured
			Writen(sockfd,timed_out_msg,strlen(timed_out_msg));
			return;
		}
		if(strcmp(line,"ALIVE\n")==0)//If ALIVE is received, just continue to next loop
		{	
			Writen(sockfd,still_alive_msg,strlen(still_alive_msg));
			continue;
		}

		char str[MAXLINE];
		strcpy(str,line);


   		char *cmd;
   		char *rest;
   		
		int spc = stringChar(str,' ');
		
		/*

		This part of the code is to ensure that if the user enters a
		command like JOIN\n then the strtok wont result in "rest" which
		contains the rest of the information contain NULL
		*/

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
      	/*=================================================================*/

		if(strcmp(cmd,"JOIN")==0 || strcmp(cmd,"JOIN\n")==0){
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
			return;
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


