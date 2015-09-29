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


		char data[40];
		snprintf(data,sizeof(data),"Hostname : %s\n",hostname);
		Writen(sockfd,data,strlen(data));
		snprintf(data,sizeof(data),"Realname : %s\n",realname);
		Writen(sockfd,data,strlen(data));
		strftime(data,sizeof(data),"Time Joined : %X\n", localtime(&time_joined));
		Writen(sockfd,data,strlen(data));
		
		pthread_mutex_unlock(&connection_mutex);

		
		
	}
}

void
showTime(int sockfd){
	time_t t;
  	struct tm * currTime;

	time(&t);
	currTime = localtime(&t);

	char sTime[60];
	strftime(sTime,sizeof(sTime),"Server local time : %X\n", currTime);
	
	Writen(sockfd,sTime,strlen(sTime));
}