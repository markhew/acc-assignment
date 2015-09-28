#include	"acc.h"




static void	*doit(void *);		/* each thread executes this function */
static void *rejectConn(void *);



//mutex for count for number of clients
pthread_mutex_t numClient_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t connection_mutex = PTHREAD_MUTEX_INITIALIZER;

int		numClients;
int		max_clients, max_idle_time;
strCon connections[MAXCLIENTS];

int
main(int argc, char **argv)
{
	int		listenfd, connfd;
	socklen_t	addrlen, len;
	pthread_t	tid,cid;

	struct sockaddr	*cliaddr;
	struct timeval timeout;
	numClients = 0;



	if (argc == 4){

		listenfd = Tcp_listen(NULL, argv[1], &addrlen);
		max_clients = atoi(argv[2]);
		max_idle_time = atoi(argv[3]);

	}
	else if (argc == 5){
		listenfd = Tcp_listen(argv[1], argv[2], &addrlen);
		max_clients = atoi(argv[3]);
		max_idle_time = atoi(argv[4]);
	}
	else{
		err_quit("usage: tcpserv01 [ <host> ] <service or port> <Max Clients> <Max Idle Time>");
	}

	if(max_clients < 1 || max_clients > 10){
		err_quit("Number of Clients must be between 1 and 10");
	}

	if(max_idle_time < 1 || max_idle_time > 120){
		err_quit("Max idle time must be between 1 and 120");
	}

	timeout.tv_sec = max_idle_time;


	//Setting up the connection list for the server
	for(int i=0; i<MAXCLIENTS;i++){
		resetCon(i);
	}


	cliaddr = (struct sockaddr *) Malloc(addrlen);

	for ( ; ; ) {
		len = addrlen;

		connfd = Accept(listenfd, cliaddr, &len);

		if(numClients < max_clients){
			Pthread_create(&tid, NULL, &doit, (void *) connfd);
	
			pthread_mutex_lock(&numClient_mutex);
			numClients++;
			pthread_mutex_unlock(&numClient_mutex);

		}

		else{
			Pthread_create(&cid, NULL, &rejectConn, (void*) connfd);
		}
	}
}

static void *
doit(void *arg)
{
	Pthread_detach(pthread_self());
	str_chat((int) arg);	 /*same function as before */
	Close((int) arg);	/* we are done with connected socket */

	pthread_mutex_lock(&numClient_mutex);
	numClients--;
	pthread_mutex_unlock(&numClient_mutex);

	return(NULL);
}

//Close connection after sending a single reject message
static void *
rejectConn(void *arg)
{
	Pthread_detach(pthread_self());

	char* connRef = "Sorry, Please Try again later \n";
	size_t n = strlen(connRef);
	
	Writen((int)arg, connRef, n);
	Shutdown((int)arg,SHUT_WR);

	return (NULL);		
}


