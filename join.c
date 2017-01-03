#include "acc.h"

void 
join(int sockfd, char* str){

	//Setting error messages for message input lengths and format;
	char* format = "Server : JOIN <NICKNAME> <HOSTNAME> <REALNAME>\n";
	char* nicklen = "Server : Nickname cannot exceed 10 characters\n";
	char* hostlen = "Server : Hostname cannot exceed 20 characters\n";
	char* reallen = "Server : Realname cannot exceed 20 characters\n";
	char names[MAXLINE];
	if(str != NULL && strcmp(str,"")!=0){
		strcpy(names,str);

		char* nickname, *hostname, *realname;
		nickname = strtok(names," ");
		hostname = strtok(NULL, " ");
		realname = strtok(NULL, "\n");

		//Check if there is actually a hostname and realname in the join command
		if(hostname == NULL || realname == NULL){
			Writen(sockfd,format, strlen(format));
		}
		else{	
			//Check that names do not exceed allocated character length
			if(strlen(nickname) > 10){
				Writen(sockfd,nicklen, strlen(nicklen));
			}
			if(strlen(hostname) > 20){
				Writen(sockfd,hostlen, strlen(hostlen));
			}
			if(strlen(realname) > 10){
				Writen(sockfd,reallen, strlen(hostlen));
			}
			else{

				int fDfound = -1; //For if the client has already joined
				int nicknameFound = -1; //For if the nickname is already taken
				int realnameFound = -1; //For if the person is already connected somewhere else

				//Go through list of connections to check if fd, nickname, real name are found
				pthread_mutex_lock(&connection_mutex);

				for (int i = 0; i < MAXCLIENTS; ++i)
				{
					if(sockfd == connections[i].sockfd){
						fDfound = i;
					}
					if(strcmp(nickname,connections[i].nickname) == 0){
						nicknameFound = i;
					}
					if(strcmp(realname,connections[i].realname) == 0){
						realnameFound = i;
					}
				}
				pthread_mutex_unlock(&connection_mutex);

				//Setting error messages for if names are in use
				char* rnFoundMsg = "Server : You are already connected to MNC\n";
				char* nnFoundMsg = "Server : Nickname already in use\n";
				char* aJoinedMsg = "Server : Already connected, please QUIT to start new Connection\n";

				//If real name or nickname is not unique, do not let user connect
				if(realnameFound >= 0){
					Writen(sockfd, rnFoundMsg,strlen(rnFoundMsg));
				}
				else if(nicknameFound >= 0){

					Writen(sockfd, nnFoundMsg,strlen(nnFoundMsg));
				}
				else if(fDfound >= 0){
						Writen(sockfd, aJoinedMsg, strlen(aJoinedMsg));	
				}
				else{
					int conIdx = setCon(sockfd, nickname, hostname, realname);
					if(conIdx >=0){
						char msg[100], bmsg[100];
						snprintf(msg, sizeof(msg), "Server : JOIN %s %s %s. Welcome to MNC!\n", nickname, hostname, realname);
						Writen(sockfd,msg,strlen(msg));
						snprintf(bmsg, sizeof(bmsg), "Server : Let us welcome a new user - %s\n",nickname);
						broadcast(bmsg,conIdx);
						Setsockopt(sockfd,SOL_SOCKET,SO_RCVTIMEO,&timeout, sizeof(timeout));
						//Set a timeout countdown after successfully joining

					}
				}
			}
		}
	}
	else{
		Writen(sockfd,format,strlen(format));
	}
	
	
}