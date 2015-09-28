#include	"acc.h"



static void	*doit(void *);		/* each thread executes this function */
int		numClients;
int		max_clients, max_idle_time;

int
main(int argc, char **argv)
{
	int		listenfd, connfd;
	socklen_t	addrlen, len;
	pthread_t	tid;
	struct sockaddr	*cliaddr;
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

	cliaddr = (struct sockaddr *) Malloc(addrlen);

	for ( ; ; ) {
		len = addrlen;
		connfd = Accept(listenfd, cliaddr, &len);

		Pthread_create(&tid, NULL, &doit, (void *) connfd);
		numClients++;
		printf("%d clients connected\n", numClients);
	}
}

static void *
doit(void *arg)
{
	Pthread_detach(pthread_self());
	str_chat((int) arg);	 /*same function as before */
	Close((int) arg);	/* we are done with connected socket */
	numClients--;
	printf("%d clients connected\n", numClients);
	return(NULL);
}
