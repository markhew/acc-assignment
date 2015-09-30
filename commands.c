#include "acc.h"
void
whois(int sockfd, char* nickname){
	int index = findNickName(nickname);
	if(index < 0){
		Writen(sockfd, "User not found\n",20);
	}
	else{
		pthread_mutex_lock(&connection_mutex);
		
		strCon connection = connections[index];
		char* msg = "THAT IS YOU\n";
		if(connection.sockfd == sockfd){
			Writen(sockfd, msg, strlen(msg));
		}	
		char hostname[10], realname[20];//Since these values are fixed from the begininng
		time_t time_joined;
		strcpy(hostname,connection.hostname);
		strcpy(realname,connection.realname);
		time_joined = connection.time_joined;


		char data[50];
		snprintf(data,sizeof(data),"Server : (Hostname)  %s\n",hostname);
		Writen(sockfd,data,strlen(data));
		snprintf(data,sizeof(data),"Server : (Realname) %s\n",realname);
		Writen(sockfd,data,strlen(data));
		strftime(data,sizeof(data),"Server : (Joined) %X\n", localtime(&time_joined));
		Writen(sockfd,data,strlen(data));
		
		pthread_mutex_unlock(&connection_mutex);

		
		
	}
}
//Function to display the current local time for the server to the client
void
showTime(int sockfd){
	time_t t;
  	struct tm * currTime;

	time(&t);
	currTime = localtime(&t);

	char sTime[60];
	strftime(sTime,sizeof(sTime),"Server : Local time here %X\n", currTime);
	
	Writen(sockfd,sTime,strlen(sTime));
}

void
quit(int sockfd, char* qMsg){
	char quitMsg[256];
	char* default_msg = "Bye all!\n";
	char msg[256];
	char nickname[20]; //Nickname cant be more than 20 characters long
	int connIdx = findConnFD(sockfd);
	
	if(connIdx >= 0){ //Dont send a message if not joined	

		//Get the nickname of the connected client
		pthread_mutex_lock(&connection_mutex);
		strcpy(nickname,connections[connIdx].nickname);
		pthread_mutex_unlock(&connection_mutex);

		//If there is no quit message, use the default one
		if(qMsg == NULL || strcmp(qMsg,"")==0){
			strcpy(quitMsg, default_msg);
		}
		else{
			strcpy(quitMsg,qMsg);
		}

		snprintf(msg,sizeof(msg),"%s : %s\n",nickname,quitMsg);

		//Broadcast the quit message
		broadcast(msg,connIdx);


	}


}
