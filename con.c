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

void
setCon(int fd, char* nick, char* host, char* real){
	pthread_mutex_lock(&connection_mutex);
	int idx = -1;
	//Loop through the connections to find the first free one
	for(int i=0; i< MAXLINE; i++){
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

	if(idx >= 0){
		printf("HELLO\n");
		printf("STATUS %d\n", connections[idx].status);
		printf("FD %d\n", connections[idx].sockfd);
		printf("NICKNAME %s\n", connections[idx].nickname);
		printf("HOSTNAME %s\n", connections[idx].hostname);
		printf("REALNAME %s\n", connections[idx].realname);

	}

}