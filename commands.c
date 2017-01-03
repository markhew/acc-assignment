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
		char hostname[HOSTLEN], realname[REALLEN];//Since these values are fixed from the begininng
		time_t time_joined;
		strcpy(hostname,connection.hostname);
		strcpy(realname,connection.realname);
		time_joined = connection.time_joined;


		char nData[100];
		char tData[50];
		char sData[150];
		snprintf(nData,sizeof(nData),"Server : (Hostname)  %s\nServer : (Realname) %s\n",hostname,realname);
		strftime(tData,sizeof(tData),"Server : (Joined) %X\n", localtime(&time_joined));
		snprintf(sData,sizeof(sData),"%s%s",nData,tData);
		Writen(sockfd,sData,strlen(sData));
		
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
