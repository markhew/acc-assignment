#include "acc.h"

int validateJOIN(int, char*);

void
validate(int sockfd ,char* sendline){
	char *cmd, *rest;
	char line[300];
	strcpy(line,sendline);

	cmd = strtok(line," "); //Validate the command first
	rest = strtok(NULL,"\n");

	if(strcmp(cmd,"JOIN") == 0 || strcmp(cmd,"JOIN\n") ==0 ) {
		if(validateJOIN(sockfd,rest) == 1){
			Writen(sockfd,sendline,strlen(sendline));
		}	
	}
	else if (strcmp(cmd,"MSG") == 0 || strcmp(cmd,"MSG\n") ==0 ){
		if(strlen(rest) < 0 ){
			printf("Client : Message has no content\n");
		}
		else if(strlen(rest) > 256){
			printf("Client : Length of message cannot be more than 256 characters long\n");
		}
		else{
			Writen(sockfd,sendline,strlen(sendline));
		}
	}

	else if(strcmp(cmd,"WHOIS") == 0 || strcmp(cmd,"WHOIS\n") ==0 ){
		if(rest == NULL || strcmp(rest,"") == 0){
			printf("Client : Who is who?\n");
		}
	}

	else if(strcmp(cmd,"TIME") == 0 || strcmp(cmd,"TIME\n") ==0 ||
			strcmp(cmd,"ALIVE") == 0 || strcmp(cmd,"ALIVE\n") ==0 ||
			strcmp(cmd,"QUIT") == 0 || strcmp(cmd,"QUIT\n") ==0){
		Writen(sockfd,sendline,strlen(sendline));

	}

	else{
			printf("Client : Invalid Command, valid commands are :\nJOIN, MSG, WHOIS, TIME, ALIVE, QUIT\n" );
	}
}

//Validate returns 1 if valid, returns 0 and outputs error if invalid
int
validateJOIN(int sockfd,char* names){
	char* format = "Client : JOIN <NICKNAME> <HOSTNAME> <REALNAME>\n";
	char* nicklen = "Client : Nickname cannot exceed 10 characters\n";
	char* hostlen = "Client : Hostname cannot exceed 10 characters\n";
	char* reallen = "CLient : Realname cannot exceed 20 characters\n";
	
	int valid = 1;

	if(names != NULL && strcmp(names,"")!=0){
	char *nickname, *hostname, *realname;
	char	str[INET_ADDRSTRLEN];
	nickname = strtok(names," ");
	hostname = strtok(NULL, " ");
	realname = strtok(NULL, "\n");

		if(nickname == NULL || hostname == NULL || realname == NULL){
			printf("%s\n", format);
			valid = 0;
		}
		else if( strlen(nickname) > 10){
			printf("%s\n", nicklen);
			valid = 0;
		}
		else if(strlen(hostname) > 10){
			printf("%s\n", hostlen);
			valid = 0;
		}
		else if(strlen(realname) > 20){
			printf("%s\n", reallen);
			valid = 0;
		}/* Potentially check host name 
		else{
			struct sockaddr_in	cliaddr;
			socklen_t len = sizeof(cliaddr);
			getsockname(sockfd, (SA*) &cliaddr, &len);
			
		}*/
	}
	else{
		valid = 0;
		printf("%s\n", format);
	}
	return valid;
}