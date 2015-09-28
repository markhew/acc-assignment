#include "acc.h"

void 
join(int sockfd, char* str){

	printf("JOINING CHAT\n" );
	char names[MAXLINE];
	if(str != NULL){
		strcpy(names,str);

		char* nickname, *hostname, *realname;
		nickname = strtok(names," ");
		hostname = strtok(NULL, " ");
		realname = strtok(NULL, "\n");

		//Check if there is actually a hostname and realname in the join command
		if(hostname == NULL || realname == NULL){
			Writen(sockfd,"JOIN <NICKNAME> <HOSTNAME> <REALNAME>\n", 40);
		}
		else{	
			//Check that names do not exceed allocated character length
			if(strlen(nickname) > 10){
				Writen(sockfd,"Nickname cannot exceed 10 characters\n", 40);
			}
			if(strlen(hostname) > 10){
				Writen(sockfd,"Hostname cannot exceed 10 characters\n", 40);
			}
			if(strlen(realname) > 10){
				Writen(sockfd,"Realname cannot exceed 20 characters\n", 40);
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

				//If real name or nickname is not unique, do not let user connect
				if(realnameFound >= 0){
					Writen(sockfd, "You are already connected\n",30);
				}
				else if(nicknameFound >= 0){

					Writen(sockfd, "Nickname taken\n",23);
				}
				else if(fDfound >= 0){
						Writen(sockfd, "Already connected, please QUIT to start new Connection\n",60);
					
				}
				else{
					int conIdx = setCon(sockfd, nickname, hostname, realname);
					if(conIdx >=0){
						char msg[100], bmsg[100];
						snprintf(msg, sizeof(msg), "Server : JOIN %s %s %s. Welcome to MNC!\n", nickname, hostname, realname);
						Writen(sockfd,msg,strlen(msg));
						snprintf(bmsg, sizeof(bmsg), "Server : Let us welcome a new user - %s\n",nickname);
						broadcast(bmsg,conIdx);
					}
				}
			}
		}
	}
	else{
		Writen(sockfd,"JOIN <NICKNAME> <HOSTNAME> <REALNAME>\n", 40);
	}
	
	
}