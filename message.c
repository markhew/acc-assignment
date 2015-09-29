#include "acc.h";


void 
message(int senderFd, char* target_msg){

	char* no_conn = "Server : You must JOIN before you can send messages\n";
	char* wrong_format = "Server : MSG <target> <message> required\n";	
	char* empty_msg = "Server : Your message has no text\n";
	char* msg_too_long = "Server : message length cannot exceed 256 characters\n";

	int senderIdx = findConnFD(senderFd);


	if(senderIdx < 0){ //If the sender has not yet joined just end
		Writen(senderFd,no_conn,strlen(no_conn));
		return; //Easier to read than nesting the rest in an "else"
	}
	//Making sure that <target> <message> is not NULL
	if(target_msg == NULL || strcmp(target_msg,"")==0){
		Writen(senderFd,wrong_format,strlen(wrong_format));
		return; 
	}

	char* target;
	target = strtok(target_msg, " ");
	
	int targetIndex = findNickName(target);
	if(targetIndex < 0){ //IF nickname is not found notify sender and end
		char no_target[60];
		snprintf(no_target,sizeof(no_target),"Server : User \"%s\" not found\n",target);
		Writen(senderFd,no_target,strlen(no_target));
		return;
	}

	char* msg;
	msg = strtok(NULL,"\n");
	if(msg == NULL || strcmp(msg,"")==0){ //If message is empty Notify user, " " is counted as message 
		Writen(senderFd,empty_msg,strlen(empty_msg));
	}
	else if(strlen(msg)> 256){
		Writen(senderFd,msg_too_long,strlen(msg_too_long));
	}
	else{
		pthread_mutex_lock(&connection_mutex);

		char* sender = connections[senderIdx].nickname;
		char message[300];
		snprintf(message,sizeof(message),"%s : %s\n",sender,msg);
		int targetfd = connections[targetIndex].sockfd;
		Writen(targetfd,message,strlen(message));
		pthread_mutex_unlock(&connection_mutex);

	}

	return;
}