#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <errno.h>
#include <netdb.h>
#include <sys/uio.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <pthread.h>
#include <sys/stat.h>
#include <signal.h>



#ifdef	HAVE_PTHREAD_H
#include	<pthread.h>
#endif


#define	MAXLINE	4096
#define	LISTENQ	1024
#define	SERV_TCP_PORT	52001
#define	OK	52001
#define	SA	struct sockaddr
#define MAXCLIENTS 10
#define NOCONN 0
#define CONN 1
/* Our own header for the programs that use threads.
   Include this file, instead of "unp.h". */


#ifndef		__unp_pthread_h
#define		__unp_pthread_h


void	Pthread_create(pthread_t *, const pthread_attr_t *, void * (*)(void *), void *);
   /*void * (*)(void *), void *);*/
void	Pthread_join(pthread_t, void **);
void	Pthread_detach(pthread_t);
void	Pthread_kill(pthread_t, int);

void	Pthread_mutexattr_init(pthread_mutexattr_t *);
void	Pthread_mutexattr_setpshared(pthread_mutexattr_t *, int);
void	Pthread_mutex_init(pthread_mutex_t *, pthread_mutexattr_t *);
void	Pthread_mutex_lock(pthread_mutex_t *);
void	Pthread_mutex_unlock(pthread_mutex_t *);

void	Pthread_cond_broadcast(pthread_cond_t *);
void	Pthread_cond_signal(pthread_cond_t *);
void	Pthread_cond_wait(pthread_cond_t *, pthread_mutex_t *);
void	Pthread_cond_timedwait(pthread_cond_t *, pthread_mutex_t *,
							   const struct timespec *);

void	Pthread_key_create(pthread_key_t *, void (*)(void *));
void	Pthread_setspecific(pthread_key_t, const void *);
void	Pthread_once(pthread_once_t *, void (*)(void));

#endif	/* __unp_pthread_h */

/*Max idle time for a client*/
extern int max_idle_time;

typedef struct connection
{
	int status;
	char nickname[10];
	char hostname[10];
	char realname[20];
	int sockfd;
	time_t time_joined;
	/* data */
} strCon;
typedef struct 
{
	int sockfd;
	fd_set allset;
} fdSetStruct;

extern strCon connections[MAXCLIENTS]; //Array to store information on connections
extern pthread_mutex_t connection_mutex;
