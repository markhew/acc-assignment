#include "acc.h"
const char* noCon = "NO_CONN";

void
resetCon(int index){
	pthread_mutex_lock(&connection_mutex);
	connections[index].status = NOCONN;
	strcpy(connections[index].nickname,noCon);
	strcpy(connections[index].hostname,noCon);
	strcpy(connections[index].realname,noCon);
	connections[index].sockfd = 999999;
	pthread_mutex_unlock(&connection_mutex);

}


int
setCon(int fd, char* nick, char* host, char* real){
	pthread_mutex_lock(&connection_mutex);
	int idx = -1;
	//Loop through the connections to find the first free one
	for(int i=0; i< MAXCLIENTS; i++){
		if(idx < 0){
			if(connections[i].status == NOCONN){
				idx = i;
			}
		}
	}
	if(idx >= 0){
		connections[idx].status = CONN;
		strcpy(connections[idx].nickname, nick);
		strcpy(connections[idx].hostname, host);
		strcpy(connections[idx].realname, real);
		connections[idx].sockfd = fd;
	}

	pthread_mutex_unlock(&connection_mutex);

	
	return idx;

}

//Finds the index of the appropriate socket fd in the connections array
int 
findConnFD(int fd){
	int idx = -1;
	pthread_mutex_lock(&connection_mutex);
	for(int i=0; i<MAXCLIENTS;i++){
		if(idx < 0){
			if(connections[i].sockfd == fd){
				idx = i;
			}
		}
	}
	pthread_mutex_unlock(&connection_mutex);
	return idx;
}

void
broadcast(char* msg, int index){
	pthread_mutex_lock(&connection_mutex);

	for(int i=0;i<MAXCLIENTS;i++){
		if(connections[i].status == CONN && index != i){
			Writen(connections[i].sockfd,msg, strlen(msg));
		}
	}
	pthread_mutex_unlock(&connection_mutex);


}