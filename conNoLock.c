#include "acc.h"
//Same functionality as findNickName it does not lock mutex as
//the function calling it already does
int
findNickName_NOLOCK(char* nickname){
	int idx = -1;
	int i;
	for( i=0; i<MAXCLIENTS;i++){
		if(idx < 0){ //Dont bother checking if index is found
			if(strcmp(connections[i].nickname, nickname) == 0){
				idx = i;
			}
		}
	}
	return idx;
}

//Same functionality as findConnFD() except it does not lock the
//mutex as the function calling it already does
int 
findConnFD_NOLOCK(int fd){
	int idx = -1;
	int i;
	for( i=0; i<MAXCLIENTS;i++){
		if(idx < 0){
			if(connections[i].sockfd == fd){
				idx = i;
			}
		}
	}
	return idx;
}